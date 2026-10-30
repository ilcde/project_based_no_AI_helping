#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer *NewInputBuffer() {
  InputBuffer *buffer = malloc(sizeof(InputBuffer));
  buffer->buffer = NULL;
  buffer->buffer_length = 0;
  buffer->input_length = 0;

  return buffer;
}

void print_prompt() { printf("db> "); }

void ReadInputBuffer(InputBuffer *input_buffer) {
  ssize_t byte_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (byte_read <= 0) {
    printf("Error reading input");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_length = byte_read - 1;
  input_buffer->buffer[byte_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}
int main(int argc, char *argv[]) {
  InputBuffer *input = NewInputBuffer();

  while (true) {
    print_prompt();
    ReadInputBuffer(input);

    if (strcmp(input->buffer, ".exit") == 0) {
      close_input_buffer(input);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'.\n", input->buffer);
    }
  }
}
