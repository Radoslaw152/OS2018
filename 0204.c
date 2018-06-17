#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main(int argc, const char* const argv[])
{
	if (argc != 2)
	{
		err(1,"Wrong arguments");
	}

	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC,0644);

	for(int i = 0; i < 10;++i)
	{
		int status;
		if ( fork() > 0 )
		{
			wait(&status);
			write(fd, "bar\n",sizeof("bar\n"));
		}
		else
		{
			write(fd,"foo",sizeof("foo"));
			exit(0);
		}
	}
	close(fd);
	exit(0);
}
