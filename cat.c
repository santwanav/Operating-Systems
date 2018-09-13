#include<stdio.h>
#include<stdlib.h>
/* It should accept just one argument and print an error on all other cases*/
int main(int argc, char *argv[]) {
	if (argc > 2) {
		printf("Too many arguments.");
		exit(1);
	}
	else if (argc < 2) {
		printf("No file specified.");
		exit(1);
	}
	else {
		FILE *file = fopen(argv[1], "r");
		if (file == NULL) {
			printf("No such file found");
			exit(1);
		}
		else {
			fseek(file, 0, SEEK_END);
			long fsize = ftell(file);
			fseek(file, 0, SEEK_SET);
			char *buff = malloc(fsize+1);
			fread(buff, fsize, 1, file);
			fclose(file);
			printf("%s", buff);
			exit(0);
		}
	}
	return 0;
}

