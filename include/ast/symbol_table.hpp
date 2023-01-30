#pragma once
#include <assert.h>
#include <iostream>
#include <map>
#include <variant>
struct value
{
    bool flag;
    std::variant<int, std::string> _value;
};

class SymbolTalbe
{
private:
    std::map<std::string, value> table;

public:
    enum TYPE {
        CONST,
        VAR
    };
    SymbolTalbe(){};
    ~SymbolTalbe() = default;
    void addConst(const std::string &ident, int val)
    {
        assert(!table.count(ident));
        table[ident] = {CONST, val};
    }
    void addVar(const std::string &ident, const std::string &val)
    {
        assert(!table.count(ident));
        table[ident] = {VAR, val};
    }
    int getConst(const std::string &ident)
    {
        assert(table.count(ident));
        return toConst(table[ident]._value);
    }
    int toConst(std::variant<int, std::string> val)
    {
        return std::get<int>(val);
    }
    std::string getVar(const std::string &ident)
    {
        assert(table.count(ident));
        return toVar(table[ident]._value);
    }
    std::string toVar(std::variant<int, std::string> val)
    {
        return std::get<std::string>(val);
    }
    value get(const std::string &ident)
    {
        assert(table.count(ident));
        return table[ident];
    }
    bool has(const std::string &ident)
    {
        return table.count(ident);
    }
};
