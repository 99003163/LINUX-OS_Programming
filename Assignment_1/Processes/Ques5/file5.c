#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
int var,stat;
var=fork();
if(var<0)
{
printf("error");
}
else if(var==0)
{
execlp("gcc","gcc","t.c","-o","ta",NULL);
exit(0);
}
else
{
waitpid(-1,&stat,0);
printf("child is created\n");
printf("statis %d",WEXITSTATUS(stat));
}
}
