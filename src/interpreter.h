#ifndef BRAINFUCK_INTERPRETER_LOADED
#define BRAINFUCK_INTERPRETER_LOADED

#define ERR_INITIALIZE -1
#define ERR_ARRAY_BOUNDS -2
#define ERR_END -3

void initialize(size_t array_member_num);

int evaluate(char* code, size_t code_length);

#endif