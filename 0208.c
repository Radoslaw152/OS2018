#include <sys/wait.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		err(1,"Wrong parameters");
	}


	if ( fork() == 0 )
	{
		execlp(argv[1],argv[1],0);
		exit(255);
	}
	else
	{
		if ( fork() == 0 )
		{
			execlp(argv[2],argv[2],0);
			exit(255);
		}
		else
		{
			int status1;
			int status2;
			pid_t pid1 = wait(&status1);
			pid_t pid2 = wait(&status2);

			if (WEXITSTATUS(status1) == 0)
			{
				printf("%d\n",pid1);
			}
			else if(WEXITSTATUS(status2) == 0)
			{
				printf("%d\n",pid2);
			}
			else
			{
				printf("-1\n");
			}
		}
	}
		exit(0);
}

			
