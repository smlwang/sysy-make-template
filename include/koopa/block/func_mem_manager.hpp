#ifndef _KOOPA_BLOCK_FUNC_MEM_MANAGER_HPP
#define _KOOPA_BLOCK_FUNC_MEM_MANAGER_HPP
#include "../../fmt/print.hpp"
#include <cassert>
#include <map>
#include <string>
#include <vector>
struct FuncInfo {
    // whether this function will call another function or not
    bool call;

    size_t max_cal_args;

    size_t self_args;

    // count the memory of variables need to alloc on the function frame
    size_t stack_mem_count;

    void init() {
        call = false;
        stack_mem_count = 0;
        max_cal_args = 0;
        stack_mem_count = 0;
    }
};

const std::map<std::string, size_t> regular = {
    {"a0", 0}, {"a1", 1}, {"a2", 2}, {"a3", 3},
    {"a4", 4}, {"a5", 5}, {"a6", 6}, {"a7", 7},
};
class FuncMemManager {

private:
    std::map<std::string, size_t> _manager;
    size_t _arg_num; // 本函数形参个数
    size_t _self_arg_start; // 本函数参数传入后存放位置
    size_t _temp_start;
    size_t _temp_end;
    size_t _ra_start;
    size_t _tot;
    bool _call;

public:
    FuncMemManager() = default;
    FuncMemManager(FuncInfo info) : _call(info.call) {
        _arg_num = info.self_args;
        _self_arg_start = info.max_cal_args;
        if (_self_arg_start > 8) {
            _self_arg_start -= 8;
        } else {
            _self_arg_start = 0;
        }
        _temp_start = _self_arg_start + info.self_args;
        _ra_start = _temp_end = _temp_start + info.stack_mem_count;
        _tot = _ra_start;
        if (_call) {
            _tot += 1;
        }
        while (_tot & 3) _tot++;
    }
    ~FuncMemManager() = default;
    size_t insert(const std::string &var) {
        _manager[var] = --_temp_end;
        return _temp_end;
    }
    std::string sp_args(size_t i) const {
        assert(i > 7);
        return std::to_string((i - 8) * 4) + "(sp)";
    }
    size_t sp_offset(const std::string &var) {
        if (_manager.count(var)) {
            return _manager[var] * 4;
        }
        return insert(var) * 4;
    }
    auto begin() { return _manager.begin(); }
    auto end() { return _manager.end(); }
    std::string sp_address(const std::string &var) {
        return std::to_string(sp_offset(var)) + "(sp)";
    }
    std::string addr(int i) const { return std::to_string(i * 4) + "(sp)"; }
    std::vector<std::string> prologue(const std::vector<std::string> &p) {
        std::vector<std::string> prologues;
        if (_tot) prologues.push_back("addi sp, sp, -" + std::to_string(_tot * 4));

        // load arguments
        for (int i = 0; i < std::min((size_t)8, _arg_num); i++) {
            prologues.push_back("sw a" + std::to_string(i) + ", " +
                                addr(_self_arg_start + i));
            _manager[p[i]] = _self_arg_start + i;
        }
        for (int i = 8; i < _arg_num; i++) {
            prologues.push_back("lw a0, " + addr(_tot + i - 8));
            prologues.push_back("sw a0, " + addr(_self_arg_start + i));
            _manager[p[i]] = _self_arg_start + i;
        }

        // store ra
        if (_call) {
            prologues.push_back("sw ra, " + addr(_ra_start));
        }
        return prologues;
    }
    std::vector<std::string> epilogue() {
        std::vector<std::string> epilogues;
        if (_call) {
            epilogues.push_back("lw ra, " + addr(_ra_start));
        }
        if (_tot) epilogues.push_back("addi sp, sp, " + std::to_string(_tot * 4));
        epilogues.push_back("ret");
        return epilogues;
    }
};

#endif