#pragma once

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include <iostream>
#include <string>
#include <vector>
#include <stack>

enum class TOKEN {
    NUMBER,
    SYMBOL,
    END,
};

struct token_t {
    TOKEN type;
    std::string value;
};

class Token {
    public:
        void push_number(std::string);
        void push_symbol(std::string);
        void push_end();
        void show();
    private:
        std::vector<token_t> tokens;
        int pos;
};

class Lexer {
    public:
        Token run(std::string);
};

enum class OPCODE {
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    PRINT,
    PRINTLN,
};

struct vmcode_t {
    OPCODE type;
    int value;
    std::string name;

    vmcode_t(OPCODE t): type(t) {}
    vmcode_t(OPCODE t, int v): type(t), value(v) {}
    vmcode_t(OPCODE t, std::string n): type(t), name(n) {}
};
