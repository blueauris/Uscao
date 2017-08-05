/*
ID: pallas21
LANG: C
TASK:barn1
*/

/*1-3-2-barn1.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 04- 12 
 */


#include <stdio.h>
#include <stdlib.h>
#define MAXBARN 200

// global variable
FILE *fin;
FILE *fout;

int M = 0;  	// number of wood block
int S = 0;			// number of barn
int C =0;			// number of cows
int cow[MAXBARN]= {0};		// the position of cow
int blankLen[MAXBARN] = {0}; // the length of the blank barn
int maxWoodLen = 0;
int numWood = 1;

// local functions
int CmpInt(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}
int RevCmpInt(const void *a, const void *b)
{
	return -(*(int*)a - *(int*)b);
}

//---main function
int main () 
{
	int i=0;
	fin  = fopen ("barn1.in", "r");
	fout = fopen ("barn1.out", "w");
	fscanf( fin, "%d %d %d%*c", &M, &S, &C);
	if ( C == 1){
		fprintf( fout, "1\n");
		return 0;
	}

	for ( i = 0; i < C; ++i){
		fscanf( fin, "%d%*c", &cow[i] );
	}
	qsort(cow, C, sizeof(cow[0]), CmpInt);
	for ( i=1; i < C; ++i){
		blankLen[i-1] = cow[i] - cow[i-1] - 1;
	}
	qsort(blankLen, C, sizeof(blankLen[0]), RevCmpInt);

	maxWoodLen = cow[C-1] -cow[0] + 1;
	i=0;
	numWood = 1;
	while ( blankLen[i] != 0 && numWood < M){
		maxWoodLen -= blankLen[i];
		++i;
		++numWood;
	}

	fprintf( fout, "%d\n", maxWoodLen);

	fclose(fin);
	fclose(fout);
	return 0;
}
//---main function ends

