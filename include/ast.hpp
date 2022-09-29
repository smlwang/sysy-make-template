#include<memory>
#include<iostream>
#pragma once
class BaseAST {
    public:
        virtual ~BaseAST() = default;
        virtual void Dump() const = 0;
};
// CompUnit  ::= FuncDef;

// FuncDef   ::= FuncType IDENT "(" ")" Block;
// FuncType  ::= "int";

// Block     ::= "{" Stmt "}";
// Stmt      ::= "return" Number ";";
// Number    ::= INT_CONST;

class CompUnitAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> func_def;
        void Dump() const override {
            func_def->Dump();
        }
};

class FuncDefAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> func_type;
        std::string ident;
        std::unique_ptr<BaseAST> block;
        void Dump() const override {
            std::cout << "fun ";
            if(ident == "main") std::cout << "@";
            else std::cout << "%";
            std::cout << ident << "(): ";
            func_type->Dump();
            std::cout << " ";
            block->Dump();
        }
};
class FuncTypeAST : public BaseAST {
    public:
        std::string ident;
        void Dump() const override {
            if(ident == "int") std::cout << "i32";
            else std::cout << ident;
        }
};
class BlockAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> stmt;
        void Dump() const override {
            std::cout << "{\n";
            std::cout << "%entry:\n\t";
            stmt->Dump();
            std::cout << "}";
        }
};
class StmtAST : public BaseAST {
    public:
        std::string number;
        void Dump() const override {
            std::cout << "ret " << number << "\n";
        }
};
