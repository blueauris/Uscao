/*
ID: pallas21
LANG: C
TASK:clocks
*/

/*1-4-2-clocks.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 10- 19 
 */
// 问题模型化为 A+M*T=R  
// 其中A={a1,..a9} R={4n1，..,4n9}  T为转换矩阵 TT为T的逆矩阵
// 求系数矩阵M={m1,..m9}
// 因n1..n9不确定，用M=(R-A)*TT 同样需要多次试算，且判断条件为M是否为整数，不直观
#include <stdio.h>

// global constant
#define N 10		//9个元素 + 首位留空

// global variable
FILE *fin;
FILE *fout;

int a[N] = {0};		//原始列
int r[N] = {0};		//目标列
int c[N] = {0};		//计算中间值 用于比较的数列
int m[N] = {0};		//所求系数矩阵  满足 (c=m * T) ==r时 即求得解
int M[N] = {0};	    //保存最终结果，M[0]为项数

int T[N][N] ={		//转换矩阵
	{0},						//空行
//     A B C D E F G H I
	{0,1,1,0,1,1,0,0,0,0},		//1  ABDE
	{0,1,1,1,0,0,0,0,0,0},		//2  ABC
	{0,0,1,1,0,1,1,0,0,0},		//3  BCEF
	{0,1,0,0,1,0,0,1,0,0},		//4  ADG
	{0,0,1,0,1,1,1,0,1,0},		//5  BDEFH
	{0,0,0,1,0,0,1,0,0,1},		//6  CFI 
	{0,0,0,0,1,1,0,1,1,0},		//7  DEGH
	{0,0,0,0,0,0,0,1,1,1},		//8  GHI
	{0,0,0,0,0,1,1,0,1,1}		//9  EFHI
};

// local functions
int getInput();
int searchDeep(int pos);
int checkSolution();
int saveSolution();
int printAnswer();

//----------------------main function-----------------------//
int main () 
{
	int i=1;
	fin  = fopen ("clocks.in", "r");
	fout = fopen ("clocks.out", "w");

	getInput();
	searchDeep(i);
	printAnswer();

	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int getInput()
{
	int i;
	for(i=0; i<3; ++i)	{
		fscanf(fin,"%d %d %d%*c\n", &a[i*3+1],&a[i*3+2],&a[i*3+3]);
	}
	for(i=1; i<N; ++i){
		r[i] = (4-a[i]/3)%4;
	}
	return 0;
}

int searchDeep(int depth)		//深度优先搜索
{
	int i;
	for(i=0; i<=3; ++i){
		m[depth] = i;
		if( depth == 9 ){
			if( checkSolution() ){
			saveSolution();
			return 1;
			}
		}
		else if(depth <9){
			searchDeep(depth+1);
		}
	}
	return 0;
}

int checkSolution()		//计算矩阵并校验结果
{
	int temp[N] = {0};
	int i,j;
	for( i=1; i<N; ++i){
		for(j=1; j<N; ++j){
			temp[i] +=m[j]*T[j][i];
			}
		if ( temp[i]%4 != r[i]){
			return 0;
		}
	}
	return 1;
}

int saveSolution()
{
	int sum=0;
	int i;
	for(i=1; i<N; ++i){
			sum += m[i];
	}
	if ( M[0] == 0 || M[0] >sum ){
		M[0] = sum;
		for(i=1; i<N; ++i){
			M[i] = m[i];
		}
	}
	return 1;
}

int printAnswer()
{
	int i,j;
	char str[N*3*2] ="\0";
	char* p = str;
	for(i=1; i<N; ++i){
		for(j=0; j<M[i]; ++j){
			*p = i+'0';
			++p;
			*p = ' ';
			++p;
	
		}
	}
	*(--p) = '\n';
	*(++p) = '\0';

	 fprintf(fout,"%s",str);
	 return 0;
}	

			
//---local end-----------------------------------//
