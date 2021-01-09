#include "stcksem.h"

#define Max_itms 3 

#define Buffer_Size 3

sem_t emp;
sem_t full;
int ip = 0;
int op = 0;
int itm = 0;
int buf[Buffer_Size];

void *producer(void *p_no) {
  if (ip == Buffer_Size - 1) {
    printf("Producer Stack is full \n");
  } 
  else {
    for (int i = 0; i < Max_itms; i++) {
      itm = rand();
      sem_wait(&emp);
      /* put value itm into the buffer */
      buf[ip] = itm;
      printf("Producer %d: Insert itm %d at %d\n", *((int *)p_no), buf[ip],
             ip);
      ip = (ip + 1) % Buffer_Size;
      sem_post(&full);
    }
  }
}

void *consumer(void *c_no) {
  if (op == Buffer_Size - 1) {
    printf("Consumer Stack is full\n");
  } 
  else {
    int itm = 0;
    for (int i = 0; i < Max_itms; i++) {
      sem_wait(&full);
      /* take one unit of data from the buffer */
      itm = buf[op];
      printf("Consumer %d: Remove itm %d from %d\n", *((int *)c_no), itm, op);
      op = (op + 1) % Buffer_Size;
      sem_post(&emp);
    }
  }
}

void main() {
  pthread_t pro[3], con[3];
  sem_init(&emp, 0, Buffer_Size);
  sem_init(&full, 0, 0);

  int a[3] = {1, 2, 3}; 

  for (int i = 0; i < 3; i++) {
    pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
  }
  for (int i = 0; i < 3; i++) {
    pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
  }

  for (int i = 0; i < 3; i++) {
    pthread_join(pro[i], NULL);
  }
  for (int i = 0; i < 3; i++) {
    pthread_join(con[i], NULL);
  }

  sem_destroy(&emp);
  sem_destroy(&full);
}
