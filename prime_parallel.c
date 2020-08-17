////////////////////////////////////////////////////////////////////////////
// prime_parallel.c
// -------------------------------------------------------------------------
//
// finds prime numbers till the number given by user parallely
//
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <pthread.h> 
#include <stdbool.h>

#define NUM_THREADS 2

int n; // to store user input
int *primeArray = NULL;  // to store the prime numbers

// Function prototype
void WriteToFile(char *pFilename, int *pMatrix, int inRow);
void *ThreadFunc(void *pArg); // POSIX thread function format

int main()
{
	int i;
	struct timespec start, end, startComp, endComp; //to store the times for calculation
	double time_taken; 
	

	pthread_t tid[NUM_THREADS];
	int threadNum[NUM_THREADS];
	
	scanf("%d",&n);
    
    clock_gettime(CLOCK_MONOTONIC, &start); 
    
    primeArray = (int*)malloc( n* sizeof(int)); // allocating the size of array to store prime numbers
    
    clock_gettime(CLOCK_MONOTONIC, &startComp);
    
    	// Fork		
	for (i = 0; i < NUM_THREADS; i++)
	{
	    	threadNum[i] = i;
		pthread_create(&tid[i], 0, ThreadFunc, &threadNum[i]); //creating threads and calculating prime numbers
	}
	

	// Join
	for(i = 0; i < NUM_THREADS; i++)
	{
	    	pthread_join(tid[i], NULL);
	}
    
    
    
    clock_gettime(CLOCK_MONOTONIC, &endComp); 
    time_taken = (endComp.tv_sec - startComp.tv_sec) * 1e9; 
    	time_taken = (time_taken + (endComp.tv_nsec - startComp.tv_nsec)) * 1e-9; 
	printf("Cell product complete - Computational time only(s): %lf\n", time_taken); // portion of the computing time of ts
	
    WriteToFile("prime.txt", primeArray, n);
    
    clock_gettime(CLOCK_MONOTONIC, &end); 
	time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 
	printf("Overall time (Including read, product and write)(s): %lf\n", time_taken);
    

}


// Function definition
void *ThreadFunc(void *pArg)
{
	int i, j,sqrt_i;
	bool prime;
	int my_rank = *((int*)pArg);
	printf("Thread %d\n", my_rank);
	
	int rpt = n / NUM_THREADS; 
	int rptr = n % NUM_THREADS; // rpt = rows per thread remainder
	
	int sp = my_rank * rpt; 
	int ep = sp + rpt; 
	if(my_rank == NUM_THREADS-1)
		ep += rptr;

	
	for( int i =sp ; i<=ep ; i++)
    {
        if(i ==1){ 
        continue;}
        sqrt_i =sqrt(i);
        prime = true;
        for (int j = 2 ; j<= sqrt_i ; j++){
            if(i%j == 0){       //check if the remainder is zero 
                prime = false;
            }}
        if (prime == true){
            primeArray[i] =  i;     //storing the prime number only in array
           }
       
    }

	return NULL;
}


void WriteToFile(char *pFilename, int *pMatrix, int inRow)
{
	int i, j;
	FILE *pFile = fopen(pFilename, "w");
	for(i = 0; i < inRow; i++){
	    if(pMatrix[i] != 0){     // writing only prime number in array into file
		fprintf(pFile, "%d\t", pMatrix[i]);
		fprintf(pFile, "\n");}
	}
	fclose(pFile);
}
