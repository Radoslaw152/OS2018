#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
int main (int argc, char* argv[])
{
	if (argc != 2 )
	{
		err(1,"Wrong arguments");
	}

	int status;
	if (fork () > 0 )
	{
		wait(&status);
		if (WEXITSTATUS(status) == 0)
		{
			printf("The command is %s - SUCCESSFUL\n", argv[1]);
		}
		else
		{
			printf("The command is %s - FAILED\n", argv[1]);
		}
	}
	else
	{
		int fd = open("/dev/null", O_WRONLY | O_APPEND | O_CREAT, 0644);
		close(1);
		close(2);
		dup(fd);
		dup(fd);
		if( execlp(argv[1],argv[1],".",0) == -1 )
		{
			exit(-1);
		}
		
	}
	exit(0);
}
