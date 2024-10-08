#pragma once

/* Represents the parsed arguments passed to the application. */
typedef struct {
  char *filename; // File name of source code.
} Args;

Args *parse_args(int, char **);
void destroy_args(Args *);
