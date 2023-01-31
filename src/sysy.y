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
    std::vector<BaseAST*> *arr_val;
}
%token INT RETURN CONST IF ELSE
%token WHILE CONTINUE BREAK
%token <str_val> IDENT MUL ADD EQ REL LAND LOR
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt BlockItem
%type <ast_val> Exp PrimaryExp UnaryExp AddExp MulExp LOrExp RelExp EqExp LAndExp
%type <ast_val> Decl ConstDecl VarDecl BType ConstDef VarDef ConstExp ConstInitVal InitVal LVal
%type <arr_val> ConstDefs VarDefs BlockItems
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
    : '{' '}' {
        auto ast = new BlockAST();
        ast->blockItems = vector<BaseAST*>({});
        $$ = ast;
    }
    | '{' BlockItems '}' {
        auto ast = new BlockAST();
        ast->blockItems = *unique_ptr<vector<BaseAST*>>($2);
        $$ = ast;
    }
    ;
BlockItems
    : BlockItem {
        auto arr = new vector<BaseAST*>();
        (*arr).push_back($1);
        $$ = arr;
    }
    | BlockItems BlockItem {
        (*$1).push_back($2);
        $$ = $1; 
    }
    ;
BlockItem
    : Decl {
        auto ast = new BlockItemAST();
        ast->item = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | Stmt {
        auto ast = new BlockItemAST();
        ast->item = unique_ptr<BaseAST>($1);
        $$ = ast;
    } 
    ;
Stmt
    : LVal '=' Exp ';' {
        auto ast = new Stmt2();
        ast->lVal = unique_ptr<BaseAST>($1);
        ast->exp = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    | ';' {
        auto ast = new Stmt4();
        ast->exp = unique_ptr<BaseAST>(nullptr);
        $$ = ast;
    }
    | Exp ';' {
        auto ast = new Stmt4();
        ast->exp = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | Block {
        auto ast = new Stmt3();
        ast->block = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | RETURN ';' {
        auto ast = new StmtNull();
        $$ = ast;
    }
    | RETURN Exp ';' {
        auto ast = new Stmt1();
        ast->exp = unique_ptr<BaseAST>($2);
        $$ = ast;
    }
    | IF '(' Exp ')' Stmt {
        auto ast = new Stmt5();
        ast->exp = unique_ptr<BaseAST>($3);
        ast->stmt = unique_ptr<BaseAST>($5);
        $$ = ast;
    }
    | IF '(' Exp ')' Stmt ELSE Stmt {
        auto ast = new Stmt6();
        ast->exp = unique_ptr<BaseAST>($3);
        ast->stmt = unique_ptr<BaseAST>($5);
        ast->estmt = unique_ptr<BaseAST>($7);
        $$ = ast;
    }
    | WHILE '(' Exp ')' Stmt {
        auto ast = new While();
        ast->exp = unique_ptr<BaseAST>($3);
        ast->stmt = unique_ptr<BaseAST>($5);
        $$ = ast;
    }
    | BREAK {
        auto ast = new Break();
        $$ = ast;
    }
    | CONTINUE {
        auto ast = new Continue();
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
    ;
Decl
    : ConstDecl {
        auto ast = new DeclAST();
        ast->decl = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    | VarDecl {
        auto ast = new DeclAST();
        ast->decl = unique_ptr<BaseAST>($1);
        $$ = ast;
    }
    ;
ConstDecl
    : CONST BType ConstDefs ';' {
        auto ast = new ConstDeclAST();
        ast->bType = unique_ptr<BaseAST>($2);
        ast->constDef = *unique_ptr<vector<BaseAST*>>($3);
        $$ = ast;
    }
    ;
ConstDefs
    : ConstDef {
        $$ = new vector<BaseAST*>({($1)});
    }
    | ConstDefs ',' ConstDef {
        (*$1).push_back($3);
        $$ = $1;
    }
    ;
ConstDef
    : IDENT '=' ConstInitVal {
        auto ast = new ConstDefAST();
        ast->ident = *unique_ptr<string>($1);
        ast->constInitVal = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    ;
VarDecl
    : BType VarDefs ';' {
        auto ast = new VarDeclAST();
        ast->bType = unique_ptr<BaseAST>($1);
        ast->varDef = *unique_ptr<vector<BaseAST*>>($2);
        $$ = ast;
    }
    ;
VarDefs
    : VarDef {
        $$ = new vector<BaseAST*>({($1)});
    }
    | VarDefs ',' VarDef {
        (*$1).push_back($3);
        $$ = $1;
    }
    ;
VarDef
    : IDENT '=' InitVal {
        auto ast = new VarDef1();
        ast->ident = *unique_ptr<string>($1);
        ast->initVal = unique_ptr<BaseAST>($3);
        $$ = ast;
    }
    | IDENT {
        auto ast = new VarDef2();
        ast->ident = *unique_ptr<string>($1);
        $$ = ast;
    }
    ;
InitVal
    : Exp {
        auto ast = new InitValAST();
        ast->exp = unique_ptr<BaseAST>($1);
    }
    ;
ConstInitVal
    : ConstExp {
        auto ast = new ConstInitValAST();
        ast->constExp = unique_ptr<BaseAST>($1);
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
BType
    : INT {
        auto ast = new BTypeAST();
        ast->bType = "int";
        $$ = ast;
    }
    ;
%%
void yyerror(unique_ptr<BaseAST> &ast, const char *s){
    cerr << "error: " << s << endl;
}