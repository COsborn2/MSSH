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
void forkItFileOut(char ** argv, int directTo)
{
	int status;
	pid_t pid = fork();
	if(pid != 0){
		waitpid(pid, &status, 0);
	}
	else{
		dup2(directTo, 1);
		if(execvp(argv[0], argv) == -1)
			exit(-1);
	}
}
void forkItFileIn(char ** argv, int directTo)
{
	int status;
	pid_t pid = fork();
	if(pid != 0){
		waitpid(pid, &status, 0);
	}
	else{
		dup2(directTo, 0);
		if(execvp(argv[0], argv) == -1)
			exit(-1);
	}
}
