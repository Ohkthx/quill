#include "lexer.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 128

/* Create a new file reader.
 *
 * Returns a pointer to the new file reader if successful, or NULL if memory
 * allocation failed or the file could not be opened.
 */
FileReader *create_reader(const char *filename) {
  FileReader *reader = malloc(sizeof(FileReader));
  if (!reader) {
    fprintf(stderr, "Failed to create reader: Memory allocation failed");
    return NULL;
  }

  reader->line_number = 0;
  reader->line_length = 0;
  reader->max_size = INITIAL_BUFFER_SIZE;

  // Open the file.
  reader->file = fopen(filename, "r");
  if (!reader->file) {
    fprintf(stderr, "Failed to open file");
    free(reader);
    return NULL;
  }

  // Allocate the buffer for the line.
  reader->buffer = malloc(reader->max_size);
  if (!reader->buffer) {
    fprintf(stderr, "Failed to allocate buffer");
    fclose(reader->file);
    free(reader);
    return NULL;
  }

  return reader;
}

/* Destroy a file reader.
 *
 * Frees the memory associated with the file reader.
 */
void destroy_reader(FileReader *reader) {
  if (!reader) {
    return;
  }

  fclose(reader->file);
  free(reader->buffer);
  free(reader);
}

/* Reads the next line from the File within FileReader. Expands the FileReader's
 * buffer if the line is too long.
 *
 * Returns a pointer to the line if successful, or NULL if the end of the file
 * has been reached. This is the same data contained in the buffer of the line.
 */
char *read_line(FileReader *reader) {
  assert(reader != NULL && "reader pointer should not be NULL");
  if (!reader) {
    fprintf(stderr, "Reader pointer is NULL");
    return NULL;
  }

  reader->line_length = 0;

  while (true) {
    // Read the next portion of the line.
    char *line = fgets(reader->buffer + reader->line_length,
                       reader->max_size - reader->line_length, reader->file);

    if (!line) {
      // Could be EOF or partial line.
      if (reader->line_length == 0) {
        // EOF reached.
        return NULL;
      } else {
        // Partial line.
        reader->buffer[reader->line_length] = '\0';
        reader->line_number += 1;
        return reader->buffer;
      }
    }

    // Update the length of the line read so far.
    size_t len = strlen(line);
    reader->line_length += len;

    // Check if we read the full line (ends with '\n').
    if (reader->buffer[reader->line_length - 1] == '\n') {
      // Exclude the newline character.
      reader->line_length--;
      reader->buffer[reader->line_length] = '\0';
      reader->line_number += 1;
      return reader->buffer;
    }

    // Resize the buffer if it is full.
    if (reader->line_length == reader->max_size - 1) {
      size_t new_size = reader->max_size * 2;
      char *new_buffer = realloc(reader->buffer, new_size);
      if (!new_buffer) {
        fprintf(stderr, "Failed to expand buffer");
        return NULL;
      }

      reader->buffer = new_buffer;
      reader->max_size = new_size;
    }
  }
}
