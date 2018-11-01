/**********************************************************************
 *
 * qsort-pthread.h -- Parallel implementation of QuickSort
 *
 * Dimitris Antoniadis <akdimitri@auth.gr>
 * Last edited: 31/10/2018
 *
 **********************************************************************/


#ifndef _QSORT_PTHREADS_H_
#define _QSORT_PTHREADS_H_

/* qsort parallel pthreads -- Sort vector v (of length n) using QuickSort and 2^p threads */
void Quicksort_Parallel( int *v, int n, int p);

#endif /* _QSORT_PTHREADS_H_ */



