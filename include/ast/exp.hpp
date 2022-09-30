#pragma once
#include"def.hpp"
// Stmt        ::= "return" Exp ";";
// Exp         ::= UnaryExp;
// UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp;
// PrimaryExp  ::= "(" Exp ")" | Number;
// UnaryOp     ::= "+" | "-" | "!";
// Number      ::= INT_CONST;

class ExpAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> unaryExp;
        void Dump() const override {
            unaryExp->Dump();
        }
};
class PrimaryExp1 : public BaseAST {
    public:// ( Exp )
        std::unique_ptr<BaseAST> exp;
        void Dump() const override {
            exp->Dump();
        }
};
class PrimaryExp2 : public BaseAST {
    public: // Number
        std::unique_ptr<BaseAST> number;
        void Dump() const override {
            std::cout << unaryid.next() << " = sub "; 
            number->Dump();
            std::cout << ", 0" << std::endl;
        }
};
class UnaryExp1 : public BaseAST {
    public:// PrimaryExp
        std::unique_ptr<BaseAST> primaryExp;
        void Dump() const override {
            primaryExp->Dump();
        }
};
class UnaryExp2 : public BaseAST {
    public: // UnaryOp UnaryExp
        std::unique_ptr<BaseAST> unaryOp, unaryExp;
        void Dump() const override {
            unaryExp->Dump();
            unaryOp->Dump();
        }
};
class UnaryOpAST : public BaseAST {
    public:
        std::string unaryOp;
        void Dump() const override {
            auto out = [](const std::string &s){
                std::cout << s << std::endl;
            };
            if(unaryOp == "!"){
                out(unaryid.next() +  " = eq 0, " + unaryid.pre());
            }else if(unaryOp == "-"){
                out(unaryid.next() +  " = sub 0, " + unaryid.pre());
            }
        }
};