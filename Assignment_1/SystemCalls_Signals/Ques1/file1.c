#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    	int maxlen=256, fd1, fd2;
    	char buffer[maxlen];
    	ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
	fd1=open("demo.txt",O_RDONLY);
    
	if(fd1<0)
	{
		perror("open");
		exit(1);
	}
	
    fd2=open("demo1.txt",O_WRONLY|O_CREAT, 0666);
    if(fd2<0)
	{
		perror("open");
		exit(1);
	}
  
    /* Copy process */
    while((ret_in = read (fd1, &buffer, maxlen)) > 0)
          {
            ret_out = write (fd2, &buffer, (ssize_t) ret_in);
            if(ret_out != ret_in)
               {
                /*error in write function */
                perror("write");
                exit(2);
               }
           }
	close(fd1);
    close(fd2);
	exit(0);
}
