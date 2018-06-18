#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <wait.h>
#include <stdlib.h>
int main()
{
	int p1[2];
//	int p2[2];
//	int p3[2];
	pipe(p1);
//	pipe(p2);
//	pipe(p3);
	pid_t cut_pid = fork();

	if (cut_pid == -1)
	{
		errx(1,"Cannot create a process");
	}
	if (cut_pid == 0)
	{
		close(p1[0]);
		if ( dup2(p1[1],1) == -1)
		{
			err(2,"Cannot dup");
		}
		//execlp("cut","cut","-d",":","-f","7","/etc/passwd",0);
		execlp("cut","cut","-d:","-f7","/etc/passwd",0);
		err(3,"Cannot exec");
	}

	close(p1[1]);

	int p2[2];
	pipe(p2);

        pid_t sort_pid = fork();

        if (sort_pid == -1)
        {
                errx(1,"Cannot create a process");
        }
        if (sort_pid == 0)
        {
                close(p2[0]);
		if (dup2(p1[0],0) == -1)
		{
			err(2,"Cannot dup");
		}
                if ( dup2(p2[1],1) == -1)
                {
                        err(2,"Cannot dup");
                }
                execlp("sort","sort","-",0);
                err(3,"Cannot exec");
        }

	close(p2[1]);

	int p3[2];
	pipe(p3);
	pid_t uniq_pid = fork();

	if (uniq_pid == -1)
	{
		err(1,"Cannot create a process");
	}
	if(uniq_pid == 0)
	{
		close(p3[0]);
		if (dup2(p2[0],0) == -1)
		{
			err(2,"Cannot dup");
		}
		if(dup2(p3[1],1) == -1)
		{
			err(2,"Cannot dup");
		}

		execlp("uniq","uniq","-c",0);
		err(3,"Cannot exec");
	}

	close(p3[1]);

	dup2(p3[0],0);
	execlp("sort","sort","-n",0);
	exit(0);
}


