#pragma once
#include "def.hpp"
// CompUnit  ::= FuncDef;

// FuncDef   ::= FuncType IDENT "(" ")" Block;
// FuncType  ::= "int";

// Block     ::= "{" Stmt "}";
// Stmt      ::= "return" Exp ";";

// Number    ::= INT_CONST;
// bool pre_ret = 0;

class CompUnitFuncAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_def;
    std::unique_ptr<std::string> Dump() const override {
        func_def->Dump();
        return nullptr;
    }
    int Eval() const override { return 0; }
};


class CompUnitDeclAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> global_def;
    std::unique_ptr<std::string> Dump() const override {
        global_flag = true;
        global_def->Dump();
        global_flag = false;
        return nullptr;
    }
    int Eval() const override { return 0; }
};

class CompUnitAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> cur_def;
    std::unique_ptr<BaseAST> compUnit;
    std::unique_ptr<std::string> Dump() const override {
        compUnit->Dump();
        cur_def->Dump();
        return nullptr;
    }
    int Eval() const override { return 0; }
};
class FuncDefAST : public BaseAST {
public:
    std::string func_type;
    std::string ident;
    std::vector<std::string *> funcFParams;
    std::unique_ptr<BaseAST> block;
    std::unique_ptr<std::string> Dump() const override {
        block_symbol.step_in_block();
        rets.in();

        Out("fun @", ident, '(');
        if (funcFParams.size()) {
            int siz = funcFParams.size();
            for (int i = 0; i < siz; i++) {
                std::string param = *funcFParams[i];
                block_symbol.param_def(param);
                if (i) Out(", ");
                Out("%", param, ": i32");
            }
        }
        Out(')');

        if (func_type == "int") {
            funcType[ident] = 1;
            Out(": i32");
        }
        Out(" {\n");
        LabelOut("%entry");

        block->Dump();
        if (!rets.retruned()) {
            rets.ret();
            if (func_type == "void") {
                TextLine("ret");
            } else {
                assert(ident == "main");
                TextLine("ret 0");
            }
        }
        Line("}");
        Line("");
        rets.out();
        block_symbol.step_out_block();
        return nullptr;
    }
    int Eval() const override { return 0; }
};

class BlockAST : public BaseAST {
public:
    std::vector<BaseAST *> blockItems;
    std::unique_ptr<std::string> Dump() const override {
        for (int i = 0; i < blockItems.size(); i++) {
            blockItems[i]->Dump();
        }
        return nullptr;
    }
    int Eval() const override { return 0; }
};
class BlockItemAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> item;
    std::unique_ptr<std::string> Dump() const override {
        if (item != nullptr)
            item->Dump();
        return nullptr;
    }
    int Eval() const override { return item->Eval(); }
};

class Stmt1 : public BaseAST {
public: // return exp;
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<std::string> Dump() const override {
        if (rets.size()) {
            if (rets.retruned())
                return nullptr;
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
class StmtNull : public BaseAST {
public:
    std::unique_ptr<std::string> Dump() const override { 
        if (rets.size()) {
            if (rets.retruned())
                return nullptr;
            rets.ret();
            TextLine("ret");
        }
        return nullptr; 
    }
    int Eval() const override { return 0; }
};
class Stmt2 : public BaseAST {
public: // lVal = exp;
    std::unique_ptr<BaseAST> lVal;
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<std::string> Dump() const override {
        if (rets.retruned())
            return nullptr;
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
        if (rets.retruned())
            return nullptr;
        if (block != nullptr) {
            block_symbol.step_in_block();
            block->Dump();
            block_symbol.step_out_block();
        }
        return nullptr;
    }
    int Eval() const override { return block->Eval(); }
};
class Stmt4 : public BaseAST {
public:
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<std::string> Dump() const override {
        if (rets.retruned())
            return nullptr;
        if (exp != nullptr)
            exp->Dump();
        return nullptr;
    }
    int Eval() const override { return 0; }
};

class Stmt5 : public BaseAST {
public: // if (exp) stmt
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<BaseAST> stmt;
    std::unique_ptr<std::string> Dump() const override {
        if (rets.retruned())
            return nullptr;
        bid.new_branch(BranchIdGenerator::IF);
        auto e = *exp->Dump();

        TextLine("br ", e, ", ", bid.bthen(), ", ", bid.bend());

        Line("");
        LabelOut(bid.bthen());
        rets.in();
        stmt->Dump();
        if (!rets.retruned())
            TextLine("jump ", bid.bend());
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
        if (rets.retruned())
            return nullptr;
        bid.new_branch(BranchIdGenerator::IF);
        auto e = *exp->Dump();
        rets.ret();
        TextLine("br ", e, ", ", bid.bthen(), ", ", bid.belse());

        Line("");
        LabelOut(bid.bthen());
        rets.in();
        stmt->Dump();
        if (!rets.retruned())
            TextLine("jump ", bid.bend());
        rets.out();

        Line("");
        LabelOut(bid.belse());
        rets.in();
        estmt->Dump();
        if (!rets.retruned())
            TextLine("jump ", bid.bend());
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
        if (rets.retruned())
            return nullptr;
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