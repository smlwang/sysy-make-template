#pragma once
#include<iostream>
#include<map>
class regEnum
{
private:
    std::string reg[15] = {
        "t0", "t1", "t2", "t3", "t4", "t5", "t6",
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
    };
    int idx;
public:
    regEnum(){idx = 0;}
    ~regEnum(){}
    const std::string next(){
        idx = (idx + 1) % 15;
        return reg[idx];
    } 
    const std::string now(){
        return reg[idx];
    }
};
static regEnum reg;
static std::map<unsigned long long, std::string> regaddr;