/*
ID: pallas21
LANG: C
TASK:milk
*/

/*1-3-1-milk.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 04- 12 
 */

#include <stdio.h>
#include <stdlib.h>

// global constant
#define maxFarmer 5000

// class/struct define
typedef struct
{
	int price;
	int amount;
}SFarmer;

// global variable
FILE *fin;
FILE *fout;
int amuMilk=0;			//amount of milk need
int nFarm=0;		// number of farmer
SFarmer farmers[maxFarmer];

// local functions
int CompPri(const void *a, const void *b)
{
	return( (SFarmer*)a) ->price - ((SFarmer*)b)->price ;
}

//------------------------------------------------------------//
//---main function
int main () 
{
	int i=0;
	int restMilk = 0;
	int total = 0;
	fin  = fopen ("milk.in", "r");
	fout = fopen ("milk.out", "w");
	fscanf(fin,"%d %d%*c",&amuMilk,&nFarm);
	for (i=0; i<nFarm; ++i){
		fscanf(fin, "%d %d%*c", &farmers[i].price, &farmers[i].amount);
	}
	
	qsort( farmers, nFarm, sizeof(SFarmer), CompPri );

	restMilk = amuMilk;
	total = 0;
	for (i=0; i < nFarm && restMilk > 0; ++i){
		if ( restMilk >= farmers[i].amount ){
			restMilk -= farmers[i].amount;
			total += farmers[i].price * farmers[i].amount ;
		}
		else{
			total += farmers[i].price * restMilk;
			restMilk = 0;
		}
	}

	fprintf(fout, "%d\n", total);

	fclose(fin);
	fclose(fout);
	return 0;
}
//---main function ends

