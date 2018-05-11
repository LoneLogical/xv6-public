#include "types.h"
#include "user.h"

int basicTest(void);
int philTest(void);
int test3(void);

int main(int argc, char *argv[]) {
    printf(1, "####################################################\n");
    printf(1, "# This program tests the correctness of your lab#2\n");
    printf(1, "####################################################\n");
    

    if (atoi(argv[1]) == 1)
	basicTest();
    else if (atoi(argv[1]) == 2)
	philTest();
    else if (atoi(argv[1]) == 3)
	test3(); 
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
				altprty(10);
				for(j=0; j<100; j++) {
					printf(1, "Process #%d: j=%d\n",i,j);
					yield();
				}
				exit(0);
			}
			else if(i == 1) {
				altprty(10);
				for(j=0; j<100; j++) {
					printf(1, "Process #%d: j=%d\n",i,j);
					yield();
				}
				exit(0);
			}
			else if(i == 2) {
				altprty(10);
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
	int pids[5] = {0, 0, 0, 0, 0};
	//int status = 0;

	printf(1, "\nparent pid: %d\n", getpid());

	for (i = 0; i < 5; i++) {
        	pids[i] = fork();

		printf(1, "\nrunning pid %d after fork\n", getpid());

		//child
		if (pids[i] == 0) {
			inherit_prty();
			printf(1, "\nchild inherited parents priority: %d , and is now scheduled\n", getprty());
			break;
		}
	
		altprty(10 + i);
		printf(1, "\nparent running with highest priority %d\n", getprty());	
	}

				
	int status = 0;
	for (i = 0; i < 5; i++) 
		wait(&status);


	return 0;
}

int test3(void) {
	int pid = 0;
	altprty(25);

	printf(1, "\n Parent's pid %d \n", getpid());

	pid = fork();

	//parent
	if (pid) {
		printf(2, "\nparents's (# %d ) priority before donate %d\n", getpid(), getprty()); 
		donate_prty();
	
		printf(1, "\n parent (# %d ) resuming after donation\n", getpid());	
		int status = 0;
		wait(&status);
	}

	else {
		printf(2, "\nchild's (# %d) priority after donation %d\n", getpid(), getprty());	
	}

	return 0;
}	





