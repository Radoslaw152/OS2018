#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		err(1,"Wrong argument");
	}

	const char string[] = "foobar\n";

//	int fd = open(argv[1],O_RDONLY, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int status;
	if ( fork() > 0 )
	{
		wait(&status);
		int fd = open(argv[1],O_RDONLY);
		int counter = 0;
		char temp;
		lseek(fd,0,SEEK_SET);
		while( read(fd,&temp,1) > 0 )
		{

			if(counter == 2)
			{
				const char delimiter[] = " ";
				write(1,delimiter, sizeof(delimiter));
				counter = 0;
			}
			counter++;
			write(1,&temp,1);
		}
		close(fd);
	}
	else
	{
		int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(fd, string, sizeof(string));
		close(fd);
	}
	exit(0);
}
