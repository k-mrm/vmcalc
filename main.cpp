#include "vmcalc.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        puts("error"); exit(1);
    }
    std::string src = std::string(argv[1]);
    Token token;
    Lexer lexer;
    token = lexer.run(src);
    token.show();
    Parser parser;
    AST *ast;
    ast = parser.run(token);
    parser.show(ast); puts("");
    VMcode vmcode;
    vmcode.generate(ast);
    VM vm;
    int stacktop = vm.run(vmcode.codes);
    printf("%d\n", stacktop);
}
