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
        int Eval() const override { return 0; }
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
        int Eval() const override { return 0; }
};
class FuncTypeAST : public BaseAST {
    public:
        std::string ident;
        std::unique_ptr<std::string> Dump() const override {
            if(ident == "int") std::cout << "i32";
            else std::cout << ident;
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class BlockAST : public BaseAST {
    public:
        std::vector<BaseAST*> blockItems;
        std::unique_ptr<std::string> Dump() const override {
            irid.in();
            std::cout << "{\n";
            std::cout << "%entry:\n";
            for(int i = 0; i < blockItems.size(); i++)
                blockItems[i]->Dump();
            std::cout << "}";
            irid.out();
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class BlockItemAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> item;
        std::unique_ptr<std::string> Dump() const override {
            item->Dump();
            return nullptr;
        }
        int Eval() const override { return 0; }
};
// class BItem2 : public BaseAST {
//     public:
//         std::unique_ptr<BaseAST> stmt;
//         std::unique_ptr<std::string> Dump() const override {
//             stmt->Dump();
//             return nullptr;
//         }
//         int Eval() const override { return 0; }
// };
class Stmt1 : public BaseAST {
    public: // return exp;
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
            auto ret = exp->Dump();
            std::cout << "ret " << (*ret) << std::endl;
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class Stmt2 : public BaseAST {
    public: // lVal = exp;
        std::unique_ptr<BaseAST> lVal;
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
            return nullptr;
        }
        int Eval() const override { return 0; }
};