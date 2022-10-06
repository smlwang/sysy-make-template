#pragma once
#include<map>
#include<iostream>
#include<assert.h>
#include<variant>
class SymbolTalbe
{
private:
    std::map<std::string, std::variant<int, std::string>> table;
public:
    enum TYPE{CONST, VAR};
    SymbolTalbe(){};
    ~SymbolTalbe() = default;
    void addConst(const std::string &ident, int val){
        assert(!table.count(ident));
        table[ident] = val;
    }
    void addVar(const std::string &ident, const std::string &val){
        assert(!table.count(ident));
        table[ident] = val;
    }
    int getConst(const std::string &ident){
        assert(table.count(ident));
        return toConst(table[ident]);
    }
    int toConst(std::variant<int, std::string> val){
        return std::get<int>(val);
    }
    std::string getVar(const std::string &ident){
        assert(table.count(ident)); 
        return toVar(table[ident]);
    }
    std::string toVar(std::variant<int, std::string> val){
        return std::get<std::string>(val);
    }
    std::variant<int, std::string> get(const std::string &ident){
        assert(table.count(ident)); 
        return table[ident];
    }
    bool has(const std::string &ident){
        return table.count(ident);
    }
};


