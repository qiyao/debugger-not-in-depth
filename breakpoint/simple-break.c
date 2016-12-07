#include <sys/ptrace.h>
#include <asm/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int 
main()
{
  pid_t child = fork();

  if(child == 0){
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execl("./int3", NULL);
  }
  else{
    int status;
    long pc;

    while(1){
      wait(&status);
      if (WIFEXITED(status)){
	printf("Exit status:%d\n",WEXITSTATUS(status));
	return 0;
      }	  
      if (WIFSTOPPED(status)){
	printf("STOPPED by %d, ", WSTOPSIG(status));
      }
      if (WIFSIGNALED(status)) {
	printf("SIGNALED by %d, ", WTERMSIG(status));
      }
      
      pc = ptrace(PTRACE_PEEKUSER, child, 4 * EIP, NULL);
      printf ("at 0x%lx\n", pc);

      ptrace(PTRACE_CONT,child, NULL, NULL);	  
    }
	 
  }
  return 0;
}
