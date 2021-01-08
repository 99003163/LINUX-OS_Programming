#include<stdio.h>
#include <pthread.h> 
#define MAX 1000 
#define MAX_THREAD 10 

int a[MAX];


int sum1[10] = { 0 }; 
int part1 = 0; 
  
void* sum1_array(void* arg) 
{  
	int thread_part1 = part1++; 
      for(int i = thread_part1 * (MAX / 10); i < (thread_part1 + 1) * (MAX / 10); i++)
	{
		a[i]=1;
	}
	
    // Each thread computes sum1 of 1/10th of array 
   
  
    for (int i = thread_part1 * (MAX / 10); i < (thread_part1 + 1) * (MAX / 10); i++) 
    
        sum1[thread_part1] += a[i]; 
        	
} 
  
// Driver Code 
int main() 
{ 

  
    pthread_t threads[MAX_THREAD]; 
  
    // Creating 10 threads 
    for (int i = 0; i < MAX_THREAD; i++) 
        pthread_create(&threads[i], NULL, sum1_array, (void*)NULL); 
  
    // joining 10 threads 
    for (int i = 0; i < MAX_THREAD; i++) 
        pthread_join(threads[i], NULL); 
  
    // adding sum of all parts 
    int total_sum1 = 0; 
    for (int i = 0; i < MAX_THREAD; i++) 
        total_sum1 += sum1[i]; 
  
   printf("total:%d\n",total_sum1);
  
    return 0; 
} 
