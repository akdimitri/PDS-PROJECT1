/**********************************************************************
 *
 * qsort-pthread.c -- Parallel implementation of QuickSort
 *
 * Dimitris Antoniadis <akdimitri@auth.gr>
 * Last edited: 31/10/2018
 *
 **********************************************************************/


#include <pthread.h>
#include <stdio.h>
#include "qsort-sequential.h"


/* This argument is used by pthreads in order to pass the required arguments */
struct ARGUMENT{
	int *v; 			//pointer to the start of the Array of integers
	int n;				//size o Array v
	int height;			//height of threads recursion
};


/* local function declarations */
int my_partition(int *v, int n);
void median_of_three( int *v, int n);
void my_qsort_seq(int *v, int n);

void *Quicksort( void *_ARGUMENT){
	
	
	struct ARGUMENT _ARGUMENT_PASSED = *((struct ARGUMENT *) _ARGUMENT);
	
	/* If level 0 has not been reached create a new thread */
	if( _ARGUMENT_PASSED.height != 0 && _ARGUMENT_PASSED.n > 50){
		
		struct ARGUMENT _ARGUMENT_1, _ARGUMENT_2;
		
		int p = my_partition( _ARGUMENT_PASSED.v, _ARGUMENT_PASSED.n);
		
		
		_ARGUMENT_1.v = _ARGUMENT_PASSED.v;
		_ARGUMENT_1.n = p;
		_ARGUMENT_1.height = _ARGUMENT_PASSED.height - 1;
		
		_ARGUMENT_2.v = &(_ARGUMENT_PASSED.v[p+1]);
		_ARGUMENT_2.n = _ARGUMENT_PASSED.n - p -1;
		_ARGUMENT_2.height = _ARGUMENT_PASSED.height - 1;
		
		
		/* Create new thread */
		pthread_t tid;
		
		int ret;
		if( ret = pthread_create( &tid, NULL, Quicksort, (void*) &_ARGUMENT_2)){
			perror("ERROR PTHREAD CREATION");			
		}
		
		//MEANWHILE
		Quicksort((void*) &_ARGUMENT_1);
		
		//Wait the other thread to finish
		pthread_join( tid, NULL);
	}
	else{
		qsort_seq( _ARGUMENT_PASSED.v, _ARGUMENT_PASSED.n);
	}
}

/** Quicksort_Parallel() : this function is called by main thread. **/
void Quicksort_Parallel( int *v, int n, int p){
	
	struct ARGUMENT _ARGUMENT;
	_ARGUMENT.v = v;
	_ARGUMENT.n = n;
	_ARGUMENT.height = p;
	
	//start parallel execution
	Quicksort((void*) &_ARGUMENT);
}


/* median of three -- picks the 1st the last and the middle element of
an Array, compares them and places them sorted in the 1st the last and the pivot is placed
in place n-2.*/
void median_of_three( int *v, int n){
	int center = (n-1)/2;
	if( v[center] < v[0])
		swap( v, 0, center);
	if( v[n-1] < v[0])
		swap( v, n-1, 0);
	if( v[n-1] < v[center])
		swap( v, center, n-1);
	
	//place pivot in position v[n-1]
	swap( v, center, n-2);
}


int my_partition ( int *v, int n) {
	if( n > 5){
		median_of_three( v, n);
		//median of three picks the median of three elements and moves it at place v[n-2].
		//These three elements are partitioned.
		int pivot = v[n-2];
		int i = 0;
		  
		for (int j = 1; j < n - 2; j++) 
			if (v[j] < pivot) 
				swap(v,i++,j);

		swap(v, i, n - 2);
		return (i);
	}
	else{
		int pivot = v[n-1];
		int i = 0;
		  
		for (int j = 0; j < n - 1; j++) 
			if (v[j] < pivot) 
				swap(v,i++,j);

		swap(v, i, n - 1);
		return (i);
		
	}
}


