#include "vmcalc.h"

AST *Parser::run(Token _t) {
    token = _t;

    AST *program = expr_add();
    return program;
}

AST *Parser::expr_add() {
    AST *left = expr_mul();

    while(1) {
        if(token.is("+")) {
            token.step();
            left = new Node_binary("+", left, expr_mul());
        }
        else if(token.is("-")) {
            token.step();
            left = new Node_binary("-", left, expr_mul());
        }
        else
            return left;
    }
}

AST *Parser::expr_mul() {
    AST *left = expr_primary();

    while(1) {
        if(token.is("*")) {
            token.step();
            left = new Node_binary("*", left, expr_mul());
        }
        else if(token.is("/")) {
            token.step();
            left = new Node_binary("/", left, expr_mul());
        }
        else
            return left;
    }
}

AST *Parser::expr_primary() {
    while(1) {
        if(token.istype(TOKEN::NUMBER)) return expr_num(token.get_step());
        else if(token.is("(")) {
            token.step();
            AST *left = expr_add();
            token.expect(")");
            return left;
        }

        fprintf(stderr, "??? : %s", token.get_step().value.c_str());
        return nullptr;
    }
}

AST *Parser::expr_num(token_t tk) {
    return new Node_number(atoi(tk.value.c_str()));
}

void Parser::show(AST *ast) {
    switch(ast->get_ndtype()) {
        case NODE::NUMBER: {
            auto n = (Node_number *)ast;
            printf("%d ", n->value);
        } break;
        case NODE::BINARY: {
            auto b = (Node_binary *)ast;
            printf("(");
            printf("%s ", b->op.c_str());
            show(b->left);
            show(b->right);
            printf(")");
        } break;
        default: puts("error");
    }
}
