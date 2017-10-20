/*
ID: pallas21
LANG: C
TASK:sprime
*/

/*1-5-3-sprime.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 11- 18 
 */

/* 分析:
 * 长度为N的所有特殊质数，如果去除右侧最低位，
 剩下的字符组成的新数必是长度为N-1的特殊质数
 即长度为N的所有特殊质数一定是由长度为N-1的特殊质数增加右侧一位所得
 *
 * 算法：
 从N=1开始，求出特殊质数并保存。
 用长度N=m时的特殊质数表，在右侧增加一个数字并检验来生成N=m+1的数表
 N=1 的特殊质数为 2 3 5 7
 从长度N=m的特殊质数推导到N=m+1的特殊质数，在右侧可加的数字为 1 3 7 9四个
 为提高效率，可预生成 10^(n/2) 以内的质数表用于质数判断。
 */

#include <stdio.h>
#include <malloc.h>
// global constant
#define maxN 8				//最大范围
#define maxNumPri 1500	//10000 以内质数 1229个
#define aveDigNum 4		//尾部可加的数字个数

// global variable
FILE *fin;
FILE *fout;

int souN = 0;				//原始输入
int* primeList = NULL;		//质数表
int  numPrime = 0;			//质数表长度
int* spMatr[maxN+2];	//所求特殊质数矩阵
//spMat中 spMat[0] 是四个可加尾数 spMat[i] 为N=i时的特殊质数表 spMat[i][0] 为此时的质数个数
int digit[aveDigNum] = {1,3,7,9};		//尾部数字
int prime1[5] = {4,2,3,5,7};	//1位特殊质数

// local functions
int init();
int calculate();
int printAns();
int shutdown();
int genPrimeList(int up);		//生成小于up的质数表
int isPrime(int data);			//验证质数

//----------------------main function-----------------------//
int main () 
{
	fin  = fopen ("sprime.in", "r");
	fout = fopen ("sprime.out", "w");
	init();
	calculate();
	printAns();
	shutdown();
	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends-----------------//

//---local functions-----------------------------//
int init()
{
	fscanf(fin, "%d", &souN);
	primeList = (int*)malloc(maxNumPri*sizeof(int));
	primeList[0] = 2;
	primeList[1] = 3;
	numPrime =2;
	spMatr[0] = NULL;
	spMatr[1] = prime1;
	return 0;
}

int calculate()
{
	int i,j,k;
	int base10=1;
	int preDigit=0;			//取上一层数组中的第一个
	int curDigit = 0;		//当前层的数
	int curNum = 0;			//当前层已选到的数
	for(i=0; i<(souN+1)/2; ++i){
		base10 *=10;
	}
	genPrimeList(base10);

	for( i=2; i<=souN; ++i){		//向下递推一层
		spMatr[i] =(int*)malloc(sizeof(int) * spMatr[i-1][0]*4 );
		curNum=0;
		for( j=1; j<= spMatr[i-1][0] ; ++j){		//该层取后一个质数
			preDigit = spMatr[i-1][j];

			for( k=0; k<aveDigNum; ++k){			//后一个可用数字
				curDigit = 10*preDigit + digit[k];
				if( isPrime(curDigit) ){
					++curNum;
					spMatr[i][curNum] = curDigit;
				}
			}
		}
		spMatr[i][0] = curNum;
	}
	return 0;
}

int printAns()
{
	int i;
	for(i=1; i<= spMatr[souN][0]; ++i){
		fprintf(fout,"%d\n", spMatr[souN][i]);
	}
	return 0;
}

int shutdown()
{
	int i;
	for(i=2; i<= souN; ++i){
		free(spMatr[i]);
	}

	return 0;
}
//---local end-----------------------------------//

//---tool functions------------------------------//
int genPrimeList(int up)		//生成小于up的质数表
{	
	int i,j;
	int bPrime;
	for( i=5; i<=up; ++i){
		if( isPrime(i) ){
			primeList[numPrime] = i;
			++numPrime;
		}
	}
	return 0;
}

int isPrime(int data)		//验证质数
{
	int i;
	for( i=0; i<numPrime; ++i){
		if( data == primeList[i])
			return 1;
		if( data % primeList[i] == 0){
			return 0;
		}
	}
	return 1;
}

//---tool functions end---------------------------------------//
