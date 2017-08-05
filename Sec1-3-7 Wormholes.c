/*
ID: pallas21
LANG: C
TASK:wormhole
*/

/*1-3-7-wormhole.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2017- 04- 24 
 */

/*算法提要:
 *基本思路 由于数据范围很小（1<=N<=12）所以只要枚举所有组合情况然后判断是否有环
 
 *当有12个虫洞时，共有6个配对
  配对组合总数为 C(12,2)C(10,2)C(8,2)C(6,2)C(4,2)C(2,2)/P(6,6) = 10395 种，每个组合可从12个虫洞中任意一个开始进入
  故最多判断次数为 10395*12= 124740次。穷举法可用，但可能超时，需剪枝。

 *考察贝茜牛的运动特点。牛只能沿X轴向右运动，即从某个虫洞出发的牛只能沿X轴正向移动到同一行的下一个虫洞，不能跨行移动。
  当循环能够发生，牛必然要从一个洞离开，再进入下一个洞。因为虫洞不能重叠，则牛离洞后必须自行行进。可推得，这两个虫洞必然在同一行且直达（中间没有其他虫洞）。为讨论方便，称这两个在同一行且直达的虫洞为一个水平组，于是有重要结论，只有当至少存在一个水平组，循环才有可能。如果12个虫洞都不能构成一个水平组，无法实现循环。
  继续考察。对一个水平组，若这两个虫洞被配对为一对，则牛可在这两个虫洞间循环，所以数据中有水平组且该组两虫洞配对的方案均为可用。
  若一个水平组的虫洞未配对，则这两个虫洞分别为两个传送的出口和入口（左出右进），则至少应有另外两个虫洞对应于该组虫洞作为入口与出口，由前述推论，那组虫洞也应为一个水平组，且未被配对。故可推导知，数据中有水平组且组中虫洞均未配对时，仅当至少有两组及以上水平组时，配对方案可能成立。仅有一个水平组且未配对时，配对方案不可用。
  综合以上，可得结论，数据中同一行且相邻的虫洞的数目与所求结果之间关系如下：
  1.无任何两个虫洞在同一行，则结果为0
  2.有且只有两个虫洞在同一行，结果为剩余虫洞任意分为两个一组的总组合数，例如N=12时 S=C(10,2)C(8,2)C(6,2)C(4,2)C(2,2)/P(5,5) = 945
  3.有两组以上在同一行的虫洞，分情况讨论
    a.各组均不在同一行，
    b.有若干组在同一行，
  

 */
#define LTEST		//测试代码

#ifdef LTEST
#else
#endif

#include <stdio.h>
// global constant
#define N 

// global variable
FILE *fin;
FILE *fout;

// process functions
int init();
int getData();
int calculate();
int printAns();
int shutdown();

// tool functions

// test function
int  testScene();
int  testRound();

// string functions
int strlen(char* str);
int strncpy(char* tar, char *sou,int length);
int strcat(char *dest,char *src);
int strcomp(char * str1, char *str2);

//----------------------main function--------------//
int main () 
{
	init();
	calculate();
	printAns();
	shutdown();
	return 0;
}
//----------------------main function ends--------//


//--- process functions --------------------------//
int init()
{
	fin  = fopen ("PROGRAM_NAME.in", "r");
	fout = fopen ("PROGRAM_NAME.out", "w");
	return 0;
}

int getData()
{
	return 0;
}

int calculate()
{
	return 0;
}

int printAns()
{
	return 0;
}

int shutdown()
{
	fclose(fin);
	fclose(fout);
	return 0;
}
//--- process functions end-----------------------//

//--- tool functions -----------------------------//


//---tool functions end---------------------------//

//---------test function--------------------------//
int  testScene()
{
	return 0;
}

int  testRound()
{
	return 0;
}
//---test functions end---------------------------//


//---string functions-----------------------------//
int strlen(char* str)
{
	char *pos = str;
	while( *pos != '\0' )
		++pos;
	return pos - str ;
}

int strcat(char* tar, char* sou)
{   
	char *pos = tar;   
	while(*pos != '\0')
		++pos;   
	while( *sou != '\0'){
		*pos = *sou;
		++pos, ++sou;
	}   
	return  0;   
} 

int strncpy(char* tar, char *sou,int length)
{
	int len = strlen(sou);
	len = (len<length)?len:length;
	int i = 0;
	for (i =0; i <len;i++)
	{
		tar[i] = sou[i];
	}
	tar[i]='\0';
	return 0;
}

int strcomp(char * str1, char *str2)
{
	if (strlen(str1) != strlen(str2))
		return -1;
	while( *str1 == *str2)
	{
		if( *str1 != '\0' )
			str1++,str2++;
		else return 0;
	}
	return 1;
}
//---string functions end-------------------------//
