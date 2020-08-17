////////////////////////////////////////////////////////////////////////////
// prime_serial.c
// -------------------------------------------------------------------------
//
// finds prime numbers till the number given by user on one core only
//
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <string.h>
#include<math.h>
#include<stdbool.h>

// Function prototype
void WriteToFile(char *pFilename, int *pMatrix, int inRow);

int main()
{	
	struct timespec start, end, startComp, endComp; //to store time
	double time_taken;
	int n; // to store the user input
	int sqrt_i;
	bool prime;  
	int *primeArray = NULL;
	
	// Get current clock time.
	
    scanf("%d",&n);         // get the user input
    
    clock_gettime(CLOCK_MONOTONIC, &start); 
    
    primeArray = (int*)malloc( n* sizeof(int)); //create the array of size n
    
    clock_gettime(CLOCK_MONOTONIC, &startComp); 
    for( int i =2 ; i<=n ; i++)
    {
        sqrt_i =sqrt(i);
        prime = true;
        for (int j = 2 ; j<= sqrt_i ; j++){
            if(i%j == 0){  //to check if it is prime or not
                prime = false;
            }}
        if (prime == true){
            primeArray[i] =  i;  //writing the orime number
           }
       
    }
    
    clock_gettime(CLOCK_MONOTONIC, &endComp); 
    time_taken = (endComp.tv_sec - startComp.tv_sec) * 1e9; 
    	time_taken = (time_taken + (endComp.tv_nsec - startComp.tv_nsec)) * 1e-9; 
	printf("Cell product complete - Computational time only(s): %lf\n", time_taken); // portion of the computing time of ts
	
    WriteToFile("prime.txt", primeArray, n);
    
    clock_gettime(CLOCK_MONOTONIC, &end); 
	time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
    	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9; 
	printf("Overall time (Including read, product and write)(s): %lf\n", time_taken);	// ts

	return 0;
}

// Function definition
void WriteToFile(char *pFilename, int *pMatrix, int inRow)
{
	int i, j;
	FILE *pFile = fopen(pFilename, "w");
	for(i = 0; i < inRow; i++){
	    if(pMatrix[i] != 0){            // writing only prime number in array into file
		fprintf(pFile, "%d\t", pMatrix[i]);
		fprintf(pFile, "\n");}
	}
	fclose(pFile);
}
