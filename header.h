#define handle_error(msg) \
  { perror(msg); exit(EXIT_FAILURE);}

extern void print_file(char *file);
