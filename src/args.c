#include "args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Create a new Args object */
Args *create_args(char *filename) {
  Args *args = (Args *)malloc(sizeof(Args));
  args->filename = (char *)malloc(strlen(filename) + 1);
  strcpy(args->filename, filename);
  return args;
}

/* Destroy an Args object */
void destroy_args(Args *args) {
  if (!args) {
    return;
  }

  free(args->filename);
  free(args);
}

/* Parse command line arguments */
Args *parse_args(int argc, char **argv) {
  if (argc != 3) {
    printf("Not enough arguments passed.\n");
    return NULL;
  } else if (strcmp(argv[1], "-f")) {
    printf("Invalid first parameter.\n");
    return NULL;
  }

  Args *args = create_args(argv[2]);
  return args;
}
