#pragma once
#include "../fmt/print.hpp"
#include "block/func_mem_manager.hpp"
#include "koopa.h"
#include "previs.hpp"
#include "register.hpp"
#include <cassert>
#include <iostream>
#include <algorithm>

#define toull(x) ((unsigned long long)(&x))
void Visit(const koopa_raw_program_t &);
void Visit(const koopa_raw_slice_t &);
void Visit(const koopa_raw_function_t &);
void Visit(const koopa_raw_basic_block_t &);
void Visit(const koopa_raw_value_t &);
void Visit(const koopa_raw_integer_t &);
void Visit(const koopa_raw_aggregate_t &);
void Visit(const koopa_raw_func_arg_ref_t &);
void Visit(const koopa_raw_block_arg_ref_t &);
void Visit(const koopa_raw_global_alloc_t &);
void Visit(const koopa_raw_load_t &);
void Visit(const koopa_raw_store_t &);
void Visit(const koopa_raw_get_ptr_t &);
void Visit(const koopa_raw_get_elem_ptr_t &);
void Visit(const koopa_raw_binary_t &);
void Visit(const koopa_raw_branch_t &);
void Visit(const koopa_raw_jump_t &);
void Visit(const koopa_raw_call_t &);
void Visit(const koopa_raw_return_t &);

TempRegister t_reg;
FuncMemManager sp_allocer;
std::map<std::string, bool> vis;
std::string cur_func_end;

static bool has_return;
void Visit(const koopa_raw_program_t &program) {
    // 访问所有全局变量
    Visit(program.values);
    // 访问所有函数
    Visit(program.funcs);
}

struct instrution_name {
    std::string name;
    bool has;
} iname;

std::string phare_arg(const koopa_raw_value_t &arg) {
    std::string tmp = t_reg.apply();
    if (arg->kind.tag == KOOPA_RVT_INTEGER) {
        TextLine("li ", tmp, ", ", arg->kind.data.integer.value);
    } else {
        TextLine("lw ", tmp, ", ", sp_allocer.sp_address(arg->name));
    }
    return tmp;
}
// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice) {
    for (size_t i = 0; i < slice.len; ++i) {
        auto ptr = slice.buffer[i];
        // 根据 slice 的 kind 决定将 ptr 视作何种元素
        switch (slice.kind) {
        case KOOPA_RSIK_FUNCTION:
            // 访问函数
            Visit(reinterpret_cast<koopa_raw_function_t>(ptr));
            break;
        case KOOPA_RSIK_BASIC_BLOCK:
            // 访问基本块
            Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr));
            break;
        case KOOPA_RSIK_VALUE:
            // 访问指令
            Visit(reinterpret_cast<koopa_raw_value_t>(ptr));
            break;
        default:
            // 我们暂时不会遇到其他内容, 于是不对其做任何处理
            assert(false);
        }
    }
}
std::vector<std::string> get_func_param(const koopa_raw_slice_t &slice) {
    std::vector<std::string> params;
    for (size_t i = 0; i < slice.len; ++i) {
        auto ptr = slice.buffer[i];
        auto alter = reinterpret_cast<koopa_raw_value_t>(ptr);
        params.push_back(alter->name);
    }
    return params;
}
// 访问函数
void Visit(const koopa_raw_function_t &func) {
    if (func->bbs.len == 0) return;
    TextLine(".text");
    TextLine(".globl ", func->name + 1);
    // prologue
    Line(func->name + 1, ":");
    cur_func_end = std::string(func->name + 1) + "_end";
    auto info = pre_visit(func);
    std::vector<std::string> params = get_func_param(func->params);
    sp_allocer = FuncMemManager(info); 
    auto prologues = sp_allocer.prologue(params);
    for (auto v : prologues) {
        TextLine(v);
    }
    Line("");

    // 访问所有基本块
    Visit(func->bbs);

    // epilogue
    LabelOut(cur_func_end);
    auto epilogues = sp_allocer.epilogue();
    for (auto v : epilogues) {
        TextLine(v);
    }
    Line("");
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb) {
    if (bb->insts.len == 0) return;
    if (vis[std::string(bb->name)])
        return;
    if (std::string(bb->name + 1) != "entry")
        vis[bb->name] = 1;
    // 访问所有指令
    Visit(bb->insts);
}

// 访问指令
void Visit(const koopa_raw_value_t &value) {
    // 根据指令类型判断后续需要如何访问
    const auto &kind = value->kind;
    iname.has = value->name;
    if (value->name) {
        iname.name = std::string(value->name);
    }
    switch (kind.tag) {
    case KOOPA_RVT_RETURN:
        // 访问 return 指令
        Visit(kind.data.ret);
        break;
    case KOOPA_RVT_INTEGER:
        // 访问 integer 指令
        Visit(kind.data.integer);
        Line("");
        break;
    // 访问 二元运算符
    case KOOPA_RVT_BINARY:
        Visit(kind.data.binary);
        Line("");
        break;
    case KOOPA_RVT_ALLOC:
        Visit(kind.data.global_alloc);
        Line("");
        break;
    case KOOPA_RVT_LOAD:
        Visit(kind.data.load);
        Line("");
        break;
    case KOOPA_RVT_STORE:
        Visit(kind.data.store);
        Line("");
        break;
    case KOOPA_RVT_BRANCH:
        Visit(kind.data.branch);
        break;
    case KOOPA_RVT_JUMP:
        Visit(kind.data.jump);
        break;
    case KOOPA_RVT_CALL:
        if (value->name) has_return = true;
        Visit(kind.data.call);
        has_return = false;
        break;
    case KOOPA_RVT_GLOBAL_ALLOC:
        Visit(kind.data.global_alloc);
        break;
    default:
        // 其他类型暂时遇不到
        // exit(1);
        assert(false);
    }
}
void Visit(const koopa_raw_return_t &ret) {
    if (!ret.value) {
        TextLine("j ", cur_func_end);
        return;
    }
    if (ret.value->ty->tag != KOOPA_RTT_UNIT) {
        if (ret.value->kind.tag == KOOPA_RVT_INTEGER) {
            TextLine("li a0, ", ret.value->kind.data.integer.value);
        } else {
            std::string retv = phare_arg(ret.value);
            TextLine("mv a0, ", retv);
        }
    }
    TextLine("j ", cur_func_end);
}

void Visit(const koopa_raw_integer_t &integer) { Out(integer.value); }

void Visit(const koopa_raw_binary_t &binary) {
    auto op = binary.op;
    auto l = binary.lhs;
    auto r = binary.rhs;
    std::string lhs = phare_arg(l);
    std::string rhs = phare_arg(r);
    std::string dest = t_reg.apply();
    std::string destAdr = sp_allocer.sp_address(iname.name);
    TextLine("lw ", dest, ", ", destAdr);
    switch (op) {
    case KOOPA_RBO_ADD:
        BinaryOut("add", dest, lhs, rhs);
        break;
    case KOOPA_RBO_AND:
        BinaryOut("and", dest, lhs, rhs);
        break;
    case KOOPA_RBO_DIV:
        BinaryOut("div", dest, lhs, rhs);
        break;
    case KOOPA_RBO_EQ:
        BinaryOut("xor", dest, lhs, rhs);
        BinaryOut("seqz", dest, dest);
        break;
    case KOOPA_RBO_GE:
        BinaryOut("slt", dest, lhs, rhs);
        BinaryOut("seqz", dest, dest);
        break;
    case KOOPA_RBO_GT:
        BinaryOut("sgt", dest, lhs, rhs);
        break;
    case KOOPA_RBO_LE:
        BinaryOut("sgt", dest, lhs, rhs);
        BinaryOut("seqz", dest, dest);
        break;
    case KOOPA_RBO_LT:
        BinaryOut("slt", dest, lhs, rhs);
        break;
    case KOOPA_RBO_MOD:
        BinaryOut("rem", dest, lhs, rhs);
        break;
    case KOOPA_RBO_MUL:
        BinaryOut("mul", dest, lhs, rhs);
        break;
    case KOOPA_RBO_NOT_EQ:
        BinaryOut("xor", dest, lhs, rhs);
        BinaryOut("snez", dest, dest);
        break;
    case KOOPA_RBO_OR:
        BinaryOut("or", dest, lhs, rhs);
        break;
    case KOOPA_RBO_SAR:
        BinaryOut("sra", dest, lhs, rhs);
        break;
    case KOOPA_RBO_SHL:
        BinaryOut("sll", dest, lhs, rhs);
        break;
    case KOOPA_RBO_SHR:
        BinaryOut("srl", dest, lhs, rhs);
        break;
    case KOOPA_RBO_SUB:
        BinaryOut("sub", dest, lhs, rhs);
        break;
    case KOOPA_RBO_XOR:
        BinaryOut("xor", dest, lhs, rhs);
        break;
    default:
        break;
    }
    TextLine("sw ", dest, ", ", destAdr);
}

void Visit(const koopa_raw_load_t &load) {
    // %0 = load @x

    // the address of @x on stack
    auto src = sp_allocer.sp_address(load.src->name);

    // `value` will be reused
    auto value = t_reg.apply();
    // %0 = *@x
    TextLine("lw ", value, ", ", src);

    // address of %0 on stack
    auto dest = sp_allocer.sp_address(iname.name);
    // restore %0 to stack
    TextLine("sw ", value, ", ", dest);
}

void Visit(const koopa_raw_store_t &store) {
    // store %1, @x

    // get the value of %1 on stack
    auto src = phare_arg(store.value);

    // get the address of @x
    auto dest = sp_allocer.sp_address(store.dest->name);

    // @x = %1
    TextLine("sw ", src, ", ", dest);
}
void Visit(const koopa_raw_global_alloc_t &alloc) {
    // do nothing, the variable has been allocated
}
void Visit(const koopa_raw_branch_t &branch) {
    auto cond = phare_arg(branch.cond);
    TextLine("bnez ", cond, ", ", branch.true_bb->name + 1);
    TextLine("j ", branch.false_bb->name + 1);
    std::string t_branch = branch.true_bb->name;
    if (!vis[t_branch]) {
        vis[t_branch] = 1;
        Line("");
        LabelOut(branch.true_bb->name + 1);
        Visit(branch.true_bb->insts);
    }
    std::string f_branch = branch.false_bb->name;
    if (!vis[f_branch]) {
        vis[f_branch] = 1;
        Line("");
        LabelOut(branch.false_bb->name + 1);
        Visit(branch.false_bb->insts);
    }
}
void Visit(const koopa_raw_jump_t &jump) {
    TextLine("j ", jump.target->name + 1);
    if (vis[jump.target->name])
        return;
    vis[jump.target->name] = 1;
    Line("");
    LabelOut(jump.target->name + 1);
    Visit(jump.target->insts);
}

void deal_call_param(const koopa_raw_slice_t& slice, int idx) {
    auto ptr = slice.buffer[idx];
    auto alter = reinterpret_cast<koopa_raw_value_t>(ptr);
    if (alter->kind.tag == KOOPA_RVT_INTEGER) {
        int p = alter->kind.data.integer.value;
        if (idx < 8) {
            TextLine("li a",  idx, ", ", p);
        } else {
            TextLine("li t0, ", p);
            TextLine("sw t0, ", sp_allocer.sp_args(idx));
        }
    } else {
        if (idx < 8) {
            TextLine("lw a", idx, ", ", sp_allocer.sp_address(alter->name));
        } else {
            TextLine("lw t0, ", sp_allocer.sp_address(alter->name));
            TextLine("sw t0, ", sp_allocer.sp_args(idx));
        }
    }
}
void Visit(const koopa_raw_call_t &call) {
    int len = call.args.len;
    for (int i = 0; i < len; i++) {
        deal_call_param(call.args, i); 
    }
    TextLine("call ", call.callee->name + 1);
    if (has_return) {
        TextLine("sw a0, ", sp_allocer.sp_address(iname.name));
    }
}
