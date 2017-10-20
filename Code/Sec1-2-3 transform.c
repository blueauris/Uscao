/*
ID: pallas21
LANG: C
TASK:transform
*/

/*1-2-2-transform.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 01- 05 
 */

#include <stdio.h>

#define MAX_N 10
// test function
int printMatrix(int in[MAX_N][MAX_N]);

// global variable
FILE *fin;
FILE *fout;

int ori_mat[MAX_N][MAX_N];
int tar_mat[MAX_N][MAX_N];
int cal_mat[MAX_N][MAX_N];
int temp_mat[MAX_N][MAX_N];

int N=0;
int step = 0;
int b_fit = 0;

// local functions
int getMatrix(int tar[MAX_N][MAX_N]);
int rotate();
int mirror();
int compare();
int copy(int tar[MAX_N][MAX_N], int sou[MAX_N][MAX_N]); 

//////////////////
//main function
/////////////////
int main () 
{
	fin  = fopen ("transform.in", "r");
	fout = fopen ("transform.out", "w");

	fscanf(fin, "%d%*c", &N);
	getMatrix(ori_mat);
//	printMatrix(ori_mat);
	getMatrix(tar_mat);
//	printMatrix(tar_mat);
	copy(cal_mat,ori_mat);
//	printMatrix(cal_mat);

	for (step = 1; step <= 3; ++step){
		rotate();
		if(compare() ==1 ){
			b_fit =1;
			break;
		}
	}

	if ( !b_fit){
		copy(cal_mat,ori_mat);
//		printMatrix(cal_mat);
		mirror();
		if(compare() ==1 ){
			b_fit =1;
			step =4;
		}
	}

	if ( !b_fit){
		for (step = 1; step <= 3; ++step){
			rotate();
			if(compare() ==1 ){
				b_fit =1;
				step =5;
				break;
			}
		}

	}

	if ( !b_fit){
		copy(cal_mat,ori_mat);
		if(compare() ==1 ){
			b_fit =1;
			step =6;
		}
		else {
			step = 7;
		}
	}
	fprintf(fout, "%d\n", step);
	fclose(fin);
	fclose(fout);
	return 0;
}
/////////////////
//main function ends
/////////////////
int getMatrix(int tar[MAX_N][MAX_N])
{
	int i,j;
	char str[MAX_N];
	for (i=0; i<N; ++i){
		fscanf(fin, "%s%*c",str);
		for (j=0; j<N; ++j){
			if (str[j] == '@'){
				tar[i][j] = 1;
			}
			else {
				tar[i][j] = 0;
			}
		}
	}
	return 0;
}

int rotate()
{
	int i, j;
	for (i=0; i<N; ++i){
		for (j=0; j<N; ++j){
			temp_mat[j][N-1-i] =cal_mat[i][j];
		}
	}
	copy(cal_mat, temp_mat);
	return 0;
}

int mirror()
{
	int i, j;
	for (i=0; i<N; ++i){
		for (j=0; j<N; ++j){
			temp_mat[i][N-1-j] =cal_mat[i][j];
		}
	}
	copy(cal_mat, temp_mat);
	return 0;
}

int compare()
{
	int i, j;
	for (i=0; i<N; ++i){
		for (j=0; j<N; ++j){
			if ( tar_mat[i][j] != cal_mat[i][j] )
				return 0;
		}
	}
	return 1;
}

int copy(int tar[MAX_N][MAX_N], int sou[MAX_N][MAX_N])
{
	int i, j;
	for (i=0; i<N; ++i){
		for (j=0; j<N; ++j){
			tar[i][j] = sou[i][j];
		}
	}
	return 0;
}

int printMatrix(int in[MAX_N][MAX_N])
{
	int i, j;
	for (i=0; i<N; ++i){
		for (j=0; j<N; ++j){
			printf("%d ", in[i][j]);
		}
		printf("\n");
	}
	return 0;
}
