/*  Could do some demo work.  */

#include <sys/ptrace.h>
#include <asm/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#include <errno.h>

#include "breakpoint.h"
#include "link_map.h"


pid_t child;

int 
main()
{   
 
  int status;
  unsigned char orig;
  struct breakpoint b;
  long l;

  child = fork();
  if(child == 0) 
    {
      ptrace(PTRACE_TRACEME, 0, NULL, NULL);
      execl("./test-dl", NULL);
    }
  else 
    {
      int i = 0;
      char buffer[40];


      wait(NULL);

      /*  Set breakpoint on _dl_debug_state in ld-2.4.so.  */
      setup_breakpoint (child, 0x004a93c9, &b);
      ptrace(PTRACE_CONT,child, NULL, NULL);

      while (i < 30)
	{
	  /*  Wait until child stop.  */
	  wait(&status);
	  if (WIFEXITED(status))
	    {
	      printf("Exit status:%d\n",WEXITSTATUS(status));
	      return 0;
	    }

	  if (WIFSTOPPED(status))
	    {
	      printf("STOPPED by %d\n", WSTOPSIG(status));
	      hit_breakpoint(child, &b);

	      target_read_memory (r__debug, &lml, sizeof(lml));
	      printf("version: %d, map = 0x%x\n", lml.r_version, lml.r_map);

	      l = lml.r_map;
	      while (l)
		{
		  target_read_memory (l, &lm, sizeof(lm));
		  target_read_memory (lm.l_name, buffer, sizeof(buffer));
		  printf("l_addr 0x%x, l_name 0x%x, l_ld 0x%lx, l_next 0x%x, l_prev 0x%x, ", 
			 lm.l_addr, lm.l_name, lm.l_ld, lm.l_next, lm.l_prev);
		  buffer[sizeof(buffer) - 1] = '\0';
		  printf ("name = %s\n", buffer);
		  l = lm.l_next;
		}
	    }
	  if (WIFSIGNALED(status))
	    {
	      printf("SIGNALED by %d", WTERMSIG(status));
	    }

	  ptrace(PTRACE_CONT,child, NULL, NULL);	  
	  
	  i++;
	}
      
    }
  return 0;
}
