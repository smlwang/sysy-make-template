#pragma once
#include <iostream>
class Idgenerator {
private:
    long long count;
    std::string prefix;

public:
    //当前计数编号
    const std::string get() {
        return prefix + std::to_string(count);
    }
    //下一个计数编号
    const std::string next() {
        ++count;
        return get();
    }
    //当前计数前置编号
    ~Idgenerator(){};
    Idgenerator(const std::string &_pre) : prefix(_pre) {
        count = 0;
    }
};


