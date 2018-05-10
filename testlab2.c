#include "types.h"
#include "user.h"

int basicTest(void);
int philTest(void);

int main(int argc, char *argv[]) {
    printf(1, "####################################################\n");
    printf(1, "# This program tests the correctness of your lab#2\n");
    printf(1, "####################################################\n");
    

    if (atoi(argv[1]) == 1)
	basicTest();
    else if (atoi(argv[1]) == 2)
	philTest();
    
    else 
        printf(1, "\ntype \"lab2 1\" Andrew test \"lab2 2\" Phil test \n");
  
    // End of test
    exit(0);
}
 
int basicTest(void) {
    int status, i, j;
	int pid_a[5] = {0,0,0,0,0};

	for (i = 0; i < 5; i++) {
		pid_a[i] = fork();
		
		if (pid_a[i] == 0) {
			if(i == 0) {
				altprty(30);
				for(j=0; j<100; j++) {
					printf(1, "Process #%d: j=%d\n",i,j);
					yield();
				}
				exit(0);
			}
			else if(i == 1) {
				altprty(30);
				for(j=0; j<100; j++) {
					printf(1, "Process #%d: j=%d\n",i,j);
					yield();
				}
				exit(0);
			}
			else if(i == 2) {
				altprty(30);
				for(j=0; j<100; j++) {
					printf(1, "Process #%d: j=%d\n",i,j);
					yield();
				}
				exit(0);
			}
			else if(i == 3) {
				altprty(2);
				for(j=0; j<100; j++) {
					printf(1, "Process #%d: j=%d\n",i,j);
					yield();
				}
				exit(0);
			}
			else {
				altprty(2);
				for(j=0; j<100; j++) {
					printf(1, "Process #%d: j=%d\n",i,j);
					yield();
				}
				exit(0);
			}
		}
	}

	for(i = 0; i < 5; i++) {
		waitpid(pid_a[i],&status,0);
	}
	return 0;
}

int philTest(void) {
	int i;
	for (i = 0; i < 5; i = i) {
        	fork();
		i++;

		altprty(i);
		donate_prty();
		inherit_prty();
	}
	return 0;
}



