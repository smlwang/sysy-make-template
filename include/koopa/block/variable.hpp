#ifndef _KOOPA_BLOCK_VARIABLE_HPP
#define _KOOPA_BLOCK_VARIABLE_HPP
#include <set>
#include <string>
#include <vector>
class VariableCounter {
private:
    std::set<std::string> _counter;

public:
    VariableCounter() = default;
    ~VariableCounter() = default;
    void insert(const std::string &var) { _counter.insert(var); }
    void init() { _counter.clear(); }
    size_t var_num() { return _counter.size(); }
};
#endif