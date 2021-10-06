#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "interpreter.h"

#define CODE_CHARS_MAX 2048
#define BYTE_ARRAY_NUMBER 30000

int main(int argc, char *argv[]) {
  char code_input[CODE_CHARS_MAX] = "";

  if(argc <= 1) {
    // repl
    printf("Welcome to brainf*ck repl!\n");

    initialize(BYTE_ARRAY_NUMBER);

    while(true) {
      printf("> ");
      fgets(code_input, CODE_CHARS_MAX - 1, stdin);
      code_input[CODE_CHARS_MAX - 1] = '\0';

      int evalResult = evaluate(code_input, strlen(code_input));

      if(evalResult != 0) {
        printf("Evaluation terminated.\n");
      }
    }
  } else {
    // execute file
    FILE *input_file = NULL;
    input_file = fopen(argv[1], "r");

    if(input_file == NULL) {
      printf("The file %s cannot be opened.\n", argv[1]);

      return 0;
    }

    printf("Executing %s\n", argv[1]);

    initialize(BYTE_ARRAY_NUMBER);

    size_t file_chars = 0;
    fseek(input_file, 0, SEEK_END);
    file_chars = ftell(input_file);

    char *input = (char*) calloc(file_chars, sizeof(char));
    fseek(input_file, 0, SEEK_SET);

    fread((void*) input, sizeof(char), file_chars, input_file);

    fclose(input_file);

    int evalResult = evaluate(input, file_chars);

    if(evalResult != 0) {
      printf("Evaluation terminated.");
    }
  }
}