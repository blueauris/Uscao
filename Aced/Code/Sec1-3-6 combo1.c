/*
ID: pallas21
LANG: C
TASK:combo
*/

/*1-3-6-combo.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2017- 04- 20 
 */

/*算法提要:
 *这道题的规模是N<=100，直接枚举所有可能出现的号码组合即可，时间复杂度为O(n^3)。
 *也可以用 与农夫相近的密码总数+与预设密码相近的密码总数-既与农夫密码相近又与预设密码相近的密码总数 来求得最后结果。
 *本程序使用算法二：先求出两组密码各自的组合数，再计算各位上共有的数码所组成的共有组合数。
  求共有数时，需注意1. N<=5时，所有数码均为共有 2.两组密码从两个方向都可能有共同数。 
 */

#include <stdio.h>

//----------------------main function--------------//
int main () 
{
	FILE *fin;                      
	FILE *fout;
	int i;                          
	int j;
	                         
	int N = 0;                      
	int X[3]={0};		//农夫密码       
	int Y[3]={0};		//锁匠密码       
	int low,high;	// 某位上两组密码的值，按大小排序 
	int sub;	//某位上两组密码的数值的距离
	int I[3]={0}; // 各位上同时符合两组密码要求的可用数码的个数 
	int result;  	

	fin  = fopen ("combo.in", "r");
	fout = fopen ("combo.out", "w");
	fscanf(fin,"%d\n",&N);
	for(i=0;i<3;++i){
		fscanf(fin,"%d\n",&X[i]);
	}
	for(i=0;i<3;++i){
		fscanf(fin,"%d\n",&Y[i]);
	}

	
	if(N>5){
		for(i=0;i<3;++i){
			low = (X[i]<Y[i])?X[i]:Y[i];
			high = (X[i]>Y[i])?X[i]:Y[i];
			
			sub = high-low;	// 较高值向较低值的间距 
			if ( (sub>=0)&&(sub<=5) ){
				I[i] += 5-sub;
			} 
			sub = N+low-high;	// 较低值在环绕后向较高值的间距
			if ((sub>=0)&& (sub<=5)){
				I[i] += 5-sub;
			} 
		}
		result = 5*5*5*2 - I[0]*I[1]*I[2];	
	}
	else{
		result = N*N*N;
	}
	
//	printf("%d\n",result);
	fprintf(fout,"%d\n",result);
	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends--------//
