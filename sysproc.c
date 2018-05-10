#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

//CS153 Lab01
int
sys_exit(void)
{
  int exit_status;
  if (argint(0, &exit_status) < 0) {
	  return -1;
  }
  exit(exit_status);
 
  return 0;  // not reached
}


//CS153 Lab01 Implementation
int
sys_wait(void) {
  int *status;
  if (argptr(0, (char**)&status, 0) < 0) {
	return -1;
  }
  return wait(status);
}

//CS153 Lab01 Implementation
int 
sys_waitpid(void)
{
  int pid, options;
  int *status;

  if (argint(0, &pid) < 0) {
    return -1;
  }
  if (argptr(1, (char**)&status, 0) < 0) {
	return -1;
  }
  if (argint(2, &options) < 0) {
	return -1;
  }

  return waitpid(pid, status, options);
}

//CS153 Lab02 Implementation
int
sys_altprty(void)
{
	int new_priority;
	if (argint(0, &new_priority) < 0) {
		return -1;
	}
	
	return altprty(new_priority);
}

//Lab02
int
sys_inherit_prty(void)
{
  return inherit_prty();
}

//Lab02
int
sys_donate_prty(void)
{
  return donate_prty();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_getprty(void)
{
  return myproc()->priority;
}

int
sys_gettimestats(void)
{
  //gettimestats();
  struct proc *curproc = myproc();
  cprintf("Time Stats for process #%d \n",curproc->pid);
  cprintf(" -- TotalTime: %d \n", curproc->totaltime);
  cprintf(" -- WaitTime: %d \n", curproc->waitingtime);
  cprintf(" -- RunningTime: %d \n", curproc->runningtime);

  return 0;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

int
sys_yield(void)
{
  yield();
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
