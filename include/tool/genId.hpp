#pragma once
#include <iostream>
#include <vector>
class Idgenerator {
private:
    std::string prefix;
    std::vector<int> stk;
public:
    //当前计数编号
    const std::string get(long long count) {
        return prefix + std::to_string(count);
    }
    //下一个计数编号
    const std::string next() {
        stk[stk.size() - 1] += 1;
        return get(stk.back());
    }
    void in(){
        stk.push_back(-1);
    }
    void out(){
        stk.pop_back();
    }
    //当前计数前置编号
    ~Idgenerator(){};
    Idgenerator(const std::string &_pre, const std::vector<int> v) : prefix(_pre), stk(v) {
        
    };
};


