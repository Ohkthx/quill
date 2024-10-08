#include "args.h"
#include "lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  Args *args = parse_args(argc, argv);
  if (args == NULL) {
    return EXIT_FAILURE;
  }

  // Create the lexer.
  Lexer *lexer = create_lexer(args->filename);
  if (!lexer) {
    return EXIT_FAILURE;
  }

  // Tokenize the file.
  tokenize(lexer);

  // Iterate over tokens.
  Token *token = NULL;
  while ((token = iterate_tokens(lexer)) != NULL) {
    printf("Type=%d, Value=%s\n", token->type, token->value);
  }

  // Properly cleanup resources.
  destroy_args(args);
  destroy_lexer(lexer);

  return EXIT_SUCCESS;
}
