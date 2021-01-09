#include "p.h"

void main() 
{
    int fl1;
    fl1 = mkfifo("pipe1",0666);
    if(fl1<0)
        printf("\npipe1 is not created");
    else
        printf("\npipe1 created");
    int fl2;
    fl2 = mkfifo("pipe2",0666);
    if(fl2<0)
        printf("\npipe2 is not created");
    else
        printf("\npipe2 is created\n");
}
