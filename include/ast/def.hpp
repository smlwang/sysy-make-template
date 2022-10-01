#pragma once
#include<memory>
#include<iostream>
#include"../tool/genId.hpp"
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
static Idgenerator unaryid("%_unary_tmp_");
class BaseAST {
    public:
        virtual ~BaseAST() = default;
        virtual std::unique_ptr<std::string> Dump() const = 0;
};
