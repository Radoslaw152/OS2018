#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
int main(int argc, char* argv[])
{
	if (argc !=  3 )
	{
		err(1,"Wrong arguments");
	}

	int fd = open(argv[2],O_RDONLY);
	if ( fd == -1 )
	{
		err(2,"Cannot open file %s", argv[2]);
	}
	
	if ( strcmp(argv[1],"--min") == 0)
	{
		uint16_t min;
		uint16_t temp;
		read(fd,&temp,sizeof(temp));
		min = temp;
		while(read(fd,&temp,sizeof(temp)) == sizeof(temp))
		{
			if (min > temp)
			{
				min = temp;
			}
		}

		printf("The minimum number is: %d\n", min);
	}
	else if ( strcmp(argv[1],"--max") == 0)
	{
		uint16_t max;
                uint16_t temp;
                read(fd,&temp,sizeof(temp));
                max = temp;
                while(read(fd,&temp,sizeof(temp)) == sizeof(temp))
                {
                        if (max < temp)
                        {
                                max = temp;
                        }
                }

                printf("The maximum number is: %d\n", max);

	}
	else if ( strcmp(argv[1],"--print") == 0)
	{
                uint16_t temp;
                while(read(fd,&temp,sizeof(temp)) == sizeof(temp))
                {
                        printf("%d\n",temp);
                }
	}
	else
	{
		close(fd);
		err(3,"Wrong argument %s", argv[1]);
	}
	close(fd);
}
