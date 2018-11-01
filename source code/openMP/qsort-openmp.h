/**********************************************************************
 *
 * qsort-openmp.h -- Parallel implementation of QuickSort
 *
 * Dimitris Antoniadis <akdimitri@auth.gr>
 * Last edited: 31/10/2018
 *
 **********************************************************************/
#ifndef _QSORT_OPENMP_H_
#define _QSORT_OPENMP_H_

/* qsortseq -- Sort vector v (of length n) using openMP and QuickSort algorithm*/
void Openmp_Quicksort( int *v, int n, int p);

#endif /* _QSORT_OPENMP_H_ */