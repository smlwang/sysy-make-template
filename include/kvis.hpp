#pragma once
#include"koopa.h"
#include<assert.h>
#include<iostream>
#include"tool/register.hpp"
void Line(const std::string&);
void Visit(const koopa_raw_program_t&);
void Visit(const koopa_raw_slice_t&);
void Visit(const koopa_raw_function_t&);
void Visit(const koopa_raw_basic_block_t&);
void Visit(const koopa_raw_value_t&);
void Visit(const koopa_raw_integer_t&);
void Visit(const koopa_raw_aggregate_t&);
void Visit(const koopa_raw_func_arg_ref_t&);
void Visit(const koopa_raw_block_arg_ref_t&);
void Visit(const koopa_raw_global_alloc_t&);
void Visit(const koopa_raw_load_t&);
void Visit(const koopa_raw_store_t&);
void Visit(const koopa_raw_get_ptr_t&);
void Visit(const koopa_raw_get_elem_ptr_t&);
void Visit(const koopa_raw_binary_t&);
void Visit(const koopa_raw_branch_t&);
void Visit(const koopa_raw_jump_t&);
void Visit(const koopa_raw_call_t&);
void Visit(const koopa_raw_return_t&);

void Line(const std::string &opt){
    std::cout << opt << std::endl;
}

std::string dealreg(const koopa_raw_value_t& value){
  const auto &kind = value->kind;
    switch (kind.tag)
    {
    case KOOPA_RVT_INTEGER:
        int num = kind.data.integer.value;
        if(!num) return "x0";
        std::cout << "li " << reg.next() << ", " << std::to_string(num) << std::endl;
        return reg.now();
    }
    return regaddr[(unsigned long long)(&(value->kind.data))];
}
void Visit(const koopa_raw_program_t &program) {
  // 访问所有全局变量
  Visit(program.values);
  Line(".text");
  Line(".global main");
  // 访问所有函数
  Visit(program.funcs);
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

// 访问函数
void Visit(const koopa_raw_function_t &func) {
  // 访问所有基本块
  //                    删符号
  Line(std::string((func->name) + 1) + ":");
  Visit(func->bbs);
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb) {
  // 访问所有指令
  Visit(bb->insts);
}

// 访问指令
void Visit(const koopa_raw_value_t &value) {
  // 根据指令类型判断后续需要如何访问
  const auto &kind = value->kind;
  switch (kind.tag) {
    case KOOPA_RVT_RETURN:
      // 访问 return 指令
      Visit(kind.data.ret);
      break;
    case KOOPA_RVT_INTEGER:
      // 访问 integer 指令
      Visit(kind.data.integer);
      break;
      // 访问 二元运算符
    case KOOPA_RVT_BINARY:
      Visit(kind.data.binary);
      break;
    default:
      // 其他类型暂时遇不到
      // exit(1);
      assert(false);
  }
}
void Visit(const koopa_raw_return_t &ret) {
    Line("mv a0, " + dealreg(ret.value));
    Line("ret");
}

void Visit(const koopa_raw_integer_t &integer){
    std::cout << std::to_string(integer.value);
}
void Visit(const koopa_raw_binary_t &binary){
    auto op = binary.op;
    auto l = binary.lhs;
    auto r = binary.rhs;
    std::string left = dealreg(l);
    std::string right = dealreg(r);
    std::string cur = reg.next(); 
    regaddr[(unsigned long long)(&binary)] = cur;
    auto out3 = [](const std::string& op, const std::string &dist, const std::string &l, const std::string &r){
        std::cout << op << " " << dist << ", " << l << ", " << r << "\n";
    };
    auto out2 = [](const std::string& op, const std::string &dist, const std::string &l){
        std::cout << op << " " << dist << ", " << l << "\n";
    };
    
    switch (op)
    {
    case KOOPA_RBO_ADD:
        out3("add", cur, left, right);
        break;
    case KOOPA_RBO_AND:
        out3("and", cur, left, right);
        break;
    case KOOPA_RBO_DIV:
        out3("div", cur, left, right);
        break;
    case KOOPA_RBO_EQ:
        out3("xor", cur, left, right);
        out2("seqz", cur, cur);
        break;
    case KOOPA_RBO_GE:
        out3("slt", cur, left, right);
        out2("seqz", cur, cur);
        break;
    case KOOPA_RBO_GT:
        out3("sgt", cur, left, right);
        break;
    case KOOPA_RBO_LE:
        out3("sgt", cur, left, right);
        out2("seqz", cur, cur);
        break;
    case KOOPA_RBO_LT:
        out3("slt", cur, left, right);
        break;
    case KOOPA_RBO_MOD:
        out3("rem", cur, left, right);
        break;
    case KOOPA_RBO_MUL:
        out3("mul", cur, left, right);
        break;
    case KOOPA_RBO_NOT_EQ:
        out3("xor", cur, left, right);
        out2("snez", cur, cur);
        break;
    case KOOPA_RBO_OR:
        out3("or", cur, left, right);
        break;
    case KOOPA_RBO_SAR:
        out3("sra", cur, left, right);
        break;
    case KOOPA_RBO_SHL:
        out3("sll", cur, left, right);
        break;
    case KOOPA_RBO_SHR:
        out3("srl", cur, left, right);
        break;
    case KOOPA_RBO_SUB:
        out3("sub", cur, left, right);
        break;
    case KOOPA_RBO_XOR:
        out3("xor", cur, left, right);
        break;
    default:
        break;
    }
}
