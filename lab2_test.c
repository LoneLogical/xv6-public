#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
	int PScheduler(void);

	PScheduler();

    // End of test
	 exit(0);
 }    
      
int PScheduler(void){

    int pid, ret_pid, exit_status;
    int i,j,k;
  
    printf(1, "\n  Step 2: testing the priority scheduler and setpriority(int priority)) systema call:\n");
    printf(1, "\n  Step 2: Assuming that the priorities range between range between 0 to 31\n");
    printf(1, "\n  Step 2: 0 is the lowest priority. All processes have a default priority of 10\n");
    printf(1, "\n  Step 2: The parent processes will switch to priority 0\n");
    altprty(31);
    for (i = 0; i <  3; i++) {
	    pid = fork();
	    if (pid > 0 ) {
		    continue; //to next iteration of for loop
		}
	    else if (pid == 0) {
            printf(1, "\n Hello! this is child# %d and I will change my priority to %d \n",getpid(),0+10*i);
		    altprty(0+10*i);	
		    for (j=0;j<50000;j++) {
			    for(k=0;k<10000;k++) {
				    asm("nop"); 
				}
			}
		    printf(1, "\n child# %d with priority %d has finished! \n",getpid(),getprty());
			gettimestats();
		    exit(0);
        }
        else {
			printf(2," \n Error \n");
			exit(-1);
        }
	}

	if(pid > 0) {
	    for (i = 0; i <  3; i++) {
	        ret_pid = wait(&exit_status);
			printf(1,"\n This is the parent: child with PID# %d has finished with status %d \n",ret_pid,exit_status);
		}
        printf(1,"\n if processes with highest priority finished first then its correct \n");
    }
			
	return 0;
}

