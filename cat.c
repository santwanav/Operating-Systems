#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

void print_file(char* file);
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("No file specified.");
		exit(1);
	}
	for (int i = 1; i < argc; i++) {
		print_file(argv[i]);
	}
	return 0;
}

void print_file(char *file) {
	int fd = open(file, O_RDONLY);
	if (fd == -1)
		handle_error("cat error");
	struct stat sb;
	fstat (fd, &sb);
	char *page = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (page == MAP_FAILED) handle_error("mmap");
	close(fd);
	for (int i = 0; i < sb.st_size; i++)
		printf("%c", page[i]);
}

