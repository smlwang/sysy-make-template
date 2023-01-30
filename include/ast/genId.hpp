#pragma once
#include <iostream>
#include <vector>
class Idgenerator {
private:
    std::string _prefix;
    size_t _no;
public:
    //当前计数编号
    const std::string get(long long count) {
        return _prefix + std::to_string(count);
    }
    //下一个计数编号
    const std::string next() {
        _no += 1;
        return get(_no);
    }
    //当前计数前置编号
    ~Idgenerator(){};
    Idgenerator(const std::string &_pre) : _prefix(_pre) {};
};


