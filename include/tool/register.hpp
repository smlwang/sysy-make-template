#pragma once
#include<iostream>
class regEnum
{
private:
    int tcnt;
    int acnt;
public:
    regEnum(){tcnt = 0, acnt = 0;}
    ~regEnum(){}
    std::string nextT(){
        ++tcnt;
        if(tcnt >= 7) tcnt -= 7;
        return "t" + std::to_string(tcnt);
    }
    std::string nowT(){
        return "t" + std::to_string(tcnt);
    }
    std::string preT(){
        return "t" + std::to_string((tcnt + 6)  % 7);
    }
    std::string nextA(){
        ++tcnt;
        if(tcnt >= 8) tcnt -= 8;
        return "a" + std::to_string(acnt);
    }
    std::string nowA(){
        return "a" + std::to_string(acnt);
    }
    std::string preA(){
        return "a" + std::to_string((acnt + 7) % 8);
    }
};
static regEnum reg;