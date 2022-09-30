%code requires {
    #include<memory>
    #include<string>
    #include"../include/ast.hpp"
}

%{
    #include<iostream>
    #include<memory>
    #include<string>
    #include"../include/ast.hpp"
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
%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt Number

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
    : RETURN Number ';' {
        auto ast = new StmtAST();
        ast->number = unique_ptr<BaseAST>($2);
        $$ = ast;
    }
    ;
Number
    : INT_CONST {
        auto ast = new NumberAST();
        ast->number = *unique_ptr<string>(new string(to_string($1)));
        $$ = ast;
    }
    ;
%%
void yyerror(unique_ptr<BaseAST> &ast, const char *s){
    cerr << "error: " << s << endl;
}