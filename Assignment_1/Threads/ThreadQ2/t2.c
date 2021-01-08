#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
  
// Size of the array 
#define max 16 
  
// Number of threads created
#define Th_max 4 
  
// Array 
int a[max] = { 1, 3, 5, 50, 13, 15, 19, 21, 
               23, 25, 30, 300, 64, 10, 20 }; 
  
// Array to store max of threads 
int max_num1[Th_max] = { 0 }; 
int thread_num = 0; 
  
// Function to find maximum 
void maximum(void* arg) 
{ 
    int i, num = thread_num++; 
    int maxs = 0; 
  
    for (i = num * (max / 4); i < (num + 1) * (max / 4); i++) { 
        if (a[i] > maxs) 
            maxs = a[i]; 
    } 
  
    max_num1[num] = maxs; 
} 
  
// Driver code 
int main() 
{ 
    int maxs = 0; 
    int i; 
    pthread_t threads[Th_max]; 
  
    // 4 threads created 
    for (i = 0; i < Th_max; i++) 
        pthread_create(&threads[i], NULL, 
                       maximum, (void*)NULL); 
  
    // 4 threads joined
    for (i = 0; i < Th_max; i++) 
        pthread_join(threads[i], NULL); 
  
    // finds max value in array
    for (i = 0; i < Th_max; i++) { 
        if (max_num1[i] > maxs) 
            maxs = max_num1[i]; 
    } 
  
    printf("Maximum Element is : %d", maxs); 
  
    return 0; 
} 
