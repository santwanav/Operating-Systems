#include<stdio.h>
#include<stdlib.h>
/* It should accept just one argument and print an error on all other cases*/
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("No file specified.");
		exit(1);
	}
	for (int i = 1; i < argc; i++) {
		FILE *file = fopen(argv[i], "r");
		if (file == NULL) {
			printf("No such file found");
			exit(1);
		}
		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);
		char *buff = malloc(fsize+1);
		fread(buff, fsize, 1, file);
		fclose(file);
		printf("%s", buff);
	}
	return 0;
}

