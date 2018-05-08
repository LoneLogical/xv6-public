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
    int i, status;
	int pid_a[5] = {0,0,0,0,0};

	for (i = 0; i < 5; i++) {
		pid_a[i] = fork();
		
		if (pid_a[i] == 0) {
			if(i == 0) {
				altprty(30);
				for(;;) {
					printf(1, "Process #%d\n",i);
					yield();
				}
			}
			else if(i == 1) {
				altprty(30);
				for(;;) {
					printf(1, "Process #%d \n",i);
					yield();
				}
			}
			else if(i == 2) {
				altprty(30);
				for(;;) {
					printf(1, "Process #%d \n",i);
					yield();
				}
			}
			else if(i == 3) {
				altprty(2);
				for(;;) {
					printf(1, "Process #%d\n",i);
					yield();
				}
			}
			else {
				altprty(2);
				for(;;) {
					printf(1, "Process #%d: with priority %d \n",i);
					yield();
				}
			}
		}
	}

	wait(&status);

	return 0;
}


