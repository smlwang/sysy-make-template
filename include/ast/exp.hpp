#pragma once
#include"def.hpp"
#define uniqptr(x) std::unique_ptr<std::string>(new std::string(x))
// Stmt        ::= "return" Exp ";";
// Exp         ::= AddExp;
// AddExp      ::= MulExp | AddExp ("+" | "-") MulExp;
// MulExp      ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
// UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp;
// PrimaryExp  ::= "(" Exp ")" | Number;
// UnaryOp     ::= "+" | "-" | "!";
// Number      ::= INT_CONST;
static std::unique_ptr<std::string> thrOp(const std::unique_ptr<BaseAST> &l,\
                const std::unique_ptr<BaseAST> &r,\
                const std::string &op){
        auto rig1 = l->Dump();
        auto rig2 = r->Dump();
        auto lef = irid.next();
        std::cout << lef << " = " << kexp[op] << " ";
        std::cout << (*rig1) << ", " << (*rig2) << "\n"; 
        return uniqptr(lef);
}
static int eval(const std::unique_ptr<BaseAST> &l,\
                const std::unique_ptr<BaseAST> &r,\
                const std::string &op){
        auto a = l->Eval();
        auto b = r->Eval();
        if(op == "*") return a * b;
        else if(op == "/") return a / b;
        else if(op == "%") return a % b;
        else if(op == "+") return a + b;
        else if(op == "-") return a - b;
        else if(op == "==") return a == b;
        else if(op == "!=") return a != b;
        else if(op == "<=") return a <= b;
        else if(op == "<") return a < b;
        else if(op == ">=") return a >= b;
        else if(op == ">") return a > b;
        return -1;
}
class ExpAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lOrExp;
        std::unique_ptr<std::string> Dump() const override {
           return lOrExp->Dump();
        }
        int Eval() const override {
            return lOrExp->Eval();
        }
};
class PrimaryExp1 : public BaseAST {
    public:// ( Exp )
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
           return exp->Dump();
        }
        int Eval() const override {
            return exp->Eval();
        }
};
class PrimaryExp2 : public BaseAST {
    public: // Number
        std::string number;
        std::unique_ptr<std::string> Dump() const override {
            return uniqptr(number);
        }
        int Eval() const override {
            return atoi(number.c_str());
        }
};
class PrimaryExp3 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lVal;
        std::unique_ptr<std::string> Dump() const override {
            return lVal->Dump();
        }
        int Eval() const override {
            return lVal->Eval();
        }
};
class LValAST : public BaseAST {
    public:
        std::string ident;
        std::unique_ptr<std::string> Dump() const override {
            if(constSymbol.has(ident)) 
                return uniqptr(std::to_string(constSymbol.get(ident)));
            return nullptr;
        }
        int Eval() const override {
            return constSymbol.get(ident);
        }
};
class UnaryExp1 : public BaseAST {
    public:// PrimaryExp
        std::unique_ptr<BaseAST> primaryExp;
        std::unique_ptr<std::string> Dump() const override {
           return primaryExp->Dump();
        }
        int Eval() const override {
            return primaryExp->Eval();
        }
};
class UnaryExp2 : public BaseAST {
    public: // UnaryOp UnaryExp
        std::string unaryOp;
        std::unique_ptr<BaseAST> unaryExp;
        std::unique_ptr<std::string> Dump() const override {
            if(unaryOp == "+") return unaryExp->Dump();
            auto rig = unaryExp->Dump();
            auto lef = irid.next();
            std::cout << lef << " = ";
            if(unaryOp == "!"){
                std::cout << "eq 0, "; 
            }else if(unaryOp == "-"){
                std::cout << "sub 0, "; 
            }
            std::cout << (*rig) << "\n";
            return std::unique_ptr<std::string>(new std::string(lef));            
        }
        int Eval() const override {
            auto a = unaryExp->Eval();
            if(unaryOp == "+") return a;
            else if(unaryOp == "-") return -a;
            return !a;
        }
};
class AddExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> mulExp;
        std::unique_ptr<std::string> Dump() const override {
           return mulExp->Dump();
        }
        int Eval() const override {
            return mulExp->Eval();
        }
};
class AddExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> addExp;
        std::string add; // + -
        std::unique_ptr<BaseAST> mulExp;
        std::unique_ptr<std::string> Dump() const override {
            return thrOp(addExp, mulExp, add);
        }
        int Eval() const override {
            return eval(addExp, mulExp, add);
        }
};

class MulExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> unaryExp;
        std::unique_ptr<std::string> Dump() const override {
           return unaryExp->Dump();
        }
        int Eval() const override {
            return unaryExp->Eval();
        }
};
class MulExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> mulExp;
        std::string mul; // * / %
        std::unique_ptr<BaseAST> unaryExp;
        std::unique_ptr<std::string> Dump() const override {
            return thrOp(mulExp, unaryExp, mul);
        }
        int Eval() const override {
            return eval(mulExp, unaryExp, mul);
        }
};
class RelExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> addExp;
        std::unique_ptr<std::string> Dump() const override {
            return addExp->Dump();
        }
        int Eval() const override {
            return addExp->Eval();
        }
};
class RelExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> relExp;
        std::string rel; // <= < > >=
        std::unique_ptr<BaseAST> addExp;
        std::unique_ptr<std::string> Dump() const override {
            return thrOp(relExp, addExp, rel);
        }
        int Eval() const override {
            return eval(relExp, addExp, rel);
        }
};
class EqExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> relExp;
        std::unique_ptr<std::string> Dump() const override {
            return relExp->Dump();    
        }
        int Eval() const override {
            return relExp->Eval();
        }
};
class EqExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> eqExp;
        std::string eq; // !=  ==
        std::unique_ptr<BaseAST> relExp;
        std::unique_ptr<std::string> Dump() const override {
            return thrOp(eqExp, relExp, eq);
        }
        int Eval() const override {
            return eval(eqExp, relExp, eq);
        }
};
class LAndExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> eqExp;
        std::unique_ptr<std::string> Dump() const override {
            return eqExp->Dump();    
        }
        int Eval() const override {
            return eqExp->Eval();
        }
};
class LAndExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lAndExp;
        std::unique_ptr<BaseAST> eqExp;
        std::unique_ptr<std::string> Dump() const override {
            auto rig1 = lAndExp->Dump();
            auto rig2 = eqExp->Dump();
            auto lef1 = irid.next();
            std::cout << lef1 << " = ne 0, " << (*rig1) << "\n";
            auto lef2 = irid.next();
            std::cout << lef2 << " = ne 0, " << (*rig2) << "\n";
            auto lef3 = irid.next();
            std::cout << lef3 << " = and " << lef1 << ", " << lef2 << "\n";
            return std::unique_ptr<std::string>(new std::string(lef3));
        }
        int Eval() const override {
            return (lAndExp->Eval()) && (eqExp->Eval());
        }
};
class LOrExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lAndExp;
        std::unique_ptr<std::string> Dump() const override {
            return lAndExp->Dump(); 
        }
        int Eval() const override {
            return lAndExp->Eval();
        }
};
class LOrExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lAndExp1;
        std::unique_ptr<BaseAST> lAndExp2;
        std::unique_ptr<std::string> Dump() const override {
            auto rig = *thrOp(lAndExp1, lAndExp2, "|");
            auto lef = irid.next();
            std::cout << lef << " = ne 0, " << rig << "\n";
            return std::unique_ptr<std::string>(new std::string(lef));
        }
        int Eval() const override {
            return (lAndExp1->Eval()) || (lAndExp2->Eval());
        }
};