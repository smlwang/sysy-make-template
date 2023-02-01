#pragma once
#include "def.hpp"
#define uniqptr(x) std::unique_ptr<std::string>(new std::string(x))
// Stmt        ::= "return" Exp ";";
// Exp         ::= AddExp;
// AddExp      ::= MulExp | AddExp ("+" | "-") MulExp;
// MulExp      ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
// UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp;
// PrimaryExp  ::= "(" Exp ")" | Number;
// UnaryOp     ::= "+" | "-" | "!";
// Number      ::= INT_CONST;
static std::unique_ptr<std::string> thrOp(const std::unique_ptr<BaseAST> &l,
                                          const std::unique_ptr<BaseAST> &r,
                                          const std::string &op) {
    auto rig1 = l->Dump();
    auto rig2 = r->Dump();
    auto lef = irid.next();
    TextLine(lef, " = ", kexp[op], " ", *rig1, ", ", *rig2);
    return uniqptr(lef);
}
static int eval(const std::unique_ptr<BaseAST> &l,
                const std::unique_ptr<BaseAST> &r, const std::string &op) {
    auto a = l->Eval();
    auto b = r->Eval();
    if (op == "*")
        return a * b;
    else if (op == "/")
        return a / b;
    else if (op == "%")
        return a % b;
    else if (op == "+")
        return a + b;
    else if (op == "-")
        return a - b;
    else if (op == "==")
        return a == b;
    else if (op == "!=")
        return a != b;
    else if (op == "<=")
        return a <= b;
    else if (op == "<")
        return a < b;
    else if (op == ">=")
        return a >= b;
    else if (op == ">")
        return a > b;
    else if (op == "&&")
        return a && b;
    else if (op == "||")
        return a || b;
    return -1;
}
class ExpAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> lOrExp;
    std::unique_ptr<std::string> Dump() const override {
        return lOrExp->Dump();
        Line("");
    }
    int Eval() const override { return lOrExp->Eval(); }
};
class PrimaryExp1 : public BaseAST {
public: // ( Exp )
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<std::string> Dump() const override { return exp->Dump(); }
    int Eval() const override { return exp->Eval(); }
};
class PrimaryExp2 : public BaseAST {
public: // Number
    std::string number;
    std::unique_ptr<std::string> Dump() const override {
        return uniqptr(number);
    }
    int Eval() const override { return atoi(number.c_str()); }
};
class PrimaryExp3 : public BaseAST {
public:
    std::unique_ptr<BaseAST> lVal; // exp里的左值才需要取值
    std::unique_ptr<std::string> Dump() const override {
        auto lval = lVal->Dump();
        if ((*lval)[0] == '@')
            return uniqptr(LoadIdent(*lval));
        return lval;
    }
    int Eval() const override { return lVal->Eval(); }
};
class LValAST : public BaseAST {
public:
    std::string ident;
    std::unique_ptr<std::string> Dump() const override {
        auto val = block_symbol.qruey(ident);
        if (val.flag == SymbolTalbe::TYPE::CONST) {
            return uniqptr(std::to_string(block_symbol.to_const(val)));
        }
        return uniqptr(block_symbol.to_var(val));
    }
    int Eval() const override {
        return block_symbol.to_const(block_symbol.qruey(ident));
    }
};
class UnaryExp1 : public BaseAST {
public: // PrimaryExp
    std::unique_ptr<BaseAST> primaryExp;
    std::unique_ptr<std::string> Dump() const override {
        return primaryExp->Dump();
    }
    int Eval() const override { return primaryExp->Eval(); }
};
class UnaryExp2 : public BaseAST {
public: // UnaryOp UnaryExp
    std::string unaryOp;
    std::unique_ptr<BaseAST> unaryExp;
    std::unique_ptr<std::string> Dump() const override {
        if (unaryOp == "+")
            return unaryExp->Dump();
        auto rig = unaryExp->Dump();
        auto lef = irid.next();
        std::string alter = lef + " = ";
        if (unaryOp == "!") {
            alter += "eq 0, ";
        } else if (unaryOp == "-") {
            alter += "sub 0, ";
        }
        alter += *rig;
        TextLine(alter);
        return std::unique_ptr<std::string>(new std::string(lef));
    }
    int Eval() const override {
        auto a = unaryExp->Eval();
        if (unaryOp == "+")
            return a;
        else if (unaryOp == "-")
            return -a;
        return !a;
    }
};

class UnaryExp3 : public BaseAST {
public: // func(1, 3);
    std::string ident;
    std::vector<BaseAST *> funcRParams;
    std::unique_ptr<std::string> Dump() const override { 
        std::vector<std::string> params;
        for (auto v : funcRParams) {
            auto param = LoadIdent(*v->Dump());
            params.emplace_back(param);
        }
        std::string res = "";
        if (funcType.count(ident)) {
            res = irid.next();
            TextOut(res, " = call @", ident, "(");
        } else {
            TextOut("call @", ident, "(");
        }
        int siz = params.size();
        for (int i = 0; i < siz; i++) {
            if (i) Out(", ");
            Out(params[i]);
        }
        Out(")\n");
        if (res != "") return uniqptr(res);
        return nullptr; 
    }
    int Eval() const override { return 0; }
};
class AddExp1 : public BaseAST {
public:
    std::unique_ptr<BaseAST> mulExp;
    std::unique_ptr<std::string> Dump() const override {
        return mulExp->Dump();
    }
    int Eval() const override { return mulExp->Eval(); }
};
class AddExp2 : public BaseAST {
public:
    std::unique_ptr<BaseAST> addExp;
    std::string add; // + -
    std::unique_ptr<BaseAST> mulExp;
    std::unique_ptr<std::string> Dump() const override {
        return thrOp(addExp, mulExp, add);
    }
    int Eval() const override { return eval(addExp, mulExp, add); }
};

