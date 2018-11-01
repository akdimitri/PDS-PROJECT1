/**********************************************************************
 *
 * qsort-cilk.h -- Parallel implementation of QuickSort
 *
 * Dimitris Antoniadis <akdimitri@auth.gr>
 * Last edited: 31/10/2018
 *
 **********************************************************************/

#ifndef _QSORT_CILK_H_
#define _QSORT_CILK_H_

/* qsortseq -- Sort vector v (of length n) using Cilk API and QuickSort algorithm*/

void Quicksort_Cilk(int *a, int n, int p);

#endif /* _QSORT_CILK_H_ */
