/*
ID: pallas21
LANG: C
TASK:numtri
*/

/*1-5-1-numtri.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 11- 13 
 */

/* 简单的动态规划
 * 到达第i层第j个 可有多条路径 但最大值必唯一
 * 设num[i,j]为某位置原有数据，dp[i,j]表示最大的分数 
 * 状态转移方程:
 *   dp[i,j]=max(dp[i-1,j],dp[i-1,j+1])+num[i,j] 从上往下 最后搜索最大值 需处理三角形边界
 * 或dp[i,j]=max{dp[i+1,j],dp[i+1,j+1])+num[i,j] 自下而上 第一行即为最大值 需存储三角形所有项
 * 考虑便于存储，本程序采用自上而下方案
 */

#include <stdio.h>
#include <malloc.h>
// global constant
#define maxR 1000 

// global variable
FILE *fin;
FILE *fout;

int  colR=0;			//行数
int* dataList=NULL;		//输入数据
int* dpList=NULL;		//上一行计算结果
int* bufferList = NULL;	//当前行结果缓存
int maxSum = 0;			//结果最大值

// local functions
int init();
int calculate();
int printAns();
int shutdown();

int max(int x, int y)
{
	return (x>y)?x:y;
}

//----------------------main function-----------------------//
int main () 
{
	fin  = fopen ("numtri.in", "r");
	fout = fopen ("numtri.out", "w");

	init();
	calculate();
	printAns();
	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int init()
{
	int i;
	fscanf(fin, "%d", &colR);
	dataList = (int*)malloc(sizeof(int)*(colR+2));
	dpList = (int*)malloc(sizeof(int)*(colR+2));
	bufferList = (int*)malloc(sizeof(int)*(colR+2));
	for( i=0; i<=colR+1; ++i){
		bufferList[i] = dpList[i] = 0;
	}
	return 0;
}

int calculate()
{
	int i,j;
	int* swapList = NULL;
	if( colR ==1 ){
		fscanf(fin, "%d", &maxSum);
		return 0;
	}

	for( i=0; i<colR; ++i){
		for( j=0; j<=i; ++j){
			fscanf(fin, "%d", dataList+j);
		}
		fscanf(fin, "%*c");

		bufferList[0] = dataList[0] + dpList[0];	//处理首项边界
		for( j=1; j<=i; ++j){
			bufferList[j] = dataList[j] + max(dpList[j], dpList[j-1] );
		}
		swapList = bufferList, bufferList = dpList, dpList = swapList; 

	}
	
		for( maxSum=0,i=0; i<=colR; ++i){
			maxSum = max(maxSum, dpList[i]);
		}
	return 0;
}

int printAns()
{
	fprintf(fout, "%d\n", maxSum);
	return 0;
}

int shutdown()
{
	free(dataList);
	free(dpList);
	free(bufferList);
	return 0;
}
//---local end-----------------------------------//

