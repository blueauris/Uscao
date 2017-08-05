/*
ID: pallas21
LANG: C
TASK:crypt1
*/

/*1-3-5-crypt1.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 10- 05 
 */

#include <stdio.h>
//本程序限定条件为五个整数 采取生成两个整数 计算校验其余三个的做法
//用M+1位N进制数对应生成整数
// global constant
#define M 5

// global variable
FILE *fin;
FILE *fout;

int N = 0;			//字符总数，同时为多进制数的基
int ch[9];			//9个可能字符
int digit[M+1] = {0};		//用M+1位N进制数
int S[5] = {0};			//限定条件的5个整数

int total = 0;		//结果总数

// local functions
int gen();			//生成五个数
int check();		//验证三个整数
int inCharList(int temp);	//数字在给定字符中

//----------------------main function-----------------------//
int main () 
{
	int i = 0;
	fin  = fopen ("crypt1.in", "r");
	fout = fopen ("crypt1.out", "w");

	fscanf(fin,"%d\n",&N);
	for( i=0; i<N; ++i)
		fscanf(fin, "%d", &ch[i]);

	while( digit[M] == 0 )
	{
		for( i=0; i<=M-1; ++i)
		{
			if(digit[i] < N) break;
			digit[i] = 0;
			++digit[i+1];

		}

		if(digit[M] ==0)
		{
			gen();
			if( check() )
				++total;
		}
		++digit[0];

	}
	
	fprintf(fout,"%d\n",total);
	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int gen()
{
	int i;
	S[0] =ch[ digit[0] ] + ch[ digit[1] ]*10 + ch[ digit[2] ]*100;
	S[1] =ch[ digit[3] ] + ch[ digit[4] ]*10;
	S[2] = S[0] * ch[ digit[3] ];
	S[3] = S[0] * ch[ digit[4] ];
	S[4] = S[0] * S[1];

	return 0;
}

int check()
{
	int i;
	int tempInt;
	if(S[2]>=1000) return 0;
	if(S[3]>=1000) return 0;
	if(S[4]>=10000) return 0;
	
	for( i=2; i<=4; ++i)
	{
		while(S[i] >0)
		{
			tempInt = S[i]%10;
			if( !inCharList(tempInt) ) return 0;
			S[i] = S[i]/10;
		}
	}
	return 1;
}

int inCharList(int temp)
{
	int i;
	int found = 0;
	for(i=0; i<N; ++i)
	{
		if( ch[i] == temp )
			found = 1;
	}
	return found;
}

//---local end-----------------------------------//



