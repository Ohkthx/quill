#include "lexer.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* Create a new token.
 *
 * Returns a pointer to the new token if successful, or NULL if memory
 * allocation failed.
 */
Token *create_token(TokenType type, const char *value) {
  Token *token = malloc(sizeof(Token));
  if (!token) {
    return NULL;
  }

  token->type = type;
  token->value = strdup(value);
  if (!token->value) {
    free(token);
    return NULL;
  }

  return token;
}

/* Destroy a token, freeing all resources. */
void destroy_token(Token *token) {
  if (!token) {
    return;
  }

  free(token->value);
  free(token);
}

/* Parse a token from a given value.
 *
 * Returns a pointer to the new token, or NULL if memory allocation failed.
 */
Token *parse_token(const char *value) {
  Token *token = create_token(TOKEN_IDENTIFIER, value);
  if (!token) {
    fprintf(stderr, "Failed to allocate memory for token.\n");
    return NULL;
  }

  return token;
}

/* Iterate over the tokens within the lexer.
 *
 * Returns a pointer to the next token, or NULL if there are no more tokens.
 */
Token *iterate_tokens(Lexer *lexer) {
  assert(lexer != NULL && "lexer pointer should not be NULL");
  if (!lexer) {
    fprintf(stderr, "Lexer pointer is NULL.\n");
    return NULL;
  }

  if (lexer->token_position >= lexer->token_count) {
    return NULL;
  }

  // Return the next token and increment the position.
  return lexer->tokens[lexer->token_position++];
}
