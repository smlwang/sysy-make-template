#pragma once
#include"def.hpp"
// CompUnit  ::= FuncDef;

// FuncDef   ::= FuncType IDENT "(" ")" Block;
// FuncType  ::= "int";

// Block     ::= "{" Stmt "}";
// Stmt      ::= "return" Exp ";";
// Number    ::= INT_CONST;
class CompUnitAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> func_def;
        std::unique_ptr<std::string> Dump() const override {
            func_def->Dump();
            return nullptr;
        }
};

class FuncDefAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> func_type;
        std::string ident;
        std::unique_ptr<BaseAST> block;
        std::unique_ptr<std::string> Dump() const override {
            std::cout << "fun @" << ident << "(): ";
            func_type->Dump();
            std::cout << " ";
            block->Dump();
            return nullptr;
        }
};
class FuncTypeAST : public BaseAST {
    public:
        std::string ident;
        std::unique_ptr<std::string> Dump() const override {
            if(ident == "int") std::cout << "i32";
            else std::cout << ident;
            return nullptr;
        }
};
class BlockAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> stmt;
        std::unique_ptr<std::string> Dump() const override {
            std::cout << "{\n";
            std::cout << "%entry:\n";
            stmt->Dump();
            std::cout << "}";
            return nullptr;
        }
};
class StmtAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
            auto ret = exp->Dump();
            std::cout << "ret " << (*ret) << std::endl;
            return nullptr;
        }
};