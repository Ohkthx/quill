#pragma once

#include <stddef.h>
#include <stdio.h>

// Error Codes
#define LEXER_OK 0
#define LEXER_READER_NULL -1
#define LEXER_READER_LINE_NULL -2
#define LEXER_MALLOC_TOKEN -3
#define LEXER_MALLOC_TOKEN_VALUE -4
#define LEXER_REALLOC_TOKENS -5

typedef enum TokenType {
  TOKEN_EOF = 0, // End of file.
  TOKEN_EOS,     // End of statement.
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_CHAR,
  TOKEN_OPERATOR,
  TOKEN_KEYWORD,
  TOKEN_COMMENT,
} TokenType;

typedef struct {
  TokenType type; // Type of the token.
  char *value;    // Value of the token.
} Token;

typedef struct {
  size_t line_number; // Current line the buffer represents.
  size_t line_length; // Total length of the line.
  size_t max_size;    // Maximum capacity for the buffer.
  FILE *file;         // Pointer to the file.
  char *buffer;       // Buffer holding the lines contents.
} FileReader;

typedef struct {
  size_t length;   // Current length of the banks contents.
  size_t max_size; // Maximum capacity for the bank.
  size_t position; // Current position within the buffer.
  char *buffer;    // Buffer holding the banks contents.
} Bank;

typedef struct {
  FileReader *reader;    // Reader for the file.
  size_t token_position; // Current position within the token array.
  size_t token_count;    // Total number of tokens.
  Token **tokens;        // Array of pointers to tokens.
} Lexer;

// Token Functions
void destroy_token(Token *);
Token *parse_token(const char *);
Token *iterate_tokens(Lexer *);

// File Functions
FileReader *create_reader(const char *);
void destroy_reader(FileReader *);
char *read_line(FileReader *);

// Lexer Functions
Lexer *create_lexer(const char *);
void destroy_lexer(Lexer *);
int tokenize(Lexer *);
