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

enum class NODE {
    NUMBER,
    BINARY,
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

        bool is(std::string);
        bool istype(TOKEN);
        bool expect(std::string);
        void step();
        token_t get_step();
    private:
        std::vector<token_t> tokens;
        int pos = 0;
};

class Lexer {
    public:
        Token run(std::string);
};


class AST {
    public:
        virtual NODE get_ndtype() = 0;
};

class Node_number: public AST {
    public:
        int value;
        virtual NODE get_ndtype() { return NODE::NUMBER; }

        Node_number(int v): value(v) {}
};

class Node_binary: public AST {
    public:
        std::string op;
        AST *left;
        AST *right;
        virtual NODE get_ndtype() { return NODE::BINARY; }

        Node_binary(std::string o, AST *l, AST *r):
            op(o), left(l), right(r) {}
};

class Parser {
    public:
        AST *run(Token);
        void show(AST *);
    private:
        Token token;
        AST *expr_add();
        AST *expr_mul();
        AST *expr_primary();

        AST *expr_num(token_t);
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

class VMcode {
    public:
        void generate();
        std::vector<vmcode_t> vmcodes;
        void show();
};

class VM {
    public:
        void run(std::vector<vmcode_t>);
        void exec(vmcode_t);
    private:
        std::stack<int> vmstack;
};
