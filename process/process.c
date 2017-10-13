#include "process.h"

void forkIt(char ** argv, char ** thePath)
{
    int status;
	pid_t pid = fork();
	if(pid != 0){
		waitpid(pid, &status, 0);
	}
	else{
        if(execvpe(argv[0], argv, thePath) == -1)
            exit(-1);
	}
}
