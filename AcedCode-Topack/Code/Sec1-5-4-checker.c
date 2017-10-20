/*
ID: pallas21
LANG: C
TASK:checker
*/

/*1-0-1-checker.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2009- 01- 23 
 */

/*典型DFS问题，为减少计算量，分为两步
 * 第一步，求出前M(此处为3)个解，此函数不需要遍历所有解，可迅速返回
 * 第二步，求所有解的个数，利用对称性和旋转
 偶数只需求1/2，奇数只需求1/8
 其中偶数对第一行 只搜索前半
 奇数先放置中间行、中间列均只搜索一半 且 列数小于行数
 */
/*45度主对角线上任意点(x,y)，其x+y=M为常数 2<=M<=2N
 *可用M为对角线编号 此类对角线共2N-1条，起始编号为2
 *135度主对角线上任意点(x,y)，其x-y=M为常数，-(N-1)<=M<=(N-1)
 *用 M+N 为其编号 共2N+1条，起始编号为1
 */

#include <stdio.h>
#include <string.h>
// global constant
#define MAXN 13

// global variable
FILE *fin;
FILE *fout;
int caseN;						//输入的N值
int nTotalSol = 0;				//解的总数
int MatSum = 0;					//某个已求解中所有选择的数值总和，是与n相关的常数
int matrix[MAXN+1] = {0};		//以行记录的解，matrix[x]=y 表示 在点(x,y) 布点
int col[MAXN+1] = {0};			//列占用记录，col[y] = 1 表示第y列已占用
int udiag[2*MAXN +1] = {0};		//正对角线占用记录 udiag[p] = 1 表示第p条主对角线占用
int ddiag[2*MAXN +1] = {0};		//反对角线占用记录 ddiag[p] = 1  表示第p条反对角线占用

// local functions
int init();
int reset();
int calTotal();
int printLine();
int shutdown();

int dfSearch(int corX, int range,int priNum);
//深度优先搜索
//corX 搜索第x行；range 该行可搜范围；
//printNum 共需打印的解的个数 0搜索全部但不打印 65536打印全部
int mark(int x, int y);			//标记点(x,y)所在的行列和对角线为已占用
int unmark(int x, int y); 		//释放点(x,y)所在的行列纵横对角线的占用
int sumMatrix();				//当前解状态所有元素的总和
int isValidPos(int x, int y);	//点(x,y)可用性检查 返回1为可用
int printLine();				//输出一行解


//----------------------main function-----------------------//
int main () 
{
	init();
	dfSearch( 1, caseN, 3);
	reset();

	nTotalSol = calTotal();
	fprintf(fout, "%d\n", nTotalSol);
	shutdown();
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int init()
{
	fin  = fopen ("checker.in", "r");
	fout = fopen ("checker.out", "w");
	fscanf(fin,"%d",&caseN);
	MatSum = caseN*(caseN+1)/2;
	return 0;
}

int reset()
{
	memset(matrix, 0, sizeof(int)*MAXN);
	memset(col, 0, sizeof(int)*MAXN);
	memset(udiag, 0, sizeof(int)*(2*MAXN+1));
	memset(ddiag, 0, sizeof(int)*(2*MAXN+1));
	nTotalSol = 0;
	return 0;
}

int dfSearch(int corX, int range, int priNum)
{
	int corY;
	if( corX == caseN){							//到达最末行
		if( matrix[corX] != 0){					//该行已布点
			corY = matrix[corX];
			if( isValidPos(corX,corY)){
				++nTotalSol;
				if( priNum !=0 && nTotalSol<= priNum){
					printLine();
				}
			}
		}
		else{									//该行未布点
			corY = MatSum - sumMatrix();
			if( isValidPos(corX,corY)){
				matrix[corX] = corY;
				++nTotalSol;
				if( priNum !=0 && nTotalSol<= priNum){
					printLine();
				}
				matrix[corX] = 0;
			}
		}
		return 0;
	}

	if( matrix[corX] != 0 )		//该行已安放某个点
	{
		dfSearch( corX+1,caseN, priNum);
		return 0;
	}

	for( corY=1; corY <= range; ++corY){		//遍历该行所有点
		if(isValidPos(corX, corY) ){
			matrix[corX] = corY;
			mark(corX, corY);
			dfSearch( corX+1,caseN, priNum);
			unmark(corX, corY);
			matrix[corX] = 0;
		}		
		if(priNum!=0 && nTotalSol >= priNum)
			break;
	}
	return 0;
}

int mark(int x, int y)
{
	col[y] = 1;
	udiag[x+y] =1;
	ddiag[x-y+caseN] =1;	
	return 0;
}

int unmark(int x, int y)
{
	col[y] = 0;
	udiag[x+y] =0;
	ddiag[x-y+caseN] =0;
	return 0;
}

int sumMatrix()
{
	int i;
	int sum = 0;
	for( i=1; i<=caseN; ++i){
		sum += matrix[i];
	}
	return sum;
}

int isValidPos(int x, int y)
{
	return ( !col[y] && !udiag[x+y] && !ddiag[x-y+caseN]);
}

int calTotal()
{
	int i,j;
	int mid;
	int tempTotal=0;
	if( caseN %2 == 0){					//行数为偶数
		dfSearch( 1, caseN/2, 0);		//第一行搜索半行
		tempTotal = nTotalSol *2;
	}
	else{								//行数为奇数
		mid = caseN/2 + 1;
		dfSearch( 1, caseN/2, 0);		//第一行搜索半行
		tempTotal = nTotalSol *2;
		reset();

		matrix[1] = mid;
		mark(1,mid);
		dfSearch(2, caseN,0);
		tempTotal += nTotalSol;
	}
	return tempTotal;
}

int printLine()
{
	int i;
	int sum = 0;
	for( i=1; i<caseN; ++i){
		fprintf(fout, "%d ", matrix[i]);
	}
	fprintf(fout, "%d\n", matrix[i]);
	return 0;
}

int shutdown()
{
	fclose(fin);
	fclose(fout);
	return 0;
}
//---local end-----------------------------------//

