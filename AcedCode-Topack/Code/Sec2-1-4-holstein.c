/*
ID: pallas21
LANG: C
TASK:holstein
*/

/*2-1-4-holstein.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2009- 12- 12 
 */

/* 算法提要
 * 数据表示
 * 每种饲料作为元素，则选取方案即为元素的二值集合，类似于背包问题。每种饲料分别使用一个bit纪录，则可使用一个UInt表示一个方案，不同方案可编码识别。
 编码方式为，若某方案为{a1,a2,..an}这几种饲料，则方案编码为 PlanSeq = 2^a1 + 2^a2 +...+2^an，(为计算方便，PlanSeq的最低位即0位保留不使用)。
 则所有可能方案共2^NumG个,PlanSeq最大值为2^(NumG+1)-1。由本题数据量，PlanSeq可使用一个16位非负整数存储。

 * BFS搜索：
 * 将方案作为节点，向任一方案中增加一个元素（即增加一种饲料）所得方案为其后继节点，方案中删除一元素所得为其前趋节点。
 * 则所有方案构成有向图。空集为该图的起始节点，全集（选取所有元素）为该图终点。
 * BFS，全图节点按元素数量从小到大依次分层搜索，同层节点按元素大小依增序排列，则最先搜索到的节点必为所求解。

 * 使用紧凑型队列保存BFS时的待处理节点
 */

#include <stdio.h>
#include <malloc.h>

//class definition
struct Node
{
    unsigned m_data;
    struct Node* next;
};

struct ZipQueue
{
    struct Node* head;
    struct Node* tail;
    struct Node* start;
    struct Node* end;
};

// global constant
#define MAXV 25
#define MAXG 15
//#define MAXCOLOR 2048

// global variable
FILE *fin;
FILE *fout;
int NumV = 0;
int NumG = 0;
int TargetV[MAXV+1] ={0};		         //维他命需求
int TableGV[MAXG+1][MAXV+1] ={0};	     //饲料含量表
struct ZipQueue bfsQue;                  //BFS所使用
unsigned finalAns = 0;;                 //最终答案

// process functions
int init();
int calculate();
int printAns();
int shutdown();

// tool functions
int checkPlan(unsigned x);
int genNextBFLevel(unsigned x);
int AddToQue(unsigned x);
int IsEmptyQue();
unsigned popQue();
int clearQue();

// string functions
int strlen(char* str);
int strcat(char *dest,char *src);

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
    fin  = fopen ("holstein.in", "r");
    fout = fopen ("holstein.out", "w");
    bfsQue.head = bfsQue.tail = bfsQue.start = bfsQue.end = NULL;
    return 0;
}

int calculate()
{
    int i;
    int j;
    unsigned ansX;

    //readData
    fscanf(fin, "%d", &NumV);
    for(i=1; i<=NumV;++i){
        fscanf(fin, "%d", &TargetV[i]);
    }
    fscanf(fin, "%d", &NumG);
    for( i=1; i<= NumG; ++i){
        for( j=1; j<=NumV; ++j){
            fscanf(fin, "%d", &TableGV[i][j]);
        }
    }

    //Gen The 1st Level Nodes
    for( i=1; i<=NumG; ++i){
        AddToQue(0x01 << i);
    }

    //BFS
    while(!IsEmptyQue() ){
       ansX  = popQue();
       if( checkPlan(ansX) ){
           finalAns = ansX;
           break;
       }
       genNextBFLevel(ansX);
    }

    return 0;
}

int printAns()
{
    int i;
    int sum = 0;
    char strTemp[4] = "";
    char strLong[40] = ""; //40 = 9*2+6*3+*+1
    char strFinal[40] = "";
    for( i=1; i<=NumG; ++i){
        if(((0x01 <<i) & finalAns)!=0){
            ++sum;
            sprintf(strTemp,"%d ",i);
            strcat(strLong, strTemp);
        }
    } 
    sprintf(strTemp, "%d ",sum);
    strcat(strFinal, strTemp);
    strcat(strFinal, strLong);
    strFinal[ strlen(strFinal)-1 ] = '\0';
    fprintf(fout,"%s\n",strFinal);

    return 0;
}

int shutdown()
{
    clearQue();
    fclose(fin);
    fclose(fout);
    return 0;
}
//--- process functions end-----------------------//

//--- tool functions -----------------------------//
int checkPlan(unsigned x)
{
    int i = 0;
    int j = 0;
    int checked = 1;
    int boolG[MAXG+1] = {0};
    int curV[MAXV+1] = {0};

    for( i=1; i<=NumG; ++i){
        if( ( (0x01 <<i) & x ) !=0){
            boolG[i] = 1;
            for( j=1; j<=NumV; ++j){
                curV[j] += TableGV[i][j];
            }
        }
    }
    for( j=1; (j<=NumV) && checked; ++j){
        if( curV[j] <TargetV[j] ){
            checked = 0;
        }
    }

    return checked;
}

int genNextBFLevel(unsigned x)
{
    int i;
    for( i=NumG; i>=0; --i){
        if(((0x01 <<i) & x)!=0){
            break;
        }
    }
    for( i=i+1; i<=NumG;++i){
        AddToQue( (0x01<<i) | x);
    }

    return 0;
}

int AddToQue(unsigned x)
{
    struct Node* swapP;
    if(bfsQue.start == NULL){   //队列储备区域为空   
        swapP = (struct Node*)malloc(sizeof(struct Node) );
    }
    else{  //队列储备区域非空 
        swapP =bfsQue.start;
        if(bfsQue.start == bfsQue.end){    //队列储备区域仅一个元素  
            bfsQue.start = bfsQue.end = NULL;
        }
        else{    //队列储备区域有多个元素
            bfsQue.start = bfsQue.start->next;
        }
    }
    swapP->m_data = x;
    swapP->next = NULL;

    if(bfsQue.head ==NULL){
        bfsQue.head = bfsQue.tail = swapP;
    }
    else{
        bfsQue.tail->next = swapP;
        bfsQue.tail = swapP;
    }
    return 0;
}

int IsEmptyQue()
{
    return (bfsQue.head == NULL? 1:0);
}

unsigned popQue()
{
	struct Node* swapP;
	swapP = bfsQue.head;
	if( bfsQue.head ->next == NULL){
		bfsQue.head = bfsQue.tail = NULL;
	}
	else{
		bfsQue.head = bfsQue.head->next;
	}
	swapP->next = NULL;

	if(bfsQue.start == NULL){
		bfsQue.start = bfsQue.end = swapP;
	}
	else{
		bfsQue.end->next = swapP;
		bfsQue.end = swapP;
	}
	return swapP->m_data;
}

int clearQue()
{
	struct Node* tempP, *tempQ;

	tempP = tempQ = bfsQue.head;
	while( tempP!=NULL)
	{
		tempQ = tempP;
		tempP= tempP->next;
		free(tempQ);
	}

	tempP = tempQ = bfsQue.start;
	while( tempP!=NULL)
	{
		tempQ = tempP;
		tempP= tempP->next;
		free(tempQ);
	}
    return 0;
}
//---tool functions end---------------------------//

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

