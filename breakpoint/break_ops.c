#include <stdio.h>
#include <sys/ptrace.h>
#include <asm/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>


union instr 
{
  long l; 
  unsigned char c[sizeof(long)/sizeof(char)];
}u;

struct breakpoint
{
  unsigned char orig;
  void* address;
};


#undef DEBUG

extern pid_t child;

void setup_breakpoint(pid_t child, 
		      long address, 
		      struct breakpoint* b)
{
  /* Align the address.  */
  long align = (address >> 2) << 2;
  int idx = address % 4;

  /* Get original instruction at that address.  */
  u.l = ptrace(PTRACE_PEEKTEXT, child, align, NULL);
   if (errno > 0)
    printf("errno = %d\n", errno);

  b->address = (void*) address;

#ifdef DEBUG
  printf("Get Instruction [0x%x 0x%x 0x%x 0x%x] from 0x%lx\n",
         u.c[0], u.c[1], u.c[2], u.c[3], align);
#endif

  /* Write TRAP to the instruction.  */
  b->orig = u.c[idx];
  u.c[idx] = 0xcc;

  /* Write the modified instruction back.  */
  ptrace(PTRACE_POKETEXT, child, align, u.l);

#ifdef DEBUG
  printf("Set breakpoint at 0x%lx, but write [0x%x 0x%x 0x%x 0x%x] at 0x%lx\n", 
	 address, u.c[0], u.c[1], u.c[2], u.c[3], align);
#endif
}

/* Restore the original instruction, and remove the breakpoint.  */
void 
restore_breakpoint(pid_t child, struct breakpoint* b)
{
  long pc;

  long align = (long) b->address;
  int idx = align % 4;
  align = (align >> 2) << 2;

  u.l = ptrace(PTRACE_PEEKTEXT, child, align, NULL);
  u.c[idx] = b->orig;

  /* Write the original instruction back.  */
  ptrace(PTRACE_POKETEXT, child, align, u.l);

#ifdef DEBUG
  printf("Restore the original instruction at 0x%lx\n", align);
#endif

}

/* When hits the trap instruction, write the original instruction back, 
   single step this instruction, and replace the original instruction
   with trap instruction again.  */
void
hit_breakpoint (pid_t child, struct breakpoint* b)
{
  long pc;

  long align = (long) b->address;
  int idx = align % 4;
  align = (align >> 2) << 2;


  /* Decrease PC to execute the original instruciton.  */
  pc = ptrace(PTRACE_PEEKUSER, child, 4 * EIP, NULL);
#ifdef DEBUG
  printf("PC = 0x%x\n", pc);
#endif

  if (pc != (b->address) + 1)
    return;

  u.l = ptrace(PTRACE_PEEKTEXT, child, align, NULL);
  u.c[idx] = b->orig;

  /* Write the original instruction back.  */
  ptrace(PTRACE_POKETEXT, child, align, u.l);

#ifdef DEBUG
  printf("Hit breakpoint: Restore the original instruction [0x%x 0x%x 0x%x 0x%x] at 0x%lx\n", 
	 u.c[0], u.c[1], u.c[2], u.c[3], align);
#endif

  /* Decrease PC by one.  */
  ptrace(PTRACE_POKEUSER, child, 4 * EIP, pc - 1);

  /* Single step.  */
  ptrace(PTRACE_SINGLESTEP,child, NULL, NULL);
  wait(NULL);

  pc = ptrace(PTRACE_PEEKUSER, child, 4 * EIP, NULL);

#ifdef DEBUG
  printf("Single Step: pc = 0x%lx\n", pc);
#endif

  /* Write TRAP to the instruction again.  */
  b->orig = u.c[idx];
  u.c[idx] = 0xcc;
  ptrace(PTRACE_POKETEXT, child, align, u.l);

#ifdef DEBUG
  printf("Write TRAP to instruction stream again [0x%x 0x%x 0x%x 0x%x] at 0x%lx\n", 
	 u.c[0], u.c[1], u.c[2], u.c[3], align);
#endif
}


int
main()
{
  pid_t child;

  child = fork();
  if(child == 0)
    {
      ptrace(PTRACE_TRACEME, 0, NULL, NULL);
      execl("/bin/ls", NULL);
    }
  else
    {
      int status;
      long pc;
      struct breakpoint b;

      wait(NULL);

      /* Set breakpoint on _dl_debug_state in ld-2.4.so.  */
      setup_breakpoint (child, 0x004a93c9, &b);
      ptrace(PTRACE_CONT,child, NULL, NULL);

      while (1)
        {
          /* Wait until child stop.  */
          wait(&status);
          if (WIFEXITED(status))
            {
              printf("Exit status:%d\n",WEXITSTATUS(status));
              return 0;
            }

          if (WIFSTOPPED(status))
            {
              printf("STOPPED by %d, ", WSTOPSIG(status));
              hit_breakpoint(child, &b);
            }
          if (WIFSIGNALED(status))
            {
              printf("SIGNALED by %d, ", WTERMSIG(status));
            }
	  pc = ptrace (PTRACE_PEEKUSER, child, 4 * EIP, NULL);
	  printf ("at 0x%x\n", pc);
          ptrace(PTRACE_CONT,child, NULL, NULL);
        }

    }
  return 0;
}
