#pragma once
#include<map>
#include<iostream>
#include<assert.h>
class ConstSymbol
{
private:
    std::map<std::string, int> table;
public:
    ConstSymbol(){};
    ~ConstSymbol(){};
    void add(const std::string &consym, int val){
        assert(!table.count(consym));
        table[consym] = val;
    }
    int get(const std::string &consym){
        assert(table.count(consym)); 
        return table[consym];
    }
    bool has(const std::string &consym){
        return table.count(consym);
    }
};


