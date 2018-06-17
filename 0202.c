#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if ( argc != 4 )
	{
		err(1,"Wrong parameters");
	}

	int status;
	
	for (int i = 1; i < argc; ++i)
	{
		if ( fork() > 0 )
		{
			pid_t pid = wait(&status);
			printf("The PID is %d, the exit status is: %d\n", pid, WEXITSTATUS(status));
		}
		else
		{
			int fd =  open("/dev/null", O_WRONLY);
			close(1);
			close(2);
			dup(fd);
			dup(fd);

			if (execlp(argv[i],argv[i],NULL) == -1)
			{
				exit(254);
			}
		}
	}
	exit(0);
}

