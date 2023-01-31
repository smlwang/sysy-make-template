#pragma once
#include "branch_id.hpp"
#include"def.hpp"
// CompUnit  ::= FuncDef;

// FuncDef   ::= FuncType IDENT "(" ")" Block;
// FuncType  ::= "int";

// Block     ::= "{" Stmt "}";
// Stmt      ::= "return" Exp ";";

// Number    ::= INT_CONST;
// bool pre_ret = 0;

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
            Out("fun @", ident, "(): ");
            func_type->Dump();
            Out(" ");
            block->Dump();
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class FuncTypeAST : public BaseAST {
    public:
        std::string ident;
        std::unique_ptr<std::string> Dump() const override {
            if(ident == "int") Out("i32");
            else Out(ident);
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class BlockAST : public BaseAST {
    public:
        std::vector<BaseAST*> blockItems;
        std::unique_ptr<std::string> Dump() const override {
            std::unique_ptr<std::string> ret = nullptr;
            block_symbol.step_in_block();
            if (block_symbol.depth() == 1) {
                Line("{");
                Line("");
                LabelOut("%entry");
                rets.in();
            }
            for(int i = 0; i < blockItems.size(); i++) {
                auto t = blockItems[i]->Dump();
            }
            if (block_symbol.depth() == 1) {
                Line("}");
                rets.out();
            }
            block_symbol.step_out_block();
            return nullptr;
        }
        int Eval() const override { 
            return 0;
        }
};
class BlockItemAST : public BaseAST {
    public:
        std::unique_ptr<BaseAST> item;
        std::unique_ptr<std::string> Dump() const override {
            if (item != nullptr) item->Dump();
            return nullptr;
        }
        int Eval() const override { return item->Eval(); }
};

class Stmt1 : public BaseAST {
    public: // return exp;
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
            if (rets.size()) {
                if (rets.retruned()) return nullptr;
                rets.ret();
            }

            if (exp == nullptr) {
                TextLine("ret");
                return nullptr;
            }
            auto ret = exp->Dump();
            TextLine("ret ", *ret);
            return nullptr;
        }
        int Eval() const override { return -1; }
};
class Stmt2 : public BaseAST {
    public: // lVal = exp;
        std::unique_ptr<BaseAST> lVal;
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
            if (rets.retruned()) return nullptr;
            auto lef = lVal->Dump();
            auto rig = exp->Dump();
            TextLine("store ", *rig, ", ", *lef);
            return nullptr;
        }
        int Eval() const override { return 0; }
};

class Stmt3 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> block;
        std::unique_ptr<std::string> Dump() const override {
            if (rets.retruned()) return nullptr;
            if (block != nullptr) block->Dump();
            return nullptr;
        }
        int Eval() const override { return block->Eval(); }
};
class Stmt4 : public BaseAST {
    public:
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<std::string> Dump() const override {
            if (rets.retruned()) return nullptr;
            if (exp != nullptr) exp->Dump();
            return nullptr;
        }
        int Eval() const override { return 0; }
};

class StmtNull : public BaseAST {
    public:
        std::unique_ptr<std::string> Dump() const override {
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class Stmt5 : public BaseAST {
    public: // if (exp) stmt
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<BaseAST> stmt;
        std::unique_ptr<std::string> Dump() const override {
            if (rets.retruned()) return nullptr;
            bid.new_branch(BranchIdGenerator::IF);
            auto e = *exp->Dump();

            TextLine("br ", e, ", ", bid.bthen(), ", ", bid.bend());

            Line("");
            LabelOut(bid.bthen());
            rets.in();
            stmt->Dump();
            if (!rets.retruned()) TextLine("jump ", bid.bend());
            rets.out();

            Line("");
            LabelOut(bid.bend());
            rets.in();
            bid.end_branch();
            return nullptr;
        }
        int Eval() const override { return 0; }
};

class Stmt6 : public BaseAST {
    public: // if (exp) stmt else stmt
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<BaseAST> stmt;
        std::unique_ptr<BaseAST> estmt;
        std::unique_ptr<std::string> Dump() const override {
            if (rets.retruned()) return nullptr;
            bid.new_branch(BranchIdGenerator::IF);
            auto e = *exp->Dump();
            rets.ret();
            TextLine("br ", e, ", ", bid.bthen(), ", ", bid.belse());

            Line("");
            LabelOut(bid.bthen());
            rets.in();
            stmt->Dump();
            if (!rets.retruned()) TextLine("jump ", bid.bend());
            rets.out();

            Line("");
            LabelOut(bid.belse());
            rets.in();
            estmt->Dump();
            if (!rets.retruned()) TextLine("jump ", bid.bend());
            rets.out();

            Line("");
            LabelOut(bid.bend());

            rets.in();
            bid.end_branch();
            return nullptr;
        }
        int Eval() const override { return 0; }
};


class Break : public BaseAST {
    public:
        std::unique_ptr<std::string> Dump() const override {
            if (!rets.retruned()) {
                rets.ret();
                TextLine("jump ", bid.loop_end());
            }
            return nullptr;
        }
        int Eval() const override { return 0; }
};
class Continue : public BaseAST {
    public:
        std::unique_ptr<std::string> Dump() const override {
            if (!rets.retruned()) {
                rets.ret();
                TextLine("jump ", bid.loop_cond());
            }
            return nullptr;
        }
        int Eval() const override { return 0; }
};

class While : public BaseAST {
    public:
        std::unique_ptr<BaseAST> exp;
        std::unique_ptr<BaseAST> stmt;
        std::unique_ptr<std::string> Dump() const override {
            if (rets.retruned()) return nullptr;
            bid.new_branch(BranchIdGenerator::WHILE);
            rets.ret();
            TextLine("jump ", bid.loop_cond());
            Line("");
            LabelOut(bid.loop_cond());
            rets.in();
            auto cond = *exp->Dump();
            if (cond[0] == '@') {
                auto t = irid.next();
                TextLine(t, " = load ", cond);
                cond = t;
            }
            if (!rets.retruned()) {
                TextLine("br ", cond, ", ", bid.loop_start(), ", ", bid.loop_end());
            }
            rets.out();

            Line("");
            LabelOut(bid.loop_start());
            rets.in();
            stmt->Dump();
            if (!rets.retruned()) {
                TextLine("jump ", bid.loop_cond());
            }
            rets.out();

            Line("");
            LabelOut(bid.loop_end());
            rets.in();
            bid.end_branch();
            return nullptr;
        }
        int Eval() const override { return 0; }
};