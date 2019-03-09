#include "vmcalc.h"

int VM::run(std::vector<vmcode_t> vmcodes) {
    if(vmcodes.empty()) {
        fprintf(stderr, "no codes"); return -1;
    }
    for(auto code: vmcodes)
        exec(code);
    return vmstack.top();
}

void VM::exec(vmcode_t c) {
    switch(c.type) {
        case OPCODE::PUSH: {
            vmstack.push(c.value);
        } break;
        case OPCODE::ADD: {
            int r = vmstack.top(); vmstack.pop();
            int l = vmstack.top(); vmstack.pop();
            vmstack.push(l + r);
        } break;
        case OPCODE::SUB: {
            int r = vmstack.top(); vmstack.pop();
            int l = vmstack.top(); vmstack.pop();
            vmstack.push(l - r);
        } break;
        case OPCODE::MUL: {
            int r = vmstack.top(); vmstack.pop();
            int l = vmstack.top(); vmstack.pop();
            vmstack.push(l * r);
        } break;
        case OPCODE::DIV: {
            int r = vmstack.top(); vmstack.pop();
            int l = vmstack.top(); vmstack.pop();
            vmstack.push(l / r);
        } break;
        default:
            puts("???");
    }
}

