/**********************************************************************
 *
 * results.c -- Stores test results
 *
 * Dimitris Antoniadis <akdimitri@auth.gr>
 * Last edited: 31/10/2018
 *
 **********************************************************************/

#include <stdio.h>

void write_results_to_file( double s[10][15], double d[10][15], double p[10][15][8]){

	FILE *fp;

	fp = fopen("results_cilk.txt", "a");
	fprintf(fp, "\r\n");
	fprintf(fp, "Sequential Quicksort, \r\n");
	fprintf(fp, "n \r\n");
	int i,k;
	for( i = 0; i < 15 ; i++){

		fprintf(fp,"%d ", i+12);
		for( k = 0; k < 10; k++){
			fprintf(fp, "%f ", s[k][i]);
		}
		fprintf(fp, "\r\n");
	}

	fprintf(fp, "\r\n");

	fprintf(fp, "Default Quicksort,  \r\n");
	fprintf(fp, "n \r\n");
	for( i = 0; i < 15 ; i++){

		fprintf(fp,"%d ", i+12);
		for( k = 0; k < 10; k++){
			fprintf(fp, "%f ", d[k][i]);
		}
		fprintf(fp, "\r\n");
	}

	fprintf(fp, "\r\n");
	fprintf(fp, "CILK Quicksort, \r\n");

	int j;
	for( i = 0; i < 15 ; i++){
		fprintf(fp, "n = %d \r\n", i + 12);
		for( j = 0; j < 8; j++){
			fprintf(fp,"%d ", j+1);
			for( k = 0; k < 10; k++){
				fprintf(fp, "%f ", p[k][i][j]);
			}
			fprintf(fp, "\r\n");
		}
		fprintf(fp, "\r\n");
	}
	fclose(fp);
}
