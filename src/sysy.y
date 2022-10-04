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
%token INT RETURN CONST
%token <str_val> IDENT MUL ADD EQ REL LAND LOR
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block BlockItem Stmt 
%type <ast_val> Exp PrimaryExp UnaryExp AddExp MulExp LOrExp RelExp EqExp LAndExp
%type <ast_val> Decl ConstDecl BType ConstDef ConstExp ConstInitVal LVal 
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
    : LOrExp {
        auto ast = new ExpAST();
        ast->lOrExp = unique_ptr<BaseAST>($1);
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
    | LVal {
        auto ast = new PrimaryExp3();
        ast->lVal = unique_ptr<BaseAST>($1);
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
    ;
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
RelExp
    : AddExp {
        auto ast = new RelExp1();
        ast->addExp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | RelExp REL AddExp {
        auto ast = new RelExp2();
        ast->relExp = unique_ptr<BaseAST>($1);
        ast->rel = *unique_ptr<string>($2);
        ast->addExp = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    ;
EqExp
    : RelExp {
        auto ast = new EqExp1();
        ast->relExp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | EqExp EQ RelExp {
        auto ast = new EqExp2();
        ast->eqExp = unique_ptr<BaseAST>($1);
        ast->eq = *unique_ptr<string>($2);
        ast->relExp = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    ;
LAndExp
    : EqExp {
        auto ast = new LAndExp1();
        ast->eqExp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | LAndExp LAND EqExp {
        auto ast = new LAndExp2();
        ast->lAndExp = unique_ptr<BaseAST>($1);
        ast->eqExp = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    ;
LOrExp
    : LAndExp {
        auto ast = new LOrExp1();
        ast->lAndExp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | LAndExp LOR LAndExp{
        auto ast = new LOrExp2();
        ast->lAndExp1 = unique_ptr<BaseAST>($1);
        ast->lAndExp2 = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
Decl
    : ConstDecl {
        auto ast = new DeclAST();
        ast->constDecl = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    ;
ConstDecl
    : CONST BType ConstDef ';' {

    }
    ;
ConstDefs
    : 
ConstDef
    : IDENT '=' ConstInitVal {
        auto ast = new ConstDefAST();
        ast->ident = *unique_ptr<string>($1);
        ast->constInitval = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    ;
ConstInitVal
    : ConstExp {
        auto ast = new ConstInitValAST();
        ast->decl = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    ;
BlockItem
    : Decl {
        auto ast = new BItem1();
        ast->decl = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | Stmt {
        auto ast = new BItem2();
        ast->stmt = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    ;
LVal
    : IDENT {
        auto ast = new LValAST();
        ast->ident = *unique_ptr<string>($1);
        $$ = ast;
    }
    ;
ConstExp
    : Exp {
        auto ast = new ConstExpAST();
        ast->exp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    ;
%%
void yyerror(unique_ptr<BaseAST> &ast, const char *s){
    cerr << "error: " << s << endl;
}