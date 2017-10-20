/*
ID: pallas21
LANG: C
TASK:preface
*/

/*2-2-1-preface.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2010- 04- 04 
 */

/*算法提要:
 *对于数值x，其罗马字母表示方法唯一确定,可用函数分别计算各字符在数值x中出现的个数
 *记函数SingleNumP(x)为字符P在数值x中出现的次数，TotalNumP(x)为P在[0,x]中出现的总次数，则可知函数TotalNumP即为SingleNumP在[0,x]上的积分
 *可知函数SingleNumP为分段周期函数，周期取决于P字符。记r_seq为SingleNumP函数在x前所有完整周期的右边界的最大值，记函数SeqNumP(x)等价于TotalNumP(r_seq)，则SeqNumP(x)即为P字符在x前所有完整周期中出现的次数总和，同时可设定函数RestNumP(x)为x之前最后一个不完整周期中的P字符出现的总数。则 TotalNumP(x) = RestNumP(x) + SeqNumP(x)
 *对应各字符的SingleNum,TotalNumP周期及解析式如下：
 *
 * I: 周期=5  SeqNum=x/5*7
 * x%5        SingleNum        TotalNum
 * =0           0             0 + SeqNum
 * =1           1             1 + SeqNum
 * =2           2             3 + SeqNum
 * =3           3             6 + SeqNum
 * =4           1             7 + SeqNum
 *
 * V: 周期=10  SeqNum=x/10*5 
 * x%10         SingleNum        TotalNum
 * [0,4)        0             0                + SeqNum
 * [4,9)        1              (x%10-3)        + SeqNum
 * =9           0                            5 + SeqNum
 *
 * X: 周期=50  SeqNum=x/50*75
 * x%50        SingleNum        TotalNum
 * [0,9)        0             0               + SeqNum
 * [9,19)       1              (x%50-8)       + SeqNum
 * [19,29)      2             2(x%50-18) + 10 + SeqNum
 * [29,39)      3             3(x%50-28) + 30 + SeqNum
 * =39          4             4          + 60 + SeqNum
 * [40,49)      1              (x%50-39) + 64 + SeqNum
 * =49          2             2          + 73 + SeqNum
 *
 * L: 周期=100  SeqNum=x/100*50 
 * x%100         SingleNum        TotalNum
 * [0,40)        0             0                  + SeqNum
 * [40,90)       1              (x%100-39)        + SeqNum
 * [90,99]       0                            50  + SeqNum
 *
 * C: 周期=500  SeqNum=x/500*750
 * x%500         SingleNum        TotalNum
 * [0,90)        0             0                  + SeqNum
 * [90,190)      1              (x%500-89)        + SeqNum
 * [190,290)     2             2(x%500-189) + 100 + SeqNum
 * [290,390)     3             3(x%500-289) + 300 + SeqNum
 * [390,400)     4             4(x%500-389) + 600 + SeqNum
 * [400,490)     1              (x%500-399) + 640 + SeqNum
 * [490,499]     2             2(x%500-489) + 730 + SeqNum
 * 
 * D: 周期=1000  SeqNum=x/1000*500
 * xR1000        SingleNum        TotalNum
 * [0,400)       0             0                + SeqNum
 * [400,900)     1             (x%1000-399)     + SeqNum
 * [900,999]     0                          500 + SeqNum
 *
 * M: 周期=5000 
 * x%5000        SingleNum        TotalNum
 * [0,900)       0             0
 * [900,1900)    1             x-899
 * [1900,2900)   2             2(x-1899) + 1000
 * [2900,3900)   3             3(x-2899) + 3000
 */

#include <stdio.h>
// global constant
#define MaxN 3500 

// global variable
FILE *fin;
FILE *fout;
int caseN;
int value[]={ 1, 5, 10, 50, 100, 500, 1000};
char symbles[] = { 'I', 'V' , 'X', 'L', 'C', 'D', 'M'};
int count[7] = {0};

// process functions
int calculate();
int printAns();

//----------------------main function--------------//
int main () 
{
	fin  = fopen ("preface.in", "r");
	fout = fopen ("preface.out", "w");
	fscanf( fin, "%d", &caseN);

	calculate();
	printAns();

	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends--------//


//--- process functions --------------------------//

int calculate()
{
	int restN = 0;	//除去整周期后的余数
	int restnum = 0;	
	
	// char: I = 1  sequence: 5  
	restN = caseN % 5;
	if (restN == 0) restnum = 0;
	else if (restN == 1) restnum = 1;
	else if (restN == 2) restnum = 3;
	else if (restN == 3) restnum = 6;
	else if (restN == 4) restnum = 7;
	count[0] = restnum + caseN/5*7;

	// char: V = 5   sequence: 10  
	restN = caseN % 10;
	if (restN >= 0 && restN < 4) 	restnum = 0;
	else if (restN >= 4 && restN < 9) restnum = restN - 3;
	else if (restN == 9) restnum = 5;
	count[1] = restnum + caseN/10*5;

	// char: X = 10  sequence: 50  
	restN = caseN % 50;
	if (restN >= 0 && restN < 9) 	restnum = 0;
	else if (restN >= 9 && restN < 19) restnum = restN - 8;
	else if (restN >= 19 && restN < 29) restnum = 2 * (restN - 18) + 10;
	else if (restN >= 29 && restN < 39) restnum = 3 * (restN - 28) + 30;
	else if (restN == 39) restnum = 64;
	else if (restN >= 40 && restN < 49) restnum = (restN - 39) + 64;
	else if (restN == 49) restnum = 75;
	count[2] = restnum + caseN/50*75;

	// char: L = 50  sequence: 100  
	restN = caseN % 100;
	if (restN >= 0 && restN < 40) 	restnum = 0;
	else if (restN >= 40 && restN < 90) restnum = restN - 39;
	else if (restN >= 90 && restN <= 99) restnum = 50;
	count[3] = restnum + caseN/100*50;

	// char: C = 100  sequence: 500  
	restN = caseN % 500;
	if (restN >= 0 && restN < 90) 	restnum = 0;
	else if (restN >= 90 && restN < 190) restnum = restN - 89;
	else if (restN >= 190 && restN < 290) restnum = 2 * (restN - 189) + 100;
	else if (restN >= 290 && restN < 390) restnum = 3 * (restN - 289) + 300;
	else if (restN >= 390 && restN < 400) restnum = 4 * (restN - 389) + 600;
	else if (restN >= 400 && restN < 490) restnum =  (restN - 399) + 640;
	else if (restN >= 490 && restN <= 499) restnum = 2 * (restN - 489) + 730;
	count[4] = restnum + caseN/500*750;

	// char: D = 500  sequence: 1000  
	restN = caseN % 1000;
	if (restN >= 0 && restN < 400) 	restnum = 0;
	else if (restN >= 400 && restN < 900) restnum = restN - 399;
	else if (restN >= 900 && restN <= 999) restnum = 500;
	count[5] = restnum + caseN/1000*500;

	// char: M = 1000  sequence: 5000  
	restN = caseN % 5000;
	if (restN >= 0 && restN < 900) 	restnum = 0;
	else if (restN >= 900 && restN < 1900) restnum = restN - 899;
	else if (restN >= 1900 && restN < 2900) restnum = 2 * (restN - 1899) + 1000;
	else if (restN >= 2900 && restN < 3900) restnum = 3 * (restN - 2899) + 3000;
	count[6] = restnum + caseN/5000*7500;

	return 0;
}

int printAns()
{
	int i;
	for (i=0; i<7; ++i)
	{
		if( count[i] != 0 )
			fprintf(fout,"%c %d\n", symbles[i], count[i]);
	}
//	fprintf(fout,"\n");
	return 0;
}

//--- process functions end-----------------------//

