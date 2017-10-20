/*
ID: pallas21
LANG: C
TASK:pprime
*/

/*1-5-2-pprime.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 11- 16 
 */

/*分析
  这道题有两种思路：
  1.用筛法求出1..1e8范围内的素数，然后判断每个素数是否是回文数。复杂度是O(n) 
  2.生成1..1e8范围内的回文数，然后判断它是否是素数。复杂度是O(√n*√n)=O(n)
  从复杂度来看两种思路没有差别。但思路1用筛法用素数要开O(n)的数组，在n=1e8是就是90M，超出了空间限制，而思路2的空间复杂度是O(1)的，所以倾向思路2。
  思路2判断质数时如果有预计算质数表，则效率进一步提高。1e8判质数的上限为10000，故选择预计算 10000以内的质数表保存。筛法数组仅需9K。

  设生成位数为L的回文数:
  若L是奇数，那么从小到大枚举 (L+1) div2位的数，然后复制翻转生成一个回文数；
  若L是偶数，那么从小到大枚举 L div 2位的数，然后复制翻转生成一个回文数。
  上诉两个过程交替进行就可以从小到大生成回文数了。

  可证明：
  除了11，任意偶数长度的回文数都不可能为质数，因为它能被11整除。
  证明简述:
  任意偶数长度的回文数可表示为A1A2..An-1AnAnAn-1..A2A1
  可分解为 A1(1+10^(2n-1)) +A2(1+10^(2n-3))x10+..+An(11)x10^(n-1)
  数学归纳法可证明 (10^(2n-1)+1) %11 =0 对任意n成立
 *
 *
 本程序算法:
 <10000的值,直接求出所有素数,再判断回文
 >10000，先生成10000以内素数表 ,然后生成奇数长度的回文数，再使用质数表判断
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
// global constant
#define SubN 10000 			//算法分界点
#define maxNumPri 1500			//10000 以内质数 1229个
#define maxNumPP  800			//10^8 内回文质数 779个

// global variable
FILE *fin;
FILE *fout;
int lower = 0;				//输入上限
int upper=0;				//输入下限
int* primeList = NULL;		//质数表
int  numPrime = 0;			//质数表长度
int* ppList = NULL;			//所求回文质数表
int  numPP = 0;				//回文质数个数

// local functions
int init();
int calculate();
int printAns();
int shutdown();
int genPrimeList(int up);				//生成小于up的质数表
int genPalinList(int low, int up);		//选出质数表中区间内的回文数
int calSubset(int low, int up);			//依次生成从low( >10000) 到up的所有奇位长回文数，并判断
int isPrime(int data);					//检查质数
int isPalin(int data);					//检查是否为回文
int isEvenhead(int data);				//检验首位是否为偶数
int genPalin(int data);					//生成以data为前半的奇数长度回文数
int divRange(int data);					//确定指定数的前半位所形成的新数的低区间
int strlen(char* str);


//----------------------main function-----------------------//
int main () 
{
	init();
	calculate();
	printAns();
	shutdown();
	return 0;
}
//----------------------main function ends-----------------//

//---local functions-----------------------------//
int init()
{
	fin  = fopen ("pprime.in", "r");
	fout = fopen ("pprime.out", "w");

	fscanf(fin, "%d %d",&lower,&upper );
	primeList = (int*)malloc(maxNumPri*sizeof(int));
	primeList[0] = 2;
	primeList[1] = 3;
	numPrime =2;
	ppList = (int*)malloc(maxNumPP*sizeof(int));

	return 0;
}

int calculate()
{
	if(upper <= SubN){
		genPrimeList(upper);
		genPalinList(lower, upper);
	}
	else{
		genPrimeList(SubN);
		genPalinList(lower, SubN);
		calSubset(lower, upper);
	}

	return 0;
}

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

int genPalinList(int LOW, int UP)		//选出质数表中区间内的回文数
{
	int mLow = LOW;
	int mUp = (UP <= SubN)? UP:SubN;
	int i;
	int temp;
	if( mLow > mUp)
		return 0;
	for( i=0; i<numPrime; ++i){
		temp = primeList[i];
		if( temp>=mLow && temp <=mUp && isPalin(temp) ){
			ppList[numPP] = temp;
			++numPP;
		}
	}
	return 0;
}

int calSubset(int low, int up)	//依次生成从low( >10000) 到up的所有奇位长回文数，并判断是否为质数
{
	int i;			//循环变量
	int mLow,mUp;	//循环上下限
	int curData;	//生成的待判回文数	
	low = (low>SubN)? low:SubN;

	mLow = divRange(low);
	mUp = divRange(up) + 1;

	for( i =mLow; i<=mUp; ++i){
		if( isEvenhead(i) )
			continue;
		curData = genPalin(i);
		if(curData < low )
			continue;
		if(curData > up)
			break;
		if( isPrime(curData) )
		{
			ppList[numPP] = curData;
			++numPP;
		}
	}
	return 0;
}

int printAns()
{
	int i;
	for( i=0; i<numPP; ++i){
		fprintf(fout, "%d\n",ppList[i]);
	}
	return 0;

}

int shutdown()
{
	free(ppList);
	free(primeList);
	fclose(fin);
	fclose(fout);
	return 0;
}
//---local end-----------------------------------//

//---tool functions------------------------------//
int strlen(char* str)
{
	char *pos = str;
	while( *pos != '\0' )
		++pos;
	return pos - str ;
}

int isPrime(int data)		//检查质数
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

int isPalin(int data)		//检查数是否为回文
{
	char str[10] ="";
	int len;
	int i;
	sprintf(str,"%d", data);
	len = strlen(str);
	for( i=0; i<(len/2); ++i){
		if( str[i] != str[len-i-1] )
			return 0;
	}
	return 1;
}

int isEvenhead(int data)	//检验首位是否为偶数
{
	int boolHead = 0;
	int temp;
	if(data>1000)
		temp = data/1000;
	else
		temp = data/100;
	boolHead = temp%2;
	return !boolHead;
}

int genPalin(int data)	//生成以data为前半的奇数长度回文数
{
	int m;
	char str[12];
	int len = 0;
	int i;
	sprintf(str, "%d", data);
	len = strlen(str);

	for( i=0; i<len-1; ++i){
		str[2*len-2-i] = str[i];
	}
	str[2*len-1] ='\0';
	len = strlen(str);

	for(m=0, i=0; i<len; ++i){
		m =str[i] -'0' +m*10;
	}
	return m;
}

int divRange(int data)	
//确定指定数的前半位所形成的新数的低区间
//如 123456789 得到 12345
{
	int m;
	if(data > 10000000)
		m = 10000;
	else if( data > 1000000)
		m = data/1000;
	else if( data > 100000 )
		m = 1000;
	else if( data >= 10000)
		m = data/100;
	else
		m = 100;
	return m;
}
//---tool functions end---------------------------------------//
