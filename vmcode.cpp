#include "vmcalc.h"

void VMcode::generate(AST *ast) {
    switch(ast->get_ndtype()) {
        case NODE::NUMBER:
            emit_number(ast); break;
        case NODE::BINARY:
            emit_binary(ast); break;
    }
}

void VMcode::emit_number(AST *ast) {
    auto n = (Node_number *)ast;
    codes.push_back(vmcode_t(OPCODE::PUSH, n->value));
}

void VMcode::emit_binary(AST *ast) {
    auto b = (Node_binary *)ast;

    generate(b->left);
    generate(b->right);

    if(b->op == "+") {
        codes.push_back(vmcode_t(OPCODE::ADD)); return;
    }
    if(b->op == "-") {
        codes.push_back(vmcode_t(OPCODE::SUB)); return;
    }
    if(b->op == "*") {
        codes.push_back(vmcode_t(OPCODE::MUL)); return;
    }
    if(b->op == "/") {
        codes.push_back(vmcode_t(OPCODE::DIV)); return;
    }
}
