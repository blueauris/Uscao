/*
ID: pallas21
LANG: C
TASK:frac1
*/

/*1-0-1-frac1.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2009- 03- 02 
 */

/*算法提要:
 * 生成所有的真分数,加入列表,排序后输出
 */

#include <stdio.h>
// global constant
#define MAXN 160
#define NUMFRAC 8000	//分母小于160的真分数总量为7905个
int primes[] = {2,3,5,7,11,13,17,19,23,	29,
				31,37,41,43,47,53,59,61,67,71,
				73,79,83,89,97,101,103,107,109,
				113,127,131,137,139,149,151,157};	//为160以下的质数
int NumPrime = sizeof(primes)/sizeof(int);

// global variable
FILE *fin;
FILE *fout;
struct Fraction			//fraction 分数
{
	int nume;		//numerator   分子
	int deno;		//denominator 分母
};

struct Fraction trueFracAr[NUMFRAC]={0};		//真分数表
int numTrueFA=0;			//真分数总数

int caseN;		//输入的N
int relaPriAr[MAXN+1] = {1};	// relatively-prime 互质数表 relaPriAr[p] = 1 表示p与 输入数i互质
int nTotalRelPri = 0;

// local functions
int init();
int calculate();
int printAns();
int shutdown();
int genRelaPriList(int upper);
int quickSort(int left, int right);		//对真分数表快速排序
int directSort(int left );	//个数为3个时，直接排序
int compFrac(int m, int n);			//比较真分数表中下标为m，n的两个元素
int swapFrac(int m, int n);				//交换真分数表中下标为m，n的两个元素

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
	fin  = fopen ("frac1.in", "r");
	fout = fopen ("frac1.out", "w");
	fscanf(fin, "%d", &caseN);

	trueFracAr[0].nume = 0;
	trueFracAr[0].deno = 1;		// 加入分数 0/1
	trueFracAr[1].nume = 1;
	trueFracAr[1].deno = 1;		// 加入分数 1/1
	numTrueFA = 2;				// 已有2个分数
	return 0;
}

int calculate()
{
	int deno,nume;
	for( deno = 2; deno <= caseN; ++deno){
		//生成对应于deno的互质数表
		genRelaPriList(deno);
		//按互质数表生成以deno为分母的所有真分数并加入分数表中
		for(nume = 1; nume<deno; ++nume){
			if( relaPriAr[nume]){
				trueFracAr[numTrueFA].nume = nume;
				trueFracAr[numTrueFA].deno = deno;
				++numTrueFA;		// 加入分数 nume/deno
			}
		}
	}
	//排序真分数表
	swapFrac( 1, numTrueFA-1);
	quickSort(1, numTrueFA-2);

	return 0;
}

int printAns()
{
	int i;
	for( i=0; i<numTrueFA; ++i){
		fprintf(fout, "%d/%d\n",trueFracAr[i].nume,trueFracAr[i].deno);
	}
	return 0;
}

int shutdown()
{
	fclose(fin);
	fclose(fout);
	return 0;
}
//---local end-----------------------------------//

//---tool functions------------------------------//
int genRelaPriList(int digit)
{
	//检索与digit互质且小于digit的数
	int i, j;
	int gene;
	for( i=1; i<digit;++i)
		relaPriAr[i] = 1;		//reset互质数表
	for( i=0; i<NumPrime; ++i){
		if( primes[i] == digit)
			return 0;
	}		//digit是一个质数，则所有数均为互质数

	for( i=0; i<NumPrime; ++i){
		if( digit%primes[i] ==0){
			//primes[i]是digit的一个因子
			//在互质表中去除所有primes[i]的倍数
			gene = primes[i];
			for( j = gene; j < digit; j +=gene){
				relaPriAr[j] =0;
			}
		}
	}
	return 0;
}

int quickSort(int left, int right)		//对真分数表快速排序
{
	int handle = left;
	int pFront = left+1;
	int pEnd = right-1;
	if( left >= right ) return 0;		//区间长度为1
	if( right - left ==1 ){				//区间长度为2
		if( compFrac(left,right) > 0){
			swapFrac(left,right);
		}
		return 0;
	}
	if( right - left == 2){				//区间长度为3
		directSort(left);
		return 0;
	}
	//用两个指针分别从始末两端向中间搜索，直到两指针接触
	if( compFrac( handle, right) > 0 ){
		swapFrac( handle, right);
	}
	while( pFront< pEnd){
		while( compFrac( pFront, handle) < 0 && pFront <= right)
			++pFront;
		while( compFrac( pEnd, handle) > 0 && pEnd >= left+1 )
			--pEnd;
		if( pFront < pEnd ){
			swapFrac( pFront, pEnd);
			++pFront,--pEnd;
		}
	}

	if( pFront == pEnd){
		if( compFrac(handle, pFront) > 0){
			swapFrac( handle, pFront);
			handle = pFront;
		}
		else if( compFrac(handle, pFront) < 0
				&& pFront-1 != handle){
			swapFrac( handle, pFront-1);
			handle = pFront-1;
		}
	}

	if( pFront > pEnd){
		swapFrac( handle, pEnd);
		handle = pEnd;
	}
	quickSort(left, handle-1);
	quickSort( handle+1,right);
}

int directSort(int left)		//个数为3个时，直接排序
{
	if( compFrac(left, left+1) >0 ){
		swapFrac(left, left+1);
	}
	if( compFrac(left, left+2) >0 ){
		swapFrac(left, left+2);
	}
	if( compFrac(left+1, left+2) >0 ){
		swapFrac(left+1, left+2);		
	}
	return 0;
}

int compFrac(int m, int n)		//比较真分数表中下标为m，n的两个元素 0:相等,1: p>q,-1:p<q
{
	int p,q;
	if( trueFracAr[m].deno == trueFracAr[n].deno ){
		return (trueFracAr[m].nume - trueFracAr[n].nume);
	}
	else{
		p = trueFracAr[m].nume * trueFracAr[n].deno;
		q = trueFracAr[n].nume * trueFracAr[m].deno;
		return p-q;
	}
}

int swapFrac(int m, int n)		//交换真分数表中下标为m，n的两个元素
{
	int temp;
	if( trueFracAr[m].nume != trueFracAr[n].nume ){
		temp = trueFracAr[m].nume;
		trueFracAr[m].nume = trueFracAr[n].nume;
		trueFracAr[n].nume = temp;
	}
	if( trueFracAr[m].deno != trueFracAr[n].deno ){
		temp = trueFracAr[m].deno;
		trueFracAr[m].deno = trueFracAr[n].deno;
		trueFracAr[n].deno = temp;
	}
	return 0;
}
//---tool functions end---------------------------------------//
