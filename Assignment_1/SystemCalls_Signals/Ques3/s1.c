#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
void sigh_up(); 
void sig_int(); 
void sig_quit(); 
  
// main code 
void main() 
{ 
    int p_id; 
  
    if ((p_id = fork()) < 0) { 
        perror("fork"); 
        exit(1); 
    } 
  
    if (p_id == 0) { //child
        signal(SIGHUP, sigh_up); 
        signal(SIGINT, sig_int); 
        signal(SIGQUIT, sig_quit); 
        
    } 
  
    else //parent 
    { /* p_id hold id of child */
        printf("\nPARENT sends sigh_up\n\n"); 
        kill(p_id, sigh_up); 
  
        sleep(1);
        printf("\nPARENT sends sig_int\n\n"); 
        kill(p_id, sig_int); 
  
        sleep(1); 
        printf("\nPARENT sends sig_quit\n\n"); 
        kill(p_id, sig_quit); 
        sleep(1); 
    } 
} 
  
// sigh_up() definition 
void sigh_up() 
  
{ 
    signal(SIGHUP, sigh_up); 
    printf("CHILD received a sighup\n"); 
} 
  
// sig_int() definition 
void sig_int() 
  
{ 
    signal(SIGINT, sig_int); 
    printf("CHILD received a sigint\n"); 
} 
  
// sig_quit() definition 
void sig_quit() 
{ 
    printf("My Parent killed me!!!\n"); 
    exit(0); 
} 
