#include "p.h"

void main() 
{
    char str1[256]="start"; 
    int fifo_wr,fifo_rd; 
    while(strcmp(str1,"end")!=0)   
    {   
        fifo_wr= open("pipe1",O_WRONLY);   
        if(fifo_wr<0)     
            printf("\nError while opening pipe");   
        else     
        {
            printf("chat: ");     
            scanf("%s",str1);     
            write(fifo_wr,str1,255*sizeof(char));     
            close(fifo_wr);     
        }   
        fifo_rd=open("pipe2",O_RDONLY);   
        if(fifo_rd<0)     
            printf("\nError while opening pipe");   
        else     
        {     
            read(fifo_rd,str1,255*sizeof(char));     
            close(fifo_rd);     
            printf("\n%s",str1);   
        }   
    } 
}