class MulExp1 : public BaseAST {
public:
    std::unique_ptr<BaseAST> unaryExp;
    std::unique_ptr<std::string> Dump() const override {
        return unaryExp->Dump();
    }
    int Eval() const override { return unaryExp->Eval(); }
};
class MulExp2 : public BaseAST {
public:
    std::unique_ptr<BaseAST> mulExp;
    std::string mul; // * / %
    std::unique_ptr<BaseAST> unaryExp;
    std::unique_ptr<std::string> Dump() const override {
        return thrOp(mulExp, unaryExp, mul);
    }
    int Eval() const override { return eval(mulExp, unaryExp, mul); }
};
class RelExp1 : public BaseAST {
public:
    std::unique_ptr<BaseAST> addExp;
    std::unique_ptr<std::string> Dump() const override {
        return addExp->Dump();
    }
    int Eval() const override { return addExp->Eval(); }
};
class RelExp2 : public BaseAST {
public:
    std::unique_ptr<BaseAST> relExp;
    std::string rel; // <= < > >=
    std::unique_ptr<BaseAST> addExp;
    std::unique_ptr<std::string> Dump() const override {
        return thrOp(relExp, addExp, rel);
    }
    int Eval() const override { return eval(relExp, addExp, rel); }
};
class EqExp1 : public BaseAST {
public:
    std::unique_ptr<BaseAST> relExp;
    std::unique_ptr<std::string> Dump() const override {
        return relExp->Dump();
    }
    int Eval() const override { return relExp->Eval(); }
};
class EqExp2 : public BaseAST {
public:
    std::unique_ptr<BaseAST> eqExp;
    std::string eq; // !=  ==
    std::unique_ptr<BaseAST> relExp;
    std::unique_ptr<std::string> Dump() const override {
        return thrOp(eqExp, relExp, eq);
    }
    int Eval() const override { return eval(eqExp, relExp, eq); }
};
class LAndExp1 : public BaseAST {
public:
    std::unique_ptr<BaseAST> eqExp;
    std::unique_ptr<std::string> Dump() const override { return eqExp->Dump(); }
    int Eval() const override { return eqExp->Eval(); }
};
class LAndExp2 : public BaseAST {
public:
    std::unique_ptr<BaseAST> lAndExp;
    std::unique_ptr<BaseAST> eqExp;
    std::unique_ptr<std::string> Dump() const override {
        bid.new_branch(BranchIdGenerator::LAND);
        auto res = bid.alloc();
        TextLine(res, " = alloc i32");

        // lhs
        auto rig1 = lAndExp->Dump();
        auto tmp = irid.next();
        TextLine(tmp, " = ne 0, ", *rig1);
        TextLine("store ", tmp, ", ", res);
        TextLine("br ", tmp, ", ", bid.bthen(), ", ", bid.bend());
        Line("");

        // rhs
        LabelOut(bid.bthen());
        auto rig2 = eqExp->Dump();
        tmp = irid.next();
        TextLine(tmp, " = ne 0, ", *rig2);
        TextLine("store ", tmp, ", ", res);
        TextLine("jump ", bid.bend());
        Line("");

        LabelOut(bid.bend());
        bid.end_branch();
        auto t = irid.next();
        TextLine(t, " = load ", res);
        res = t;
        return uniqptr(res);
    }
    int Eval() const override { return (lAndExp->Eval()) && (eqExp->Eval()); }
};
class LOrExp1 : public BaseAST {
public:
    std::unique_ptr<BaseAST> lAndExp;
    std::unique_ptr<std::string> Dump() const override {
        return lAndExp->Dump();
    }
    int Eval() const override { return lAndExp->Eval(); }
};
class LOrExp2 : public BaseAST {
public:
    std::unique_ptr<BaseAST> lAndExp1;
    std::unique_ptr<BaseAST> lAndExp2;
    std::unique_ptr<std::string> Dump() const override {
        bid.new_branch(BranchIdGenerator::LOR);
        auto res = bid.alloc();
        TextLine(res, " = alloc i32");

        // lhs
        auto rig1 = lAndExp1->Dump();
        auto tmp = irid.next();
        TextLine(tmp, " = ne 0, ", *rig1);
        TextLine("store ", tmp, ", ", res);
        TextLine("br ", tmp, ", ", bid.bend(), ", ", bid.bthen());
        Line("");

        // rhs
        LabelOut(bid.bthen());
        auto rig2 = lAndExp2->Dump();
        tmp = irid.next();
        TextLine(tmp, " = ne 0, ", *rig2);
        TextLine("store ", tmp, ", ", res);
        TextLine("jump ", bid.bend());
        Line("");

        LabelOut(bid.bend());

        auto t = irid.next();
        TextLine(t, " = load ", res);
        res = t;
        bid.end_branch();
        return uniqptr(res);
    }
    int Eval() const override {
        return (lAndExp1->Eval()) || (lAndExp2->Eval());
    }
};