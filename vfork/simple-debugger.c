#include <sys/ptrace.h>
#include <asm/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int 
main()
{
  pid_t child;


   
  child = fork();

  if(child == 0)
    {
      ptrace(PTRACE_TRACEME, 0, NULL, NULL);
      execl("./vfork", NULL);
    }
  else
    {
      int status;

      unsigned int event;
      long pc;
      pid_t new_child = 0;
      printf ("child is %d\n", child);

	  wait(&status);
	  if (WIFEXITED(status))
	    {
	      printf("Exit status:%d\n",WEXITSTATUS(status));
	      return 0;
	    }	  
	  if (WIFSTOPPED(status))
	    {
	      printf("STOPPED by %d, ", WSTOPSIG(status));
	    }
	  if (WIFSIGNALED(status))
	    {
	      printf("SIGNALED by %d, ", WTERMSIG(status));
	    }
      
	  pc = ptrace(PTRACE_PEEKUSER, child, 4 * EIP, NULL);
	  printf ("at 0x%lx\n", pc);

          ptrace (PTRACE_SETOPTIONS , child , NULL , PTRACE_O_TRACEVFORK|PTRACE_O_TRACEVFORKDONE);

	  ptrace(PTRACE_SINGLESTEP,child, NULL, NULL);	  



      while(1)
	{
	  wait(&status);
	  if (WIFEXITED(status))
	    {
	      printf("Exit status:%d\n",WEXITSTATUS(status));
	      return 0;
	    }	  
	  if (WIFSTOPPED(status))
	    {
	      printf("STOPPED by %d [%s], ", WSTOPSIG(status), strsignal (WSTOPSIG (status)));

               event = status >> 16;
               printf ("event is %d, ", event);

               if (event == PTRACE_EVENT_VFORK){
                  printf ("vfork....\n");
                 if (ptrace(PTRACE_GETEVENTMSG, child, NULL, &new_child)) {
                    perror("ptrace PTRACE_GETEVENTMSG failed");
                 } 
                 printf ("new child is %d, resume child\n", new_child);
                 ptrace(PTRACE_CONT,new_child, NULL, NULL);
                 continue;
               }else if (event == PTRACE_EVENT_VFORK_DONE){
                  printf ("vfork done\n");
               } else{
                  ptrace(PTRACE_CONT,new_child, NULL, NULL);
                  printf ("continue child\n");
                  continue;
               }
	    }
	  if (WIFSIGNALED(status))
	    {
	      printf("SIGNALED by %d, ", WTERMSIG(status));
	    }
      
	  pc = ptrace(PTRACE_PEEKUSER, child, 4 * EIP, NULL);
	  printf ("at 0x%lx\n", pc);
/*
	  ptrace(PTRACE_CONT,child, NULL, NULL);	  
*/        ptrace(PTRACE_SINGLESTEP,child, NULL, NULL); 
	}
	 
    }
  return 0;
}
