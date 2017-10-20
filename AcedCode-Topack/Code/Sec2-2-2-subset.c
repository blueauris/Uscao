/*
ID: pallas21
LANG: C
TASK:subset
*/

/*2-2-2-subset.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2010- 04- 27 
 */

/*算法提要:
 *记输入值为m，所求值为SSub，记Sum(m)为从1到m的总和。
  可知：当m=4n+1或4n+2时，Sum为奇数，无法按题意分割，SSub=0
        当m=4n  或4n+3时，可进一步计算
 *
 *从集合｛x|x<=n｝中任取若干数，使其总和为S，记这样的取法总数为f(n,S)
  则 SSub = f(m,Sum(m)/2 )/2
 *分析 f 的性质有：
    对称性 f(n, S) = f(n, Sum(n) - S )
	递推性 f(n, S) = f(n-1, S) + f(n-1, S-n)   当 S >= n
	               = f(n-1, S)                 当 S < n
 * 初值: 对任意n，f(n, 0) = 1，f(n, 1) = 1, f(n, Sum) = 1，f(n, S) = 0 (当S>sum)
 * 由以上性质，可推导计算n=1..m的所有 f 值，输出  f(m,Sum(m)/2 )/2 即可。
 *
 * 对f(n,S)，当n指定为值p时，函数值集合{y|y=f(p, S),0<=S<=Sum(p)} 为一维数组，记为F(p)
 * 计算时，准备两个数组。其一记录f(p-1),另一以此为基准计算 F(p)。随后两数组交换位置计算F(p+1),以此类推。
 * 因 m = 2 无解，从m=3开始计算。初始化数组为F(2) = {1,1,1,1}
 */

#include <stdio.h>
// global constant
#define MAXN 39
#define MAXSUM 781

// global variable
FILE *fin;
FILE *fout;
int caseN = 0;
long long num_sub_set=0;
long long array1[MAXSUM] = {0};
long long array2[MAXSUM] = {1,1,1,1};
long long *p_pre = array1;
long long *p_cur = array2;
long long *p_swap = NULL;

int calculate();

//----------------------main function--------------//
int main () 
{
	fin  = fopen ("subset.in", "r");
	fout = fopen ("subset.out", "w");
	fscanf(fin,"%d",&caseN);

	calculate();

	fprintf(fout,"%lld\n",num_sub_set);
	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends--------//


//--- process functions --------------------------//

int calculate()
{
	int sum = 0;
	int i,j;
	if ( caseN%4 ==1 || caseN%4 == 2){
		num_sub_set = 0;
		return 0;
	}

	for(i=3; i<=caseN; ++i){
		sum = i*(i+1)/2;
		p_swap = p_pre;
		p_pre = p_cur;
		p_cur = p_swap;

		for( j=0; j<= sum/2; ++j){
			if( j-i >=0){
				p_cur[j] = p_pre[j] + p_pre[j-i];
			}
			else{
				p_cur[j] = p_pre[j];
			}
		}
		for( j=sum/2+1; j<=sum; ++j){
			p_cur[j] = p_cur[sum-j];
		}
	}
	num_sub_set =  p_cur[sum/2]/2;
	return 0;
}

