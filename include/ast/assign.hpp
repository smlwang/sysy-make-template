#pragma once
#include"def.hpp"
class DeclAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> constDecl;
        std::unique_ptr<std::string> Dump() const override {
            constDecl->Dump();
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class ConstDeclAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> bType;// 无用
        std::vector<BaseAST*> constDef;
        std::unique_ptr<std::string> Dump() const override {
            for(int i = 0; i < constDef.size(); i++)
                constDef[i]->Dump();
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class BTypeAST : public BaseAST {
    public:
        std::string bType;
        std::unique_ptr<std::string> Dump() const override {
            return nullptr;
        }
        int Eval() const override { return 0; }
        
};
class ConstInitValAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> constExp;
        std::unique_ptr<std::string> Dump() const override {
            return nullptr;
        }
        int Eval() const override { return constExp->Eval(); }
};
class ConstDefAST : public BaseAST {
    public:
        std::string ident;
        std::unique_ptr<BaseAST> constInitval;
        std::unique_ptr<std::string> Dump() const override {
            int val = constInitval->Eval();
            constSymbol.add(ident, val);
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class ConstExpAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
            return nullptr;
        }
        int Eval() const override { return exp->Eval(); }
};