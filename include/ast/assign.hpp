#pragma once
#include "def.hpp"
class DeclAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> decl;
    std::unique_ptr<std::string> Dump() const override {
        decl->Dump();
        return nullptr;
    }
    int Eval() const override { return 0; }
};
class ConstDeclAST : public BaseAST {
public:
    std::string bType; // 无用
    std::vector<BaseAST *> constDef;
    std::unique_ptr<std::string> Dump() const override {
        for (int i = 0; i < constDef.size(); i++)
            constDef[i]->Dump();
        return nullptr;
    }
    int Eval() const override { return 0; }
};
class ConstInitValAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> constExp;
    std::unique_ptr<std::string> Dump() const override { return nullptr; }
    int Eval() const override { return constExp->Eval(); }
};
class ConstDefAST : public BaseAST {
public:
    std::string ident;
    std::unique_ptr<BaseAST> constInitVal;
    std::unique_ptr<std::string> Dump() const override {
        int val = constInitVal->Eval();
        block_symbol.const_def(ident, val);
        return nullptr;
    }
    int Eval() const override { return 0; }
};
class ConstExpAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<std::string> Dump() const override { return nullptr; }
    int Eval() const override { return exp->Eval(); }
};
class InitValAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<std::string> Dump() const override { return exp->Dump(); }
    int Eval() const override { return exp->Eval(); }
};

class VarDeclAST : public BaseAST {
public:
    std::string bType;
    std::vector<BaseAST *> varDef;
    std::unique_ptr<std::string> Dump() const override {
        for (auto def : varDef)
            def->Dump();
        return nullptr;
    }
    int Eval() const override { return 0; }
};
static std::string creatVar(const std::string &ident) {
    auto sym = block_symbol.var_def(ident);
    TextLine(sym, " = alloc i32");
    return sym;
}
class VarDef1 : public BaseAST {
public:
    std::string ident;
    std::unique_ptr<BaseAST> initVal;
    std::unique_ptr<std::string> Dump() const override {
        auto rig = initVal->Dump();
        if (global_flag) {
            auto gvar = block_symbol.global_var(ident);
            TextLine("global ", gvar, " = alloc i32, ", *rig);
        } else {
            auto lef = creatVar(ident);
            TextLine("store ", *rig, ", ", lef);
        }
        return nullptr;
    }
    int Eval() const override { return 0; }
};
class VarDef2 : public BaseAST {
public:
    std::string ident;
    std::unique_ptr<std::string> Dump() const override {
        if (global_flag) {
            auto gvar = block_symbol.global_var(ident);
            TextLine("global ", gvar, " = alloc i32, 0");
        } else {
            creatVar(ident);
        }
        return nullptr;
    }
    int Eval() const override { return 0; }
};