#include "types.h"
#include "user.h"

int basicTest(void);

int main(int argc, char *argv[]) {
    printf(1, "####################################################\n");
    printf(1, "# This program tests the correctness of your lab#2\n");
    printf(1, "####################################################\n");
    

    if (atoi(argv[1]) == 1)
		basicTest();
    else 
        printf(1, "\ntype \"lab1 1\" to test exit and wait, \"lab1 2\" to test waitpid \n");
  
    // End of test
    exit(0);
}
 
int basicTest(void) {
    int pid;
	int status;

	pid = fork();

	if (pid == 0) {
		altprty(13);
		sleep(1);
		for(;;) {
			printf(1, " Child is running.\n");
		}
		exit(0);
	}
	else if (pid > 0) {
		altprty(1);
		sleep(1);
		for(;;) {
			printf(1, " Parent is running.\n");
		}
	}
	else {
		printf(1, "Something went wrong with fork system call.");
		exit(-1);
	}
	wait(&status);

	return 0;
}


