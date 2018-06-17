#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
int main(int argc, const char* const argv[])
{
	if ( argc < 2 )
	{
		err(1,"Wrong arguments");
	}

	int status;
	int successfulCounter = 0;
	int failedCounter = 0;
	for(int i = 1; i < argc;++i)
	{
		if (fork() > 0)
		{
			wait(&status);
			if (WEXITSTATUS(status) == 0)
			{
				successfulCounter++;
			}
			else
			{
				failedCounter++;
			}
		}
		else
		{
			int fd = open("/dev/null",O_WRONLY);
			close(1);
			close(2);
			dup(fd);
			dup(fd);
			if (execlp(argv[i],argv[i],0))
			{
				exit(255);
			}
			close(fd);
		}
	}
	printf("Count successful commands: %d\n",successfulCounter);
	printf("Count failed commands: %d\n", failedCounter);
	exit(0);
}

