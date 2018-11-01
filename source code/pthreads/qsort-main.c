/**********************************************************************
*
* qsort.c -- Implementation of Sequential QuickSort and Parallel QuickSort
* 		  -- >>./qsort			stores the results of 10 tests to a file
*		  -- >>./qsort q p		simple execution for 2^q array length with 2^p threads compared to sequential Quicksort 
*
*
* Dimitris Antoniadis <akdimitri@auth.gr>
**********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-sequential.h"
#include "qsort-pthreads.h"
#include "results.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>



/* local function declarations */
int  test( int *a, int n);
void init( int *a, int n);
void print(int *a, int n);
int cmpfunc (const void * a, const void * b);


/* --- Entry POINT --- */
int main(int argc, char **argv) {



	if(argc == 3){
		
		//---------------//
		//--./qsort q p--//
		//---------------//
		
		/* variables to hold execution time */
		struct timeval startwtime, endwtime;
		double qsort_time;
		
		/* initiate vector of random integerts */
		int n  = 1 << atoi(argv[1]); //2^n NUMBERS
		int p = atoi(argv[2]);
		
		/* initiate vector of random integerts */
		int *a = (int *) malloc(n * sizeof(int));
		init(a, n);
		
		/*save a copy of the array to Compare it with sequential QuickSort */
		int *b = (int *) malloc(n * sizeof(int));
		memcpy( (void*) b,(void*) a, n*sizeof(int));
		
		//----------------------//
		//--PTHREADS QUICKSORT--//
		//----------------------//		
		//parallel execution			
		gettimeofday (&startwtime, NULL);
		Quicksort_Parallel( a, n, p);
		gettimeofday (&endwtime, NULL);

		/* get time in seconds */
		qsort_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
			  + endwtime.tv_sec - startwtime.tv_sec);

		/* validate result */
		int pass = test( a, n);
		printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
		assert( pass != 0 );

		/* print execution time */
		printf("Pthreads wall clock time: %f sec\n", qsort_time);
		
		//--END--//
		/* Reinitialize the array */
		memcpy( (void*) a,(void*) b, n*sizeof(int));
		
		//------------------------//
		//--SEQUENTIAL QUICKSORT--//
		//------------------------//
		
		gettimeofday (&startwtime, NULL);
		qsort_seq(a, n);
		gettimeofday (&endwtime, NULL);
		
		/* get time in seconds */
		qsort_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		+ endwtime.tv_sec - startwtime.tv_sec);

		/* validate result */
		pass = test(a, n);
		printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
		assert( pass != 0 );

		/* print execution time */
		printf("Sequential wall clock time: %f sec\n", qsort_time);
		
		//--END--//
		
		/* Reinitialize the array */
		memcpy( (void*) a,(void*) b, n*sizeof(int));
		
		//---------------------//
		//--DEFAULT QUICKSORT--//
		//---------------------// 
		gettimeofday (&startwtime, NULL);
		qsort( a, n, sizeof(int), cmpfunc);
		gettimeofday (&endwtime, NULL);

		/* get time in seconds */
		qsort_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		  + endwtime.tv_sec - startwtime.tv_sec);

		/* validate result */
		pass = test( a, n);
		printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
		assert( pass != 0 );
		
		/* print execution time */
		printf("Qsort wall clock time: %f sec\n", qsort_time);
		
		//--END--//
		free(a);
		free(b);
	}
	else if (argc == 1){
		
		//------------//
		//--./qsort --//
		//------------//
		int i,j,k, pass;

		double SEQUENTIAL_TIMES[10][15];
		double DEFAULT_SEQUENTIAL_TIME[10][15];
		double PTHREADS_PARALLEL_TIMES[10][15][8];
		
		/* variables to hold execution time */
		struct timeval startwtime, endwtime;
		double qsort_time;
		
		
		for(k = 0; k < 10; k++){	
			printf("k = %d \n", k);
			
			for( i = 12; i <= 26; i++){
						
				int n  = 1 << i; //2^n NUMBERS
				
				/* initiate vector of random integerts */
				int *a = (int *) malloc(n * sizeof(int));
				
				/* initialize vector */
				init(a, n);

				/*save a copy of the array */
				int *b = (int *) malloc(n * sizeof(int));
				memcpy( (void*) b,(void*) a, n*sizeof(int));

				printf("n : %d \n", i);
				
				//------------------------//
				//--SEQUENTIAL QUICKSORT--//
				//------------------------// 				
				gettimeofday (&startwtime, NULL);
				qsort_seq(a, n);
				gettimeofday (&endwtime, NULL);

				/* get time in seconds */
				qsort_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
				  + endwtime.tv_sec - startwtime.tv_sec);

				/* validate result */
				pass = test(a, n);
				printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
				assert( pass != 0 );
				
				//STORE TIME
				SEQUENTIAL_TIMES[k][i-12] = qsort_time;
				
				/* print execution time */
				printf("Sequential wall clock time: %f sec\n", qsort_time);
				
				//--END--//
				
				/* Reinitialize the array */
				memcpy( (void*) a,(void*) b, n*sizeof(int));
				
				//---------------------//
				//--DEFAULT QUICKSORT--//
				//---------------------// 
				gettimeofday (&startwtime, NULL);
				qsort( a, n, sizeof(int), cmpfunc);
				gettimeofday (&endwtime, NULL);

				/* get time in seconds */
				qsort_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
				  + endwtime.tv_sec - startwtime.tv_sec);

				/* validate result */
				pass = test( a, n);
				printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
				assert( pass != 0 );
				
				//STORE TIME
				DEFAULT_SEQUENTIAL_TIME[k][i-12] = qsort_time;
				
				/* print execution time */
				printf("Qsort wall clock time: %f sec\n", qsort_time);
				
				//--END--//
				
				/* Reinitialize the array */
				memcpy( (void*) a,(void*) b, n*sizeof(int));
				
				//----------------------//
				//--PTHREADS QUICKSORT--//
				//----------------------//
				
				/* test for p = [1,8] */
				for( j = 1; j <= 8; j++){
					
					int p = j;
					printf("p : %d \n", p);

					//parallel execution			
					gettimeofday (&startwtime, NULL);
					Quicksort_Parallel( a, n, p);
					gettimeofday (&endwtime, NULL);

					/* get time in seconds */
					qsort_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
						  + endwtime.tv_sec - startwtime.tv_sec);

					/* validate result */					
					pass = test( a, n);
					printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
					assert( pass != 0 );

					/* print sorted vector */
					PTHREADS_PARALLEL_TIMES[k][i-12][j-1] = qsort_time;

					/* print execution time */
					printf("Parallel wall clock time: %f sec\n", qsort_time);
					
					/* Reinitialize the array */
					memcpy( (void*) a,(void*) b, n*sizeof(int));
				}
				//--END test for p = [1,8]--//
				free(a);
				free(b);
			}
			//--END test for q = [12,26]--//
			
		}	
		//-------------------//
		//--END of 10 tests--//
		//-------------------//
		
		/* store results to a file */
		write_results_to_file( SEQUENTIAL_TIMES, DEFAULT_SEQUENTIAL_TIME, PTHREADS_PARALLEL_TIMES);
	}
	else{
		printf("Please Enter ./qsort or ./qsort n p \n");
	}
	/* exit */
		return 0;

}







/** -------------- SUB-PROCEDURES  ----------------- **/ 

/** procedure test() : verify sort results **/
int test(int *a, int n) {
	int i;

	int pass = 0; //assign pass a positive value
	for(i = 0; i < n - 1; i++){
		if( ! ( a[i] < a[i+1])){
			int pass = 1;
			return pass; //exit test.
		}
	}
	return pass;	  
}

/** procedure init() : initialize array "a" with data **/
void init(int *a, int n) {
	int i;
	for (i = 0; i < n; i++) {
		a[i] = rand() % n; // (N - i);
	}
}

/** procedure  print() : print array elements **/
void print(int *a, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int cmpfunc (const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}

