#include <unistd.h>
#include <stdio.h>

int main(char* argv[]){
  int pid;

  pid = vfork ();
  if (pid == -1)
    {
      return 1;
    }
  else if (pid != 0)
    {
       printf ("father\n");
    }
  else
    {
       printf ("child\n");
       _exit(0);
    }
  return 0;
  
}
