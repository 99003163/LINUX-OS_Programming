#include "sm.h"

#define Max_Itms 7 // Maximum itms a producer can produce or a consumer can consume
#define Buf_Sz 7 // Size of the buf

int ip = 0;
int op = 0;
int itm=0;
int buf[Buf_Sz];
pthread_mutex_t mutex;

void *producer(void *p_no)
{   
    if(ip==Buf_Sz-1)
    {
        printf("The producer Stack is full \n");
    }
    else
    {
     for(int i = 0; i < Max_Itms; i++) {
        itm = rand(); // Produces random values
        pthread_mutex_lock(&mutex);
        // put values into the buffer 
        buf[ip] = itm;
        printf("Producer %d: Insert itm %d at %d\n", *((int *)p_no),buf[ip],ip);
        ip = (ip + 1) % Buf_Sz;     
        pthread_mutex_unlock(&mutex);
     }
    }
}
void *consumer(void *c_no)
{   
    if(op == Buf_Sz-1)
    {
        printf("The consumer Stack is full\n");
    }
    else
    {
     int itm=0;
     for(int i = 0; i < Max_Itms; i++) {
        pthread_mutex_lock(&mutex);
        // takes one unit from the buffer
        itm = buf[op];
        printf("Consumer %d: Remove itm %d from %d\n",*((int *)c_no),itm, op); 
        op = (op + 1) % Buf_Sz;     
        pthread_mutex_unlock(&mutex);
     }
    }
}

int main()
{   

    pthread_t pro[7],con[7];
    pthread_mutex_init(&mutex, NULL);

    int a[7] = {1,2,3,4,5,6,7};

    for(int i = 0; i < 7; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 7; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 7; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 7; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
