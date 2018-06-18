#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
void writeFromFD(int fd, int* index)
{
	char temp;
	off_t theEnd = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);
	off_t firstTime = 0;
	while ( read(fd,&temp,1) == 1)
	{
		if ( temp == '\n' && firstTime != 0 && index != NULL 
				&& firstTime + 1 != theEnd)
		{
			printf("\n\t%d ",index[0]++);
		}
		else
		{
			if(firstTime == 0 && index != NULL)
			{
				printf("\t%d ",index[0]++);
			}
			printf("%c",temp);
		}
		firstTime++;
	}
}
int main(int argc, const char* const argv[])
{
	if( argc < 2 )
	{
		writeFromFD(0,0);
		exit(0);
	}
	
	int shouldPutNumber = 0;
	int* index = 0;
	int number = 1;
	if ( strcmp(argv[1],"-n") == 0)
	{
		shouldPutNumber = 1;
		index = &number;
	}

	for(int i = 1 + shouldPutNumber; i < argc; ++i)
	{
		if( strcmp(argv[i],"-") == 0)
		{
			writeFromFD(0,index);
		}
		else
		{
			int fd = open(argv[i],O_RDONLY);
			if (fd == -1)
			{
				err(2,"Cannot open file %s",argv[i]);
			}
			writeFromFD(fd,index);
			close(fd);
		}
	}
}

