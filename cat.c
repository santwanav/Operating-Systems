#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)


int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("No file specified.");
		exit(1);
	}
	for (int i = 1; i < argc; i++) {
		int file = open(argv[i], O_RDONLY);
		if (file == -1)
			handle_error("No such file");
		struct stat sb;
		fstat(file, &sb);
		printf("Size: %lu\n", (uint64_t)sb.st_size);
		char *page = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, file, 0);
		if (page == MAP_FAILED) handle_error("mmap");
		close(file);
		for (int i = 0; i < sb.st_size; i++)
			printf("%c", page[i]);
	}
	return 0;
}

void print_file(char *file) {
	int fd = open(file, O_RDONLY);
	if (file == -1)
		handle_error("No such file");
	struct stat sb;
	fstat (file, &sb);
	char *page == mmap(NULL, sb.st_size; PROT_READ, MAP_SHARED, file, 0);
	if (page == MAP_FAILED) handle_error("mmap");
	close(file)
		printf("%c", page[i]);
}

