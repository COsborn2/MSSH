#include "process.h"

void forkIt(char ** argv)
{
    int status;
	pid_t pid = fork();
	if(pid != 0){
		waitpid(pid, &status, 0);
	}
	else{
        if(execvp(argv[0], argv) == -1)
            exit(-1);
	}
}
