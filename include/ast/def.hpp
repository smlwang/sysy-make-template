#pragma once
#include<memory>
#include<iostream>
#include"../tool/genId.hpp"
static Idgenerator unaryid("%_unary_tmp_");
class BaseAST {
    public:
        virtual ~BaseAST() = default;
        virtual void Dump() const = 0;
};
class NumberAST : public BaseAST {
    public:
        std::string number;
        void Dump() const override {
            std::cout << number;
        }
};