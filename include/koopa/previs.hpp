#pragma once
#include "../fmt/print.hpp"
#include "block/variable.hpp"
#include "koopa.h"
#include "register.hpp"
#include <assert.h>
#include <iostream>

struct FuncInfo {
    // whether this function will call another function or not
    bool call;

    // count the memory of variables need to alloc on the function frame
    size_t stack_mem_count;

    void init() {
        call = false;
        stack_mem_count = 0;
    }
};

FuncInfo pre_visit(const koopa_raw_function_t &);

void pre_visit(const koopa_raw_slice_t &);
void pre_visit(const koopa_raw_value_t &);
void pre_visit(const koopa_raw_basic_block_t &);
void pre_visit(const koopa_raw_aggregate_t &);
void pre_visit(const koopa_raw_func_arg_ref_t &);
void pre_visit(const koopa_raw_block_arg_ref_t &);
void pre_visit(const koopa_raw_get_ptr_t &);
void pre_visit(const koopa_raw_get_elem_ptr_t &);

static FuncInfo func_info;
static VariableCounter var_counter;
static void pre_init() {
    func_info.init();
    var_counter.init();
}

// 访问函数
FuncInfo pre_visit(const koopa_raw_function_t &func) {
    pre_init();

    // 访问所有基本块
    pre_visit(func->bbs);

    func_info.stack_mem_count = var_counter.var_num();
    return func_info;
}

// 访问 raw slice
void pre_visit(const koopa_raw_slice_t &slice) {
    for (size_t i = 0; i < slice.len; ++i) {
        auto ptr = slice.buffer[i];
        // 根据 slice 的 kind 决定将 ptr 视作何种元素
        switch (slice.kind) {
        case KOOPA_RSIK_BASIC_BLOCK:
            // 访问基本块
            pre_visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr));
            break;
        case KOOPA_RSIK_VALUE:
            // 访问指令
            pre_visit(reinterpret_cast<koopa_raw_value_t>(ptr));
            break;
        default:
            // 我们暂时不会遇到其他内容, 于是不对其做任何处理
            assert(false);
        }
    }
}

// 访问基本块
void pre_visit(const koopa_raw_basic_block_t &bb) {
    // 访问所有指令
    pre_visit(bb->insts);
}

// 访问指令
void pre_visit(const koopa_raw_value_t &value) {
    // 根据指令类型判断后续需要如何访问
    if (value->name) {
        var_counter.insert(value->name);
    }
}