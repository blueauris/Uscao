/*
ID: pallas21
LANG: C
TASK:dualpal
*/

/*1-2-3-dualpal.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 01- 30 
 */

#include <stdio.h>
// global constant
#define WIDTH 32
// class/struct define
typedef struct
{
	int data[WIDTH];
	int base;
	int len;
} digit;

// global variable
FILE *fin;
FILE *fout;
digit tar;

// local functions
int isDulPal(int sou);
int isPal(digit* pDigit);
int convertBase(digit* pDigit, int sou, int base);


//------------------------------------------------------------//
//---main function
int main () 
{
	fin  = fopen( "dualpal.in", "r");
	fout = fopen( "dualpal.out", "w");
	int N=0;
	int S=0;

	int n=0;			//计数
	int sou = 0;		//当前值
	fscanf( fin, "%d %d%*c", &N, &S);
	sou = S+1;
	while ( n < N ) {
		if (isDulPal( sou) ) {
			fprintf( fout, "%d\n", sou);
			++n;
		}
		++sou;
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
//---main function ends
//------------------------------------------------------------//


//---local functions------------------------------------------//
int isDulPal(int sou)
{
	int i;
	int numDul = 0;
	for (i=2; i<=10; ++i){
		convertBase( &tar, sou, i);
		if (isPal( &tar) ){
			++numDul;
			if (numDul >= 2){
				return 1;
			}
		}
	}
	return 0;
}

int isPal(digit* pDigit)
{
	int i =0;
	int len = pDigit->len;
	for (i=0; i <= (len/2-1); ++i){
		if (pDigit->data[i] != pDigit->data[len-i-1]){
			return 0;
		}
	}
	return 1;
}

int convertBase(digit* pDigit, int sou, int base)
{
	int i=0;
	int len =0;
	pDigit->base = base;
	while (sou > 0){
		pDigit->data[WIDTH - i -1] = sou % base;
		sou /= base;
		++i;
	}
	len =i;
	for (i=0;  i< len; ++i){
		pDigit->data[i] = pDigit->data[WIDTH - len + i];
	}
	pDigit->len = len;
	return len;
}
//---local end------------------------------------------------//

