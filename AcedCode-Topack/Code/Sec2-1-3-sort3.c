/*
ID: pallas21
LANG: C
TASK:sort3
*/

/*2-1-3-sort3.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2009- 05- 16 
 */

/* 算法提要:
 * 用num[i]记录i(1,2,3)出现的个数。排序后一定是num[1]个1，num[2]个2，num[3]个3这3段。 
 * pos[i,j]记录在第i段中的j的个数。
 * ans:=pos[1,2]+pos[1,3]+max(pos[2,3],pos[3,2]);
 *
 * pos[1,2]+pos[1,3] 是所有处于 1位的2和3的数量,
 * pos[2,1]+pos[3,1] 是不在正确位置的1的数量，这两个和是相同的。第一步求这个和，也就是让所有1归位

 * 此操作之后，存在两种情况。
 * 一：原序列中不存在 三值互换的现象，那么 d[2,3]与d[3,2]应该是相同的。max算子不起作用。
 * 二:原序列中存在 三值互换的现象。原d[2,3]与d[3,2]变为pos'[2,3]与pos'[3,2]
 * 则pos[2,3]与pos[3,2]中必有一个不变而另一个在增大，且增大的量在数值上等于原三值交换的次数。
 * 由于交换是相对的，pos'[2,3]与pos'[3,2]必相等，又由于其中有一个值没有变动，所以该值也就等于原d[2,3]与d[3,2]中的最大值。 
 * 取这个最大值就可以让 2 3 同时归位。
 * 整合两步，问题得解 
 * 
 *
 */
#include <stdio.h>
// global constant
#define MAXN 1001

// global variable
FILE *fin;
FILE *fout;
int caseN = 0;
int list[MAXN] = {0};	//列表全体
int num[4] ={0};		//用num[i]记录i(1,2,3)出现的个数
int pos[4][4] ={0}; 	//pos[i,j]记录在第i段中的j的个数
int ans = 0;

// process functions
int init();
int getData();
int calculate();
int printAns();
int shutdown();

// tool functions
int max(int a,int b)
{
	return (a>b)?a:b;
}
// test function

//----------------------main function--------------//
int main () 
{
	init();
	getData();
	calculate();
	printAns();
	shutdown();
	return 0;
}
//----------------------main function ends--------//


//--- process functions --------------------------//
int init()
{
	fin  = fopen ("sort3.in", "r");
	fout = fopen ("sort3.out", "w");
	return 0;
}

int getData()
{
	int i;
	int tempInt;
	fscanf(fin, "%d", &caseN);
	for( i=1; i<=caseN; ++i){
		fscanf(fin, "%d", &tempInt);
		list[i] = tempInt;
		++num[tempInt];
	}
	return 0;
}

int calculate()
{
	int i;
	int segment;		//当前所在的段
	for( i = 1; i<=caseN; ++i){
		if( i<=num[1] )
			segment = 1;
		else if( i<=(num[2]+num[1]) )
			segment = 2;
		else
			segment =3;
		switch( list[i] ){
			case 1:
				++pos[segment][1];
				break;
			case 2:
				++pos[segment][2];
				break;
			case 3:
				++pos[segment][3];
				break;
		}	//switch
	}	// for
	ans = pos[1][2] + pos[1][3] + max( pos[2][3],pos[3][2]);
	return 0;
}

int printAns()
{
	fprintf(fout,"%d\n",ans);
	return 0;
}

int shutdown()
{
	fclose(fin);
	fclose(fout);
	return 0;
}
//--- process functions end-----------------------//

