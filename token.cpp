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
        switch(token.type) {
            case TOKEN::NUMBER: literal = "Number"; break;
            case TOKEN::SYMBOL: literal = "Symbol"; break;
            case TOKEN::END:    literal = "End"; break;
            default: puts("error"); break;
        }

        std::cout << literal << "( " << token.value << " )" << std::endl;
    }
}

bool Token::is(std::string val) {
    return tokens[pos].value == val;
}

bool Token::istype(TOKEN ty) {
    return tokens[pos].type == ty;
}

bool Token::expect(std::string val) {
    if(tokens[pos].value == val) {
        step();
        return true;
    }
    else
        fprintf(stderr, "error: %s expected", val.c_str());
    return false;
}

token_t Token::get_step() {
    return tokens[pos++];
}

void Token::step() {
    pos++;
}
