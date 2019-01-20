#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define handle_error(msg) \
{ perror(msg); exit(EXIT_FAILURE);}

//void print_file(char* file);
void check_valid(int num);
