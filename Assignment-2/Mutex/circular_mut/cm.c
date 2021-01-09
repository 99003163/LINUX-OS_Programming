#include "cm.h"

#define Max_Itms 7 
#define Buf_Sz 7 

int ip = 0;
int op = 0;
int buf[Buf_Sz];
pthread_mutex_t mutex;

void *producer(void *p_no)
{   
    int item;
    for(int i = 0; i < Max_Itms; i++) {
        item = rand(); // Produce random items
        pthread_mutex_lock(&mutex);

        while (((ip + 1) % Buf_Sz) == op)
        {
       
           buf[ip] = item;
           printf("Producer %d: Insert Item %d at %d\n", *((int *)p_no),buf[ip],ip);
           ip = (ip + 1) % Buf_Sz;     
        }
        pthread_mutex_unlock(&mutex);
    }
}
void *consumer(void *c_no)
{   
    int item=0;
    for(int i = 0; i < Max_Itms; i++) {
        pthread_mutex_lock(&mutex);
        
        while (ip == op) 
        {
        
           item = buf[op];
           printf("Consumer %d: Remove Item %d from %d\n",*((int *)c_no),item, op); 
           op = (op + 1) % Buf_Sz;     
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{   

    pthread_t pro[7],con[7];
    pthread_mutex_init(&mutex, NULL);

    int a[7] = {1,2,3,4,5,6,7}; //Just used for numbering the producer and consumer

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
