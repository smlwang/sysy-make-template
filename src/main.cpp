#include<iostream>
#include<cstdio>
#include<cassert>
#include<sstream>
#include<memory>
#include"../include/koopa/koopa.h"
#include"../include//koopa/kvis.hpp"
#include"../include/ast/ast.hpp"
#include<string>
using namespace std;

extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAST> &ast);
void dealIR(const stringstream &buf){
    koopa_program_t program;
    koopa_error_code_t ret = koopa_parse_from_string(buf.str().c_str(), &program);
    std::cout << std::endl;
    assert(ret == KOOPA_EC_SUCCESS);
    koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
    koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
    koopa_delete_program(program);
    Visit(raw);
    koopa_delete_raw_program_builder(builder);
}
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
    cout << string(mod);
    freopen(output, "w", stdout);
    stringstream buf;
    streambuf *old = cout.rdbuf(buf.rdbuf()); 
    ast->Dump();
    cout.rdbuf(old);
    if(string(mod) == "-koopa"s){
        cout << buf.str() << endl;
        return 0;
    }
    dealIR(buf);
    fclose(stdout);
    return 0;
}
