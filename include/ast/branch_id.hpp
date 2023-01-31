#ifndef _AST_BRANCH_ID_HPP
#define _AST_BRANCH_ID_HPP
#include <string>
#include <vector>
class BranchIdGenerator
{
public:
    enum BTYPE
    {
        IF,
        WHILE,
        FOR,
        LAND,
        LOR,
    };
    struct binfo
    {
        BTYPE ty;
        size_t _no;
    };

private:
    size_t _cnt;
    std::vector<binfo> _delc;

public:
    // 当前计数编号
    void new_branch(BTYPE type)
    {
        _cnt += 1;
        _delc.push_back({type, _cnt});
    }
    void end_branch()
    {
        _delc.pop_back();
    }
    std::string bthen()
    {
        auto [_cur_type, _cur_no] = _delc.back();
        switch (_cur_type)
        {
        case IF:
            return "%if" + std::to_string(_cur_no) + "_then";
        case LAND:
            return "%and" + std::to_string(_cur_no) + "_then";
        case LOR:
            return "%or" + std::to_string(_cur_no) + "_then";
        case FOR:
        case WHILE:
        default:
            break;
        }
        return "";
    }
    std::string belse()
    {
        auto [_cur_type, _cur_no] = _delc.back();
        switch (_cur_type)
        {
        case IF:
            return "%if" + std::to_string(_cur_no) + "_else";
        case LAND:
        case LOR:
        case FOR:
        case WHILE:
        default:
            break;
        }
        return "";
    }
    std::string bend()
    {
        auto [_cur_type, _cur_no] = _delc.back();
        switch (_cur_type)
        {
        case IF:
            return "%if" + std::to_string(_cur_no) + "_end";
        case LAND:
            return "%and" + std::to_string(_cur_no) + "_end";
        case LOR:
            return "%or" + std::to_string(_cur_no) + "_end";
        case FOR:
        case WHILE:
        default:
            break;
        }
        return "";
    }
    std::string alloc()
    {
        auto [_cur_type, _cur_no] = _delc.back();
        switch (_cur_type)
        {
        case LOR:
            return "@or" + std::to_string(_cur_no);
            break;
        case LAND:
            return "@and" + std::to_string(_cur_no);
            break;

        default:
            break;
        }
        return "";
    }
};
#endif