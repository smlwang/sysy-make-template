#pragma once
#include<memory>
#include<iostream>
#include"../tool/genId.hpp"
static Idgenerator unaryid("%_unary_tmp_");
class BaseAST {
    public:
        virtual ~BaseAST() = default;
        virtual std::unique_ptr<std::string> Dump() const = 0;
};
