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

inline std::unique_ptr<std::string> thrOp(const std::unique_ptr<BaseAST> &l,\
                const std::unique_ptr<BaseAST> &r,\
                const std::string &op){
        auto rig1 = l->Dump();
        auto rig2 = r->Dump();
        auto lef = unaryid.next();
        std::cout << lef << " = " << kexp[op] << " ";
        std::cout << (*rig1) << ", " << (*rig2) << "\n"; 
        return std::unique_ptr<std::string>(new std::string(lef));
}
class ExpAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lOrExp;
        std::unique_ptr<std::string> Dump() const override {
           return lOrExp->Dump();
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
        std::string add; // + -
        std::unique_ptr<BaseAST> mulExp;
        std::unique_ptr<std::string> Dump() const override {
            return thrOp(addExp, mulExp, add);
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
        std::string mul; // * / %
        std::unique_ptr<BaseAST> unaryExp;
        std::unique_ptr<std::string> Dump() const override {
            return thrOp(mulExp, unaryExp, mul);
        }
};
class RelExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> addExp;
        std::unique_ptr<std::string> Dump() const override {
            return addExp->Dump();
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
};
class EqExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> relExp;
        std::unique_ptr<std::string> Dump() const override {
            return relExp->Dump();    
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
};
class LAndExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> eqExp;
        std::unique_ptr<std::string> Dump() const override {
            return eqExp->Dump();    
        }
};
class LAndExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lAndExp;
        std::unique_ptr<BaseAST> eqExp;
        std::unique_ptr<std::string> Dump() const override {
            auto rig1 = lAndExp->Dump();
            auto rig2 = eqExp->Dump();
            auto lef1 = unaryid.next();
            std::cout << lef1 << " = ne 0, " << (*rig1) << "\n";
            auto lef2 = unaryid.next();
            std::cout << lef2 << " = ne 0, " << (*rig1) << "\n";
            auto lef3 = unaryid.next();
            std::cout << lef3 << " = and " << lef1 << ", " << lef2 << "\n";
            return std::unique_ptr<std::string>(new std::string(lef3));
        }
};
class LOrExp1 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lAndExp;
        std::unique_ptr<std::string> Dump() const override {
            return lAndExp->Dump(); 
        }
};
class LOrExp2 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> lAndExp1;
        std::unique_ptr<BaseAST> lAndExp2;
        std::unique_ptr<std::string> Dump() const override {
            auto rig = *thrOp(lAndExp1, lAndExp2, "|");
            auto lef = unaryid.next();
            std::cout << lef << " = ne 0, " << rig << "\n";
            return std::unique_ptr<std::string>(new std::string(lef));
        }
};