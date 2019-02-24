#include "vmcalc.h"

void Token::push_number(std::string value) {
    tokens.push_back((token_t){TOKEN::NUMBER, value});
}

void Token::push_symbol(std::string value) {
    tokens.push_back((token_t){TOKEN::SYMBOL, value});
}

void Token::push_end() {
    tokens.push_back((token_t){TOKEN::END, ""});
}

void Token::show() {
    std::string literal;

    for(token_t token: tokens) {
        literal = [&]() -> std::string {
            switch(token.type) {
                case TOKEN::NUMBER: return "Number";
                case TOKEN::SYMBOL: return "Symbol";
                case TOKEN::END:    return "End";
                default: puts("error"); return "";
            }
        }();

        std::cout << literal << "( " << token.value << " )" << std::endl;
    }
}

