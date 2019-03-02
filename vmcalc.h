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
    ADD,
    SUB,
    MUL,
    DIV,
};

struct vmcode_t {
    OPCODE type;
    int value;

    vmcode_t(OPCODE t): type(t) {}
    vmcode_t(OPCODE t, int v): type(t), value(v) {}
};

class VMcode {
    public:
        std::vector<vmcode_t> compile(AST *);
        std::vector<vmcode_t> codes;
        void show();
    private:
        void emit_number(AST *);
        void emit_binary(AST *);
};

class VM {
    public:
        int run(std::vector<vmcode_t>);
        void exec(vmcode_t);
    private:
        std::stack<int> vmstack;
};
