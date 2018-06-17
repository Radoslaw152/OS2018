#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
        if ( argc < 2 )
        {
                err(1,"Wrong arguments");
        }


	int fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        for(int i = 1; i < argc - 1;++i)
        {
		int status;
                if (fork() > 0)
                {

			wait(&status);
                        if (WEXITSTATUS(status) == 0)
                        {
			//	printf("%s  %ld\n",argv[i], sizeof(*argv[i]));
				write(fd2,argv[i], strlen(argv[i]));
				write(fd2,"\n",1);
                        }
                }
                else
                {
                        int fd = open("/dev/null",O_WRONLY);
                        close(1);
                        close(2);
                        dup(fd);
                        dup(fd);
                        if (execlp(argv[i],argv[i],0) == -1)
                        {
                                exit(255);
                        }
                        close(fd);
			exit(0);
                }
        }
	close(fd2);
        exit(0);
}

