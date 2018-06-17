#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if ( argc != 3 )
	{
		err(1,"Wrong parameters");
	}

	int fd1 = open(argv[1], O_RDONLY);
       	if ( fd1 == -1 )
	{
		errx(2,"Cannot open file %s", argv[1]);
	}

	int fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC,0644);

	if ( fd2 == -1 )
	{
		close(fd1);
		errx(3, "Cannot open file %s", argv[2]);
	}

	char buffer[1024];

	int readBytes = 0;

	while( (readBytes = read(fd1, buffer, 1024)) > 0 )
	{
		write(fd2,buffer,readBytes);
	}

	close(fd1);
	close(fd2);
	exit(0);
}
