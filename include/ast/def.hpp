#pragma once
#include "ret.hpp"
#include "../fmt/print.hpp"
#include "block_symbol.hpp"
#include "branch_id.hpp"
#include "genId.hpp"
#include "symbol_table.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <vector>
static std::map<std::string, std::string> kexp = {
    {"-", "sub"}, {"+", "add"},
    {"/", "div"}, {"*", "mul"},
    {"%", "mod"}, {"<", "lt"},
    {">", "gt"}, {"<=", "le"},
    {">=", "ge"}, {"==", "eq"},
    {"!=", "ne"}, {"&", "and"},
    {"|", "or"},
};
static RetCmp rets;
static Idgenerator irid("%ir_t");
static BlockSymbol block_symbol;
static BranchIdGenerator bid;
static std::string LoadIdent(const std::string &ident)
{
    auto tmp = irid.next();
    TextLine(tmp, " = load ", ident);
    return tmp;
}
class BaseAST
{
public:
    virtual ~BaseAST() = default;
    virtual std::unique_ptr<std::string> Dump() const = 0;
    virtual int Eval() const = 0;
};
