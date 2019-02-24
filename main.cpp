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
}
