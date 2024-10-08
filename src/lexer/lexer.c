#include "lexer.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Create a new lexer.
 *
 * Returns a pointer to the new lexer if successful, or NULL if memory
 * allocation failed.
 */
Lexer *create_lexer(const char *filename) {
  Lexer *lexer = malloc(sizeof(Lexer));
  if (!lexer) {
    fprintf(stderr, "Failed to create lexer: Memory allocation failed.\n");
    return NULL;
  }

  lexer->reader = create_reader(filename);
  if (!lexer->reader) {
    free(lexer);
    fprintf(stderr, "Failed to create lexer: Reader creation failed.\n");
    return NULL;
  }

  lexer->token_count = 0;
  lexer->token_position = 0;
  return lexer;
}

/* Destroy the lexer, freeing all resources. */
void destroy_lexer(Lexer *lexer) {
  assert(lexer != NULL && "lexer pointer should not be NULL");
  if (!lexer) {
    return;
  }

  destroy_reader(lexer->reader);

  // Free each token and its value.
  for (size_t i = 0; i < lexer->token_count; i++) {
    destroy_token(lexer->tokens[i]);
  }

  free(lexer->tokens);
  free(lexer);
}

/* Read the next line from the file and tokenize it.
 *
 * Returns LEXER_OK if successful, or an error code if an error occurred.
 */
int next_line(Lexer *lexer) {
  assert(lexer != NULL && "lexer pointer should not be NULL");

  // Read the next line.
  char *line = read_line(lexer->reader);
  if (!line) {
    return LEXER_READER_LINE_NULL;
  }

  char *delim = " \t\n\r"; // Whitespace characters.
  char *token_str = strtok(line, delim);
  while (token_str) {
    Token *token = parse_token(token_str);
    if (!token) {
      fprintf(stderr, "Failed to parse token.\n");
      return LEXER_MALLOC_TOKEN;
    }

    // Add the token to the lexer's tokens array.
    Token **tokens =
        realloc(lexer->tokens, sizeof(Token *) * (lexer->token_count + 1));
    if (!tokens) {
      fprintf(stderr, "Failed to reallocate memory for tokens array.\n");
      destroy_token(token);
      return LEXER_REALLOC_TOKENS;
    }

    lexer->tokens = tokens;
    lexer->tokens[lexer->token_count] = token;
    lexer->token_count++;

    token_str = strtok(NULL, delim);
  }

  return LEXER_OK;
}

int tokenize(Lexer *lexer) {
  assert(lexer != NULL && "lexer pointer should not be NULL");

  // Parse all lines within the file.
  while (next_line(lexer) == LEXER_OK) {
    // Placeholder.
  }

  return LEXER_OK;
}
