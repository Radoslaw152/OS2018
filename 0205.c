#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
int main(int argc, const char* const argv[])
{
	if ( argc != 3 )
	{
		err(1,"Wrong arguments");
	}

	int status;
	if ( fork() == 0 )
	{
		if (execlp(argv[1],argv[1],0) == -1)
		{
			exit(255);
		}
	}
	else 
	{
		wait(&status);
		if (WEXITSTATUS(status) == 0)
		{
			execlp(argv[2],argv[2],0);
		}
	}
	exit(0);
}
