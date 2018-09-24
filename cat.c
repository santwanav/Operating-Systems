#include"header.h"

struct arguments {
	int number_noblank;
	int show_ends;
	int number_all;
	int squeeze_blank;
	int show_tabs;
	int show_nonprinting;
	int num_of_files;
	char **files;
};

static const char* optString = "bEnstTv";
void print_file(char *file, struct arguments *args);
void get_arguments(int num, char *input[], struct arguments *args);

int main(int argc, char *argv[]) {
/* Assigning initial values */
	struct arguments *args;
	args = (struct arguments*) malloc(sizeof(struct arguments));
	args->number_noblank = 0;
	args->show_ends = 0;
	args->number_all = 0;
	args->squeeze_blank = 0;
	args->show_tabs = 0;
	args->show_nonprinting = 0;
	args->num_of_files = 0;
	args->files = NULL;

/* Handle error if no file specified */
	check_valid(argc);

/* Perform command line arguments parsing */
	get_arguments(argc, argv, args);

/* Perform printing according to flags present */
	for (int i = 0; i < args -> num_of_files; i++) {
		print_file(*((args -> files) + i), args);
	}
	return 0;
}

void print_file(char *file, struct arguments *args) {
	int fd = open(file, O_RDONLY);
	if (fd == -1)
		handle_error("cat error");
	struct stat sb;
	fstat (fd, &sb);
	char *page = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (page == MAP_FAILED) handle_error("mmap");
	close(fd);
	for (int i = 0; i < sb.st_size; i++){
		if ((page[i] == '\n') && (args -> show_ends == 1)) {
			printf("%c", '$');
			printf("%c", page[i]);
		}
		else if ((page[i] == '\t') && (args -> show_tabs))
			printf("%s", "^I" );
		else
			printf("%c", page[i]);
	}
}

void check_valid(int num){
	if (num < 2) {
		printf("No file specified");
		exit(1);
	}
	return;
}

void get_arguments( int num, char *input[], struct arguments *args ) {
	int opt = 0;
	opt = getopt( num, input, optString );
	while (opt != -1) {
		switch (opt) {
			case 'b':
				args->number_noblank = 1;
				break;
			case 'E':
				args->show_ends = 1;
				break;
			case 'n':
				args->number_all = 1;
				break;
			case 's':
				args->squeeze_blank = 1;
				break;
			case 'T':
				args->show_tabs = 1;
				break;
			case 'v':
				args->show_nonprinting = 1;
				break;
			default:
				break;
		}
		opt = getopt ( num, input, optString );
	}
	args->num_of_files = num - optind;
	args->files = input + optind;

/* If both `n` and `b`, then `n` should be overwritten */
	if (args->number_all && args->number_noblank)
		args->number_all = 0;
}

