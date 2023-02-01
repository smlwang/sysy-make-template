#ifndef _AST_INCLUDE_RET_HPP
#define _AST_INCLUDE_RET_HPP
#include <vector>
class RetCmp {
private:
    std::vector<char> _ret;

public:
    RetCmp() = default;
    ~RetCmp() = default;
    void in() { _ret.push_back(0); }
    bool retruned() const { return _ret.back(); }
    void ret() { _ret.back() = 1; }
    void out() { _ret.pop_back(); }
    size_t size() const { return _ret.size(); }
};
#endif
