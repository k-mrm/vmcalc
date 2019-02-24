#include "vmcalc.h"

Token Lexer::run(std::string src) {
    Token token;

    for(unsigned int i = 0; i < src.size(); i++) {
        if(isdigit(src[i])) {
            std::string value_num;

            for(; isdigit(src[i]);i++) {
                value_num += src[i];
            }

            --i;
            token.push_number(value_num);
        }
        else if(src[i] == '+' || src[i] == '-' || src[i] == '*' || src[i] == '/' ||
                src[i] == '(' || src[i] == ')') {
            std::string value;
            value = src[i];
            if(src[i + 1] == '=') {
                i++;
                value += src[i];
            }

            token.push_symbol(value);
        }
        else if(isblank(src[i])) {
            continue;
        }
        else if(src[i] == '\n') {
            continue;
        }
        else {
            fprintf(stderr, "invalid syntax: \" %c \"", src[i]);
            //exit(1);
        }
    }
    token.push_end();

    return token;
}
