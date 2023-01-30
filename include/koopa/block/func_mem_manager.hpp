#ifndef _KOOPA_BLOCK_FUNC_MEM_MANAGER_HPP
#define _KOOPA_BLOCK_FUNC_MEM_MANAGER_HPP
#include "../print.hpp"
#include <map>
#include <string>
#include <vector>
const std::map<std::string, size_t> regular = {
    {"a0", 0},
    {"a1", 1},
    {"a2", 2},
    {"a3", 3},
    {"a4", 4},
    {"a5", 5},
    {"a6", 6},
};
class FuncMemManager
{

private:
    std::map<std::string, size_t> _manager;
    size_t _tot;

public:
    FuncMemManager() = default;
    ~FuncMemManager() = default;
    size_t insert(const std::string &var)
    {
        _manager[var] = --_tot;
        return _tot;
    }
    size_t sp_offset(const std::string &var)
    {
        if (_manager.count(var))
        {
            return _manager[var] * 4;
        }
        return insert(var) * 4;
    }
    auto begin()
    {
        return _manager.begin();
    }
    auto end()
    {
        return _manager.end();
    }
    std::string sp_address(const std::string &var)
    {
        return std::to_string(sp_offset(var)) + "(sp)";
    }
    void init(size_t var, bool is_caller)
    {
        _manager = regular;
        _tot = 18;
        if (is_caller)
        {
            _manager["ra"] = 19;
            _tot = 19;
        }
        _tot += var;
    }
    size_t var_num()
    {
        return _tot;
    }
};

#endif