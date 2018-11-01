/**********************************************************************
 *
 * qsort-openmp.h -- Parallel implementation of QuickSort
 *
 * Dimitris Antoniadis <akdimitri@auth.gr>
 * Last edited: 31/10/2018
 *
 **********************************************************************/

#include <stdio.h>
#include <omp.h>
#include "qsort-sequential.h"



void openmp_qsort(int *v, int n) {
	
	/* 50 is a random value, the optimal value is different for every CPU */
	if (n > 50) {
		int p = partition(v, n);
		/*create a new task for the lower part of the array */
		#pragma omp task 
		{
			openmp_qsort(v,p);
		}
		
		/*create a new task for the upper part of the array */
		#pragma omp task 
		{
			openmp_qsort(&v[p+1],n-p-1);
		}
	}
	else{
		qsort_seq( v, n);
	}
}

/** Openmp_Quicksort() : this function is called by main thread. This function sets the number of threads and the starts parallel execution **/
void Openmp_Quicksort( int *v, int n, int p){
	
	/* set number of threads */
	omp_set_dynamic(0);
	omp_set_num_threads( 1<<p);
	
	/* Start Parallel Execution */
	#pragma omp parallel
	{	
		
		/* This block is called only once to iniate the parallel quicksort */
		#pragma omp single nowait
		{	
			printf("You spawned %d Number of threads \n", omp_get_num_threads());
			openmp_qsort( v, n);
		}
	}
}