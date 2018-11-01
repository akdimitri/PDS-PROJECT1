/**********************************************************************
 *
 * qsort-cilk.c -- Parallel implementation of QuickSort
 *
 * Dimitris Antoniadis <akdimitri@auth.gr>
 * Last edited: 31/10/2018
 *
 **********************************************************************/


#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <stdio.h>
#include "qsort-sequential.h"


/* local function declarations */
void qsort_cilk( int *a, int n);


/** Quicksort_Cilk() : this function is called by main thread. This function sets the number of threads and the starts parallel execution **/
void Quicksort_Cilk( int *a, int n, int p){


	/*Set nworkers(THREADS) parameter*/
	int NUM_WORKERS = 1<<p;
	
	/* nworkers variable should be set as a string */
	char WORKERS[33];
	sprintf( WORKERS, "%d", NUM_WORKERS);
	
	/* Shut down Cilk runtime */
	__cilkrts_end_cilk();
	
	if (0!= __cilkrts_set_param("nworkers",WORKERS)) {
    printf("Failed to set worker count: %s \nYour CPU can not set this number of workers \n", WORKERS);
  }


	/*Start Cilk*/
	__cilkrts_init();
	
	printf("Number of Workers: %d \n", __cilkrts_get_nworkers());
	qsort_cilk( a, n);

	__cilkrts_end_cilk();
	/* Shut down Cilk runtime */
}


void qsort_cilk( int *a, int n){
	
	/* 50 is a random value, the optimal value is different for every CPU */
	if( n > 50){

		int p = partition( a, n);
		
		/* Spawn a new thread */
		cilk_spawn qsort_cilk( a, p);
		
		/* Meawhile this thread */
		qsort_cilk( &a[p+1], n-p-1);
		
		/* Wait both threads to be finished */
		cilk_sync;
	}
	else{
		qsort_seq( a, n);
	}
}
