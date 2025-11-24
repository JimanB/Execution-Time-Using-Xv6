#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid;
  int start_ticks, end_ticks;

  //check if a command is provided
  if(argc < 2){
    //print usage message to file descriptor 2 (standard error)
    fprintf(2, "usage: exectime command [args...]\n");
    exit(1); //exit with an error status
  }

  //get the starting time in ticks using the uptime() system call
  start_ticks = uptime();
  //print start time to file descriptor 1 (standard output)
  fprintf(1, "uptime: %d\n", start_ticks);

  //fork a child process
  pid = fork();

  if(pid < 0){
    //fork failed
    fprintf(2, "exectime: fork failed\n");
    exit(1); //exit with an error status
  } else if (pid == 0) {
    //this is the child process
    //argv[0] is "exectime".
    //argv[1] is the command to execute.
    //argv + 1 provides the command and its arguments to exec.
    //execute the command
    if(exec(argv[1], argv + 1) < 0){
      //exec failed
      fprintf(2, "exectime: exec %s failed\n", argv[1]);
      exit(1); //exit with an error status
    }
  } else {
    //this is the parent process
    //wait for the child process to complete.
    //wait(0) means we are not interested in the child's exit status details here.
    wait(0); 

    //get the completion time in ticks
    end_ticks = uptime();
    //print end time to file descriptor 1 (standard output)
    fprintf(1, "uptime: %d\n", end_ticks);

  }

  exit(0); //exit successfully
}
