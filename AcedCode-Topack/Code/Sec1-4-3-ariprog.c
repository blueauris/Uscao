/*
ID: pallas21
LANG: C
TASK:ariprog
*/

/*1-4-3-ariprog.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 10- 30
 */

#include <stdio.h>
#include <stdlib.h>

// global constant
#define maxB 160000			//双平方数最大值
#define maxNum 40000		//双平方数最大个数
#define maxAns 10000		//匹配项最大数量

// global variable
FILE *fin;
FILE *fout;
char bisBool[maxB] = {0};		//自然数列 双平方数所在位为 1
int bisList[maxNum] = {0};		//所有双平方数的排序表
int N = 0;					//所求等差数列长度
int M = 0;					//搜索双平方数的上界
int bisNum = 0;				//双平方数的个数

struct arrayNode
{
	int A;
	int dist;
};
struct arrayNode ans[maxAns] = {0};
int ansNum = 0;

// local functions
int init();
int search();
int printAnswer();
int compareInt(const void* elem1,const void* elem2);   
int comapreNode(const void* Node1,const void* Node2);

//----------------------main function-----------------------//
int main () 
{
	fin  = fopen ("ariprog.in", "r");
	fout = fopen ("ariprog.out", "w");

	init();
	search();
	printAnswer();
	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int init()
{
	int i,j,k;
	int numCol,num;
	fscanf(fin,"%d\n%d",&N,&M);

	k=0;
	for( i=0; i<=M; ++i){
		numCol = i*i;
		for( j=i; j<=M; ++j){
			num = numCol + j*j;
			if( bisBool[num] == 0 ){
				bisList[k]=num;
				++k;
				bisBool[num] = 1;
			}
		}
	}

	bisNum = k;
	qsort( bisList, bisNum, sizeof(bisList[0]), compareInt);
	return 0;
}

int search()
{
	int i,j,k;		//循环标志 分别记录数列a0, a1和检验数列后续项 时的位置
	int A0, dist, AK;	//等差数列的初项、公差、末项
	int AN, Wmax;	//数列最大项和最大公差
	int checkDist;	//公差匹配标志

	AN = bisList[bisNum-1];
	for( i=0; i<=bisNum-N; ++i){
		A0 = bisList[i];
		Wmax = AN-A0;
		for( j=i+1; j<=bisNum-N+1; ++j){
			dist = bisList[j] - A0;

			if( dist*(N-1) >Wmax ) break;
			AK = bisList[j];
			checkDist = 1;
			for( k=3; k<=N; ++k){
				AK +=dist;
				if( !bisBool[AK] ){
					checkDist = 0;
					break;
				}
			}

			if( checkDist ){
				ans[ansNum].A = A0;
				ans[ansNum].dist = dist;
				++ansNum;
			}
		}
	}
	
	qsort(ans, ansNum, sizeof(struct arrayNode), comapreNode);
	return 0;
}

int printAnswer()
{
	int i;
	if( ansNum == 0){
		fprintf( fout,"NONE\n");
		return 0;
	}

	for( i=0; i<ansNum; ++i){
		fprintf( fout, "%d %d\n",ans[i].A, ans[i].dist);
	}
	return 0;
}

int compareInt(const void * elem1, const void * elem2)
{
	return *(int*)elem1 - *(int*)elem2;
}

int comapreNode(const void* Node1,const void* Node2)
{
	int offset = ((struct arrayNode*)Node1)->dist - ((struct arrayNode*)Node2)->dist ;
	if( offset )
		return offset;
	else
		return  ((struct arrayNode *)Node1)->A - ((struct arrayNode *)Node2)->A;
}
//---local end-----------------------------------//

