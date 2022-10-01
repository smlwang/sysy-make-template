%code requires {
    #include<memory>
    #include<string>
    #include"../include/ast/ast.hpp"
}

%{
    #include<iostream>
    #include<memory>
    #include<string>
    #include"../include/ast/ast.hpp"
    int yylex();
    void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);
    using namespace std;
%}

%parse-param {std::unique_ptr<BaseAST> &ast}

%union {
    std::string *str_val;
    int int_val;
    BaseAST *ast_val;
}
%token INT RETURN
%token <str_val> IDENT MUL ADD
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt 
%type <ast_val> Exp PrimaryExp UnaryExp AddExp MulExp
%type <int_val> Number
%type <str_val> UnaryOp

%%
CompUnit
    : FuncDef{
        auto comp_unit = make_unique<CompUnitAST>();
        comp_unit->func_def = unique_ptr<BaseAST>($1);
        ast = move(comp_unit);
    }
    ;
FuncDef
    : FuncType IDENT '(' ')' Block {
        auto ast = new FuncDefAST();
        ast->func_type = unique_ptr<BaseAST>($1);
        ast->ident = *unique_ptr<string>($2);
        ast->block = unique_ptr<BaseAST>($5);
        $$ = ast;
    }
    ;
FuncType
    : INT {
        auto ast = new FuncTypeAST();
        ast->ident = *unique_ptr<string>(new string("int"));
        $$ = ast;
    }
    ;
Block
    : '{' Stmt '}' {
        auto ast = new BlockAST();
        ast->stmt = unique_ptr<BaseAST>($2);
        $$ = ast;
    }
    ;
Stmt
    : RETURN Exp ';' {
        auto ast = new StmtAST();
        ast->exp = unique_ptr<BaseAST>($2);
        $$ = ast;
    }
    ;
Exp
    : AddExp {
        auto ast = new ExpAST();
        ast->addExp = unique_ptr<BaseAST>($1);
        $$ = ast; 
    }
    ;
PrimaryExp
    : '(' Exp ')' {
        auto ast = new PrimaryExp1();
        ast->exp = unique_ptr<BaseAST>($2);
        $$ = ast;
    }
    | Number {
        auto ast = new PrimaryExp2();
        ast->number = *unique_ptr<string>(new string(to_string($1)));
        $$ = ast;
    }
    ;
UnaryExp
    : PrimaryExp {
        auto ast = new UnaryExp1();
        ast->primaryExp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | UnaryOp UnaryExp {
        auto ast = new UnaryExp2();
        ast->unaryOp = *unique_ptr<string>($1);
        ast->unaryExp = unique_ptr<BaseAST>($2);
        $$ = ast;
    }
    ;
UnaryOp
    : ADD {
        $$ = $1;
    }
    | '!' {
        $$ = new string("!");
    }
AddExp
    : MulExp {
        auto ast = new AddExp1();
        ast->mulExp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | AddExp ADD MulExp {
        auto ast = new AddExp2();
        ast->addExp = unique_ptr<BaseAST>($1);
        ast->add = *unique_ptr<string>($2);
        ast->mulExp = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    ;
MulExp
    : UnaryExp {
        auto ast = new MulExp1();
        ast->unaryExp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | MulExp MUL UnaryExp {
        auto ast = new MulExp2();
        ast->mulExp = unique_ptr<BaseAST>($1);
        ast->mul = *unique_ptr<string>($2);
        ast->unaryExp = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    ;
Number
    : INT_CONST {
        $$ = $1;
    }
    ;
%%
void yyerror(unique_ptr<BaseAST> &ast, const char *s){
    cerr << "error: " << s << endl;
}