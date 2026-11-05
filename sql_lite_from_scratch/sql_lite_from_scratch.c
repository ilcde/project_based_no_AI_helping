#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *Buffer;
  size_t BufferLength;
  ssize_t InputLength;

} InputBuffer;

InputBuffer *inputBuffer() {
  InputBuffer *input = malloc(sizeof(InputBuffer));
  input->Buffer = NULL;
  input->BufferLength = 0;
  input->InputLength = 0;
  return input;
};

void print_prompt() { printf("db> "); }

void read_input_byte(InputBuffer *input) {
  ssize_t readbyte = getline(&(input->Buffer), &(input->BufferLength), stdin);

  if (readbyte <= 0) {
    printf("ERROR READING INPUT");
    exit(EXIT_FAILURE);
  }
  input->InputLength = readbyte - 1;
  input->Buffer[readbyte - 1] = 0;
}
void close_input_buffer(InputBuffer *input) {
  free(input->Buffer);
  free(input);
}

typedef enum { META_SUCCESS, META_UNRECOGNISE_COMMAND } Meta_Command_Result;
typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } Prepare_Result;

Meta_Command_Result do_meta_command(InputBuffer *input) {
  if (strcmp(input->Buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_UNRECOGNISE_COMMAND;
  }
};
typedef enum { INSERT, SELECT } Statement_type;
typedef struct {
  Statement_type type_state;
} statement;

Statement_type prepare_statement(InputBuffer *input, statement *statement) {
  if (strncmp(input->Buffer, "insert", 6) == 0) {
    statement->type_state = INSERT;
    return PREPARE_SUCCESS;
  }
  if (strcmp(input->Buffer, "select") == 0) {
    statement->type_state = SELECT;
    return PREPARE_SUCCESS;
  }
  return PREPARE_UNRECOGNIZED_STATEMENT;
}
void execute_statment(statement *statement) {
  switch (statement->type_state) {
  case (INSERT):
    printf("");
    break;
  case (SELECT):
    printf("");
    break;
  }
}

int main(int argc, char *argv[]) {
  InputBuffer *input = inputBuffer();

  while (true) {
    print_prompt();
    read_input_byte(input);

    /*first leason of sqlite from scratch below
    if (strcmp(input->Buffer, ".exit") == 0) {
      close_input_buffer(input);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'.\n", input->Buffer);
    }*/
    if (input->Buffer[0] == '.') {
    }
  }
}
