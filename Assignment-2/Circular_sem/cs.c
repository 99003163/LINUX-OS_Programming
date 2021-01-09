#include "cs.h"

#define Max_Itms 3 // Maximum items 
#define Buf_Sz 3 // Size of buffer

sem_t emp;
sem_t full;
int ip = 0;
int op = 0;
int buf[Buf_Sz];
pthread_mutex_t mutex;

void *producer(void *p_no)
{   
    int itm;
    for(int i = 0; i < Max_Itms; i++) {
        itm = rand(); // Produce a random items
        sem_wait(&emp);
        pthread_mutex_lock(&mutex);
        // waiting for space
        while (((ip + 1) % Buf_Sz) == op)
        {
        //put values into the buffer 
           buf[ip] = itm;
           printf("Producer %d: Insert itm %d at %d\n", *((int *)p_no),buf[ip],ip);
           ip = (ip + 1) % Buf_Sz;     
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *c_no)
{   
    int itm=0;
    for(int i = 0; i < Max_Itms; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        /* wait for buf to fill */
        while (ip == op) 
        {
        /* take one unit of data from the buf */
           itm = buf[op];
           printf("Consumer %d: Remove itm %d from %d\n",*((int *)c_no),itm, op); 
           op = (op + 1) % Buf_Sz;     
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&emp);
    }
}

int main()
{   

    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&emp,0,Buf_Sz);
    sem_init(&full,0,0);

    int a[3] = {1,2,3}; //Just used for numbering the producer and consumer

    for(int i = 0; i < 3; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 3; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&emp);
    sem_destroy(&full);

    return 0;
}
