#pragma once
#include"def.hpp"
// Stmt        ::= "return" Exp ";";
// Exp         ::= AddExp;
// AddExp      ::= MulExp | AddExp ("+" | "-") MulExp;
// MulExp      ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
// UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp;
// PrimaryExp  ::= "(" Exp ")" | Number;
// UnaryOp     ::= "+" | "-" | "!";
// Number      ::= INT_CONST;
class ExpAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> addExp;
        std::unique_ptr<std::string> Dump() const override {
           return addExp->Dump();
        }
};
class PrimaryExp1 : public BaseAST {
    public:// ( Exp )
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
           return exp->Dump();
        }
};
class PrimaryExp2 : public BaseAST {
    public: // Number
        std::string number;
        std::unique_ptr<std::string> Dump() const override {
            std::string lef = unaryid.next();
            std::cout << lef << " = sub " << number << ", 0\n";
            return std::unique_ptr<std::string>(new std::string(lef));
        }
};
class UnaryExp1 : public BaseAST {
    public:// PrimaryExp
        std::unique_ptr<BaseAST> primaryExp;
        std::unique_ptr<std::string> Dump() const override {
           return primaryExp->Dump();
        }
};
class UnaryExp2 : public BaseAST {
    public: // UnaryOp UnaryExp
        std::string unaryOp;
        std::unique_ptr<BaseAST> unaryExp;
        std::unique_ptr<std::string> Dump() const override {
            if(unaryOp == "+") return unaryExp->Dump();
            auto rig = unaryExp->Dump();
            auto lef = unaryid.next();
            std::cout << lef << " = ";
            if(unaryOp == "!"){
                std::cout << "eq 0, "; 
            }else if(unaryOp == "-"){
                std::cout << "sub 0, "; 
            }
            std::cout << (*rig) << "\n";
            return std::unique_ptr<std::string>(new std::string(lef));            
        }
};

class AddExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> mulExp;
        std::unique_ptr<std::string> Dump() const override {
           return mulExp->Dump();
        }
};
class AddExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> addExp;
        std::string add;
        std::unique_ptr<BaseAST> mulExp;
        std::unique_ptr<std::string> Dump() const override {
            auto rig1 = addExp->Dump();
            auto rig2 = mulExp->Dump();
            auto lef = unaryid.next();
            std::cout << lef << " = ";
            if(add == "+"){
                std::cout << "add ";
            }else if(add == "-"){
                std::cout << "sub ";
            }
            std::cout << (*rig1) << ", " << (*rig2) << '\n';
            return std::unique_ptr<std::string>(new std::string(lef));
        }
};

class MulExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> unaryExp;
        std::unique_ptr<std::string> Dump() const override {
           return unaryExp->Dump();
        }
};
class MulExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> mulExp;
        std::string mul;
        std::unique_ptr<BaseAST> unaryExp;
        std::unique_ptr<std::string> Dump() const override {
            auto rig1 = mulExp->Dump();
            auto rig2 = unaryExp->Dump();
            auto lef = unaryid.next();
            std::cout << lef << " = ";
            if(mul == "*"){
                std::cout << "mul ";
            }else if(mul == "/"){
                std::cout << "div ";
            }else if(mul == "%"){
                std::cout << "mod ";
            }
            std::cout << (*rig1) << ", " << (*rig2) << '\n';
            return std::unique_ptr<std::string>(new std::string(lef));
        }
};