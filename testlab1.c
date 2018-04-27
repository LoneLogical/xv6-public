#include "types.h"
#include "user.h"

int exitWait(void);
int waitPid(void);
int waitPidTestCases(void);

int main(int argc, char *argv[]) {
    printf(1, "####################################################\n");
    printf(1, "# This program tests the correctness of your lab#1\n");
    printf(1, "####################################################\n");
  
    if (atoi(argv[1]) == 1)
        exitWait(); // Test exit and wait
    else if (atoi(argv[1]) == 2)
        waitPid(); // Test waitpid
    else if (atoi(argv[1]) == 3)
		waitPidTestCases(); //Phillip and Adrew's Test Cases for Lab 1
	// For corner cases
    else 
        printf(1, "\ntype \"lab1 1\" to test exit and wait, \"lab1 2\" to test waitpid \n");
  
    // End of test
    exit(0);
}
  
  
int exitWait(void) {
    int pid, ret_pid, exit_status;
    int i;
  
    // use this part to test exit(int status) and wait(int* status)
    printf(1, "Step 1: testing exit(int status) and wait(int* status):\n");

    for (i = 0; i < 2; i++) {
        pid = fork();
        if (pid == 0) { // only the child executed this code
            if (i == 0) {
                printf(1, " - This is child with PID# %d and I will exit with status %d\n", getpid(), 0);
                exit(0);
            } else {
                printf(1, " - This is child with PID# %d and I will exit with status %d\n" ,getpid(), -1);
                exit(-1);
            } 
        } else if (pid > 0) { // only the parent exeecutes this code
            ret_pid = wait(&exit_status);
            printf(1, " - This is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
        } else {  // something went wrong with fork system call
            printf(2, " - Error using fork\n");
            exit(-1);
        }
    }
    return 0;
}

int waitPid(void){	
    int ret_pid, exit_status;
    int i;
    int pid_a[5]={0, 0, 0, 0, 0};

    // use this part to test wait(int pid, int* status, int options)
    printf(1, "Step 2: testing waitpid(int pid, int* status, int options):\n");

    for (i = 0; i <5; i++) {
        pid_a[i] = fork();

        if (pid_a[i] == 0) { // only the child executed this code  
            printf(1, " - The is child with PID# %d and I will exit with status %d\n", getpid(), 0);

            exit(0);
        }
    }
    
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[3]);
    ret_pid = waitpid(pid_a[3], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[1]);
    ret_pid = waitpid(pid_a[1], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[2]);
    ret_pid = waitpid(pid_a[2], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[0]);
    ret_pid = waitpid(pid_a[0], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[4]);
    ret_pid = waitpid(pid_a[4], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);

    return 0;
}


//CS153 Lab01
// Provideds multiple cases for testing WaitPid function
int waitPidTestCases(void){	
    int ret_pid, exit_status;
    int i;
    int pid_a[5]={0, 0, 0, 0, 0};
    // use this part to test wait(int pid, int* status, int options)

    printf(1, "Step 2: testing waitpid(int pid, int* status, int options):\n");

    for (i = 0; i <5; i++) {
		sleep(5);
        pid_a[i] = fork();
	
        if (pid_a[i] == 0) { // only the child executed this code  
           	sleep(5); 
			if (i == 0) {
				printf(1, " - This is child with PID# %d and I will exit with status %d\n", getpid(), 13);
				exit(13);
			}
			else if (i == 1) {
				printf(1, " - This is child with PID# %d and I will exit inappropriately by not including a status \n", getpid());
				exit(0); //should return -1
			}
			else if (i == 2) {
				printf(1, " - This is child with PID# %d and I will perform an exec call that should succeed and not return to call exit %d\n", getpid(), 13);
				char *argvector[] = {"echo", "hello world", 0};
				exec("echo", argvector); //should work and not return
      			printf(1, "init: fork failed\n");
				exit(13);
			}
			else if (i == 3) {
				printf(1, " - This is child with PID# %d and I will perform an exec call that should NOT succeed and should return to call exit with status %d \n", getpid(), 13);
				char *argvector[] = {"echor", 0};
				exec("echor", argvector); //should NOT work and return for us to exit
      			printf(1, "init: fork failed\n");
				exit(13);
			}
			else {
				printf(1, " - This is child with PID# %d and I will wait on my own pid %d\n", getpid(), getpid());
				ret_pid = waitpid(getpid(), &exit_status, 0);
				printf(1, " - Child with PID# %d returned from waitpid with value: %d  and status: %d \n", getpid(), ret_pid, exit_status);
				exit(0);
			}
			/*
			else {
				printf(1, " - This is child with PID# %d and I will spawn a new child \n", getpid());
				pid_cc = fork();
				
				if (pid_cc == 0) { //grandchild process of original process
					printf(1, " - This is child with PID# %d and I will exit with status %d \n", getpid(), 77);
					sleep(50);
					exit(77);
				}
				else { //middle child process
					printf(1, " - This is child with PID# %d and I will now exit with status %d\n", getpid(), 0);
					exit(0);
				}
			}
			*/
        }
    }
       
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[0]);
    ret_pid = waitpid(pid_a[0], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[1]);
    ret_pid = waitpid(pid_a[1], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[2]);
    ret_pid = waitpid(pid_a[2], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[3]);
    ret_pid = waitpid(pid_a[3], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[4]);
    ret_pid = waitpid(pid_a[4], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);

	sleep(50);
	//ensure that child processes exited, and that waitpid returns -1 for nonexistant children
    unsigned j;
    for (j = 0; j < 5; j++) {
      if (waitpid(pid_a[j], &exit_status, 0) != -1)
        printf(1, " - FAIL -In parent: either child process %d did not exit correctly, or waitpid did not return correct value for non-existing process\n", pid_a[j]);
      else
        printf(1, " - This is the parent: exit verification for child %d success\n", pid_a[j]); 
    }


    return 0;
}

