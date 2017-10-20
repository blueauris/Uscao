/*
ID: pallas21
LANG: C
TASK:milk3
*/

/*1-4-4-milk3.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 11- 07 
 */

/*状态空间转移问题
 *每次最多有6条转移路径，DFS所有状态并记录，遇到已有状态返回
 *最后输出所有A桶为空的状态即可
 */
#include <stdio.h>
// global constant
#define maxCap 20
#define numBot 3
#define numTrans (numBot*(numBot-1))

// global variable
FILE *fin;
FILE *fout;

int bStatesTable[maxCap+1][maxCap+1]={0};		//状态记录，states[i][j]=1表示 a=i b=i的状态存在
int trans[numTrans][2] = 				//状态转移表
{
	0,1,		// A->B
	0,2,		// A->C
	1,2,		// B->C
	1,0,		// B->A
	2,0,		// C->A
	2,1			// C->B
};
struct State
{
	int bot[numBot];
};							//当前各桶的状态

int Cap[numBot]={0};		//三个桶最大容量
int maxVol=0;
struct State oriS = {0};	//初始状态

// local functions
int getInput();
int printAns();
int search(struct State curS);
struct State pour(struct State curS, int souBot, int tarBot);

int strlen(char* str);
int strcat(char* tar, char* sou);
//----------------------main function-----------------------//
int main () 
{
	getInput();
	search(oriS);



	printAns();
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int getInput()
{
	fin  = fopen ("milk3.in", "r");
	fscanf(fin, "%d %d %d\n", &Cap[0], &Cap[1], &Cap[2]);
	bStatesTable[0][0] = 1;
	maxVol = Cap[2];

	oriS.bot[0] = 0;
	oriS.bot[1] = 0;
	oriS.bot[2] = Cap[2];

	fclose(fin);
	return 0;
}

int printAns()
{
	int i;
	char str[maxCap*3] = "";
	char strB[maxCap] = "";
	fout = fopen ("milk3.out", "w");

	for( i=maxCap; i>=0; --i){
		if( bStatesTable[0][i] != 0 ){
			sprintf(strB, "%d ", maxVol-i );
			strcat(str,strB);
		}
	}
	str[ strlen(str) -1 ] = '\0';

	fprintf(fout, "%s\n",str);
	fclose(fout);
	return 0;
}

int search(struct State curS)
{
	int i;
	int souBot=0,tarBot=0;
	struct State nextS;

	for(i=0; i<numTrans; ++i){
		souBot = trans[i][0];
		tarBot = trans[i][1];
		if( curS.bot[souBot] <= 0
				|| curS.bot[tarBot] >= Cap[tarBot] )			// 判断操作可行性	
			continue;
		nextS = pour( curS, souBot, tarBot);
		if(  bStatesTable[ nextS.bot[0] ][nextS.bot[1]] )	// 检查状态是否存在
			continue;
		bStatesTable[ nextS.bot[0] ][nextS.bot[1]] = 1;		// 标记该状态

		search(nextS);
	}
	return 0;
}

struct State pour(struct State curSS, int souBot, int tarBot)
{
	int volSou, volTar,volMin;
	volSou = curSS.bot[souBot];
	volTar = Cap[tarBot] - curSS.bot[tarBot];
	volMin = (volSou <= volTar) ? volSou : volTar;
	curSS.bot[souBot] -= volMin;
	curSS.bot[tarBot] += volMin;

	return curSS;
}

//---local end-----------------------------------//
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

