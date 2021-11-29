#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


char* lineBuffer;


void nc_kill() {
	free(lineBuffer);
	exit(0);
}


int main(int argc, const char* restrict argv[]) {
	signal(SIGINT, nc_kill);

	if (argc < 2) {
		printf("Usage: %s <..files>\n", argv[0]);
		return 0;
	}
	
	for (int i = 1; i < argc; ++i) {
		if (access(argv[i], F_OK) != 0) {
			printf("NumCat: %s not found.\n");
		} else {
			unsigned int lineNum = 1;
			FILE* fp = fopen(argv[i], "r");
			
			size_t bufsize = 5;
			lineBuffer = (char*)malloc(sizeof(char) * bufsize);

			while (getline(&lineBuffer, &bufsize, fp) != -1) {
				printf("~%d  %s", lineNum, lineBuffer);
				++lineNum;
			}

			printf("\n\n");

			free(lineBuffer);
		}
	}
}
