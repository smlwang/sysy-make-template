#ifndef _AST_DEF_HPP
#define _AST_DEF_HPP
#include "../fmt/print.hpp"
#include "include/block_symbol.hpp"
#include "include/branch_id.hpp"
#include "include/genId.hpp"
#include "include/ret.hpp"
#include "include/symbol_table.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <vector>
static std::map<std::string, std::string> kexp = {
    {"-", "sub"}, {"+", "add"}, {"/", "div"}, {"*", "mul"}, {"%", "mod"},
    {"<", "lt"},  {">", "gt"},  {"<=", "le"}, {">=", "ge"}, {"==", "eq"},
    {"!=", "ne"}, {"&", "and"}, {"|", "or"},
};

// IR retrun br jump 检测
static RetCmp rets;

// 临时变量申请
static Idgenerator irid("%ir_t");

static BlockSymbol block_symbol;
static std::map<std::string, int> funcType = {
    {"getint", 1},
    {"getch", 1},
    {"getarray", 1},
};
static bool global_flag;

static BranchIdGenerator bid;
static std::string LoadIdent(const std::string &ident) {
    if (ident[0] != '@') {
        return ident;
    }
    auto tmp = irid.next();
    TextLine(tmp, " = load ", ident);
    return tmp;
}
class BaseAST {
public:
    virtual ~BaseAST() = default;
    virtual std::unique_ptr<std::string> Dump() const = 0;
    virtual int Eval() const = 0;
};
#endif