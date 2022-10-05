#pragma once
#include<memory>
#include<vector>
#include<iostream>
#include"../tool/genId.hpp"
#include"../tool/const_table.hpp"
#include<map>
static std::map<std::string, std::string> kexp = {
    {"-", "sub"},   {"+", "add"},
    {"/", "div"},   {"*", "mul"},
    {"%", "mod"},
    {"<", "lt"},    {">", "gt"},
    {"<=", "le"},   {">=", "ge"},
    {"==", "eq"},   {"!=", "ne"},
    {"&", "and"},  {"|", "or"},
};
static Idgenerator irid("%ir_t", {});
static ConstSymbol constSymbol;
class BaseAST {
    public:
        virtual ~BaseAST() = default;
        virtual std::unique_ptr<std::string> Dump() const = 0;
        virtual int Eval() const = 0;
};
