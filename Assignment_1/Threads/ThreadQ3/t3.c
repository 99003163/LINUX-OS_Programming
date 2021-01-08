#include <stdio.h>
#include <time.h>
 
int main()
{
    time_t Time= time(NULL);
    struct  tm tm = *localtime(&Time);
     
    printf("System Time is: %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
 
    return 0;
}
