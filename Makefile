run:
	g++ -o vmcalc main.cpp lexer.cpp token.cpp parser.cpp vmcode.cpp vm.cpp  -g -Wall -Wextra
