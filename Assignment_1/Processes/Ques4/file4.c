/* mini shell that can take 6 arguments*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    pid_t ret1;
    int flag;
    int cmdexe;
    char cmd[10];
    printf("Enter your command:");
    scanf("%s", cmd);                  
    ret1=fork();
    
    if(ret1<0)
    {
        perror("fork");
        exit(1);
    }
    if(ret1==0)
    {
        cmdexe=execlp(cmd,cmd,NULL);
        if(cmdexe<0)
        {
            perror("execlp");
            exit(2);
        }
        exit(0);
    }
    else
    {
        waitpid(-1,&flag,0); //waits for process;
        printf("parent--child exit flag=%d\n",
			WEXITSTATUS(flag));
    }
}
