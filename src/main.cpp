#include<iostream>
#include<cstdio>
#include<cassert>
#include<memory>
#include"../include/ast.hpp"
#include<string>
using namespace std;

extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAST> &ast);

int main(int argc, char const *argv[])
{
    assert(argc == 5);
    auto mod = argv[1];
    auto input = argv[2];
    auto output = argv[4];

    yyin = fopen(input, "r");
    assert(yyin);

    unique_ptr<BaseAST> ast;
    auto ret = yyparse(ast);
    assert(!ret);
    freopen(output, "w", stdout);
    ast->Dump();
    cout << endl;
    fclose(stdout);
    return 0;
}
