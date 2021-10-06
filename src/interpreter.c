#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "interpreter.h"

// data byte array
uint8_t *data = NULL;

// "the pointer", index of data byte array
size_t the_pointer = 0;

// max of "the pointer"
size_t the_pointer_max = 0;

void initialize(size_t array_member_num) {
  data = (uint8_t*) calloc(array_member_num, sizeof(uint8_t));
  the_pointer = 0;
  the_pointer_max = array_member_num;
}

int evaluate(char* code, size_t code_length) {
  size_t program_counter = 0;
  size_t block_depth = 0;

  // data is not initialized
  if(data == NULL) {
    fprintf(stderr, "The interpreter may not be initialized.");
    return ERR_INITIALIZE;
  }

  while(program_counter < code_length) {
    const char instraction = code[program_counter];

    if(instraction == '>') {
      // Increment the pointer
      if(the_pointer >= the_pointer_max - 1) {
        fprintf(stderr, "The pointer(%ld) indicates out of array bounds.", the_pointer);
        return ERR_ARRAY_BOUNDS;
      }

      the_pointer += 1;
    } else if(instraction == '<') {
      // Decrement the pointer
      if(the_pointer < 0) {
        fprintf(stderr, "The pointer(%ld) indicates out of array bounds.", the_pointer);
        return ERR_ARRAY_BOUNDS;
      }

      the_pointer -= 1;
    } else if(instraction == '+') {
      // Increment the byte at the pointer
      data[the_pointer] += 1;
    } else if(instraction == '-') {
      // Decrement the byte at the pointer
      data[the_pointer] -= 1;
    } else if(instraction == '.') {
      // Output the byte at the pointer
      putchar(data[the_pointer]);
    } else if(instraction == ',') {
      // Input a byte and store it in the byte at the pointer
      data[the_pointer] = getchar();
    } else if(instraction == '[') {
      // Jump forward past the matching ] if the byte at the pointer is zero.
      if(data[the_pointer] == 0) {
        const size_t block_depth_memory = block_depth;

        block_depth += 1;

        while(block_depth_memory < block_depth) {
          program_counter += 1;

          if(program_counter >= code_length) {
            fprintf(stderr, "Unexpected end of code.");
            return ERR_END;
          }

          if(code[program_counter] == '[') {
            block_depth += 1;
          } else if(code[program_counter] == ']') {
            block_depth -= 1;
          }
        }
      }
    } else if(instraction == ']') {
      // Jump backward to the matching [ unless the byte at the pointer is zero.
      if(data[the_pointer] != 0) {
        const size_t block_depth_memory = block_depth;

        block_depth += 1;

        while(block_depth_memory < block_depth) {
          program_counter -= 1;

          if(program_counter < 0) {
            fprintf(stderr, "Unexpected end of code.");
            return ERR_END;
          }

          if(code[program_counter] == ']') {
            block_depth += 1;
          } else if(code[program_counter] == '[') {
            block_depth -= 1;
          }
        }
      }
    }

    program_counter += 1;
  }

  return 0;
}
