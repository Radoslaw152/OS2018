#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>

int main()
{
	int fd1 = open("/etc/passwd", O_RDONLY);

	if ( fd1 == -1)
	{
		errx(1,"Cannot open /etc/passwd for read-only");
	}

	int fd2 = open("./passwd",O_CREAT | O_WRONLY | O_TRUNC, 0644 );

	if ( fd2 == -1)
	{
		errx(2,"Cannot open/create ./passwd");
	}

	char temp;
	while ( read(fd1, &temp, 1) == 1 )
	{
		if ( temp == ':' )
		{
			temp = '?';
		}
		write(fd2,&temp,1);
	}
	close(fd1);
	close(fd2);
	return 0;
}
