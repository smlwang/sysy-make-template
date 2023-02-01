#ifndef _AST_INCLUDE_BLOCK_SYMBOL_HPP
#define _AST_INCLUDE_BLOCK_SYMBOL_HPP
#include "symbol_table.hpp"
#include <cassert>
#include <vector>
class BlockSymbol {
private:
    std::map<std::string, int> _count;
    std::vector<SymbolTalbe> _stack;
public:
    BlockSymbol() : _stack(1) {}
    ~BlockSymbol() = default;
    void step_in_block() { _stack.push_back({}); }
    void step_out_block() { _stack.pop_back(); }
    value qruey(const std::string &var) {
        for (int i = _stack.size() - 1; i >= 0; i--) {
            if (_stack[i].has(var)) {
                return _stack[i].get(var);
            }
        }
        assert(false);
        return {};
    }
    int depth() const { return _stack.size(); }
    void param_def(const std::string &var) {
        auto &st = _stack.back();
        st.addVar(var, "%" + var);
    }
    std::string var_def(const std::string &var) {
        auto &st = _stack.back();
        assert(!st.has(var));
        _count[var] += 1;
        const std::string alter = "@" + var + std::to_string(_count[var]);
        st.addVar(var, alter);
        return alter;
    }
    int const_def(const std::string &var, const int c) {
        auto &st = _stack.back();
        assert(!st.has(var));
        st.addConst(var, c);
        return c;
    }
    std::string global_var(const std::string &gvar) {
        assert(_stack.size() == 1);
        auto &gst = _stack[0];
        gst.addVar(gvar, "@g_" + gvar);
        return "@g_" + gvar;
    }
    int to_const(value v) { return _stack.back().toConst(v._value); }
    std::string to_var(value v) { return _stack.back().toVar(v._value); }
    bool has(const std::string &var) { return _stack.back().has(var); }
};

#endif
