#ifndef AST_INCLUDE_GENID_HPP
#define AST_INCLUDE_GENID_HPP
#include <iostream>
#include <vector>
class Idgenerator {
private:
    std::string _prefix;
    size_t _no;

public:
    // 当前计数编号
    const std::string get(long long count) const {
        return _prefix + std::to_string(count);
    }
    // 下一个计数编号
    const std::string next() {
        _no += 1;
        return get(_no);
    }
    // 刚刚用过的编号
    const std::string last() const { return get(_no); }
    // 重置编号, 新方法快
    void init() { _no = 0; }
    // 当前计数前置编号
    ~Idgenerator(){};
    Idgenerator(const std::string &_pre) : _prefix(_pre){};
};
#endif