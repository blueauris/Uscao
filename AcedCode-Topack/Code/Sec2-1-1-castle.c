/*
ID: pallas21
LANG: C
TASK:castle
*/

/*2-1-1-castle.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2009- 02- 03 
 */

/*
 * 用一个二维数组记录整个平面
 * 记录每格四面的墙和每个所属连通分量
 * 宽度优先搜索计算连通分量数，搜索同时统计每个分量的节点数（即房间面积）
 * 枚举每堵墙，如果墙的两边不是同一个房间且其面积和更大，更新结果
 * 为了结果唯一，按题要求，从左下向右上，一列一列枚举格子，并且先枚举该格上面的墙再枚举右边的
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
// global constant
#define MAXWID 50 

// global variable
FILE *fin;
FILE *fout;
int planM;		//平面宽
int planN;		//平面高
struct Cell		//单格
{
	int wallN;
	int wallS;
	int wallE;
	int wallW;		//四面墙 1:有墙 0:无墙
	int roomID;
};													
struct Cell floorPlan[MAXWID+1][MAXWID+1] = {0};	//城堡平面

struct DynaArray				//动态数组
{
	int* index;
	int num;
};
struct DynaArray roomSqAr;		//各房间面积的动态数组

struct Node
{
	int x;
	int y;
	struct Node* next;
};
struct ComQueue				//紧凑型队列
//分为当前点和备用点两个列表，减少内存申请次数
//删除节点放入备用表，增加节点优先从备用表取点
{
	struct Node* head;		//当前队列头部
	struct Node* tail;		//当前队列尾部
	struct Node* start;		//备用队列头部
	struct Node* end;		//备用队列尾部
};
struct ComQueue bfsQue;		//宽度优先辅助列表

int numRooms = 1;			//房间数
int maxRoomID = 1;			//最大面积房间编号

struct combWall
{
	int combSqu;			//组合面积
	int x;
	int y;
	int dir;				//墙方向 1:北方 2:东方
}	theWall;

// local functions
int init();
int getData();
int floodFill();
int lookWall();
int printAns();
int shutdown();

//tool functions
int AddQueue(int x, int y);		//宽搜节点加入列表
int IsEmptyQue();				//检查宽搜节点表
struct Node* popQue();			//弹出宽搜节点
int search(struct Node*);		//宽搜某点
int addSqArr(int ID,int squ);	//记录房间面积
int compWall(int x, int y, int dir, int squ);
//比较格子(x,y)的墙和已找到的墙 dir为墙壁方向 返回值 0:未替换 1:已替换
int reflashWall(int x, int y, int dir, int squ); //刷新所求解

// test function
int  testScene();

//----------------------main function-----------------------//
int main () 
{
	init();
	getData();
	floodFill();
	lookWall();
//	testScene();
	printAns();
	shutdown();
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int init()
{
	fin  = fopen ("castle.in", "r");
	fout = fopen ("castle.out", "w");
	roomSqAr.num = MAXWID;
	roomSqAr.index = (int*)malloc(sizeof(int) * MAXWID);
	memset(roomSqAr.index, 0, sizeof(int)*roomSqAr.num);
	bfsQue.head = bfsQue.tail = bfsQue.end = NULL;
	theWall.combSqu = 0;
	return 0;
}

int getData()
{
	int i,j;
	int floorTemp;
	fscanf(fin,"%d %d\n", &planM, &planN);
	for( j=1; j<=planN; ++j){
		for( i=1; i<=planM; ++i){
			fscanf(fin, "%d",&floorTemp);
			floorPlan[i][j].wallS = (floorTemp >> 3)%2;
			floorPlan[i][j].wallE = (floorTemp >> 2)%2;
			floorPlan[i][j].wallN = (floorTemp >> 1)%2;
			floorPlan[i][j].wallW = floorTemp %2;
		}
	}
	return 0;	
}

int floodFill()
{
	int i,j;
	int curID = 0;
	int curSqu;
	struct Node* tempNode;

	for( j=1; j<=planN; ++j){
		for( i=1; i<=planM; ++i){
			if( floorPlan[i][j].roomID != 0 )
				continue;
			AddQueue(i,j);
			++curID;
			curSqu = 0;
			while( !IsEmptyQue() ){
				tempNode = popQue();
				if( floorPlan[tempNode->x][tempNode->y].roomID == 0){
					floorPlan[tempNode->x][tempNode->y].roomID = curID;
					++curSqu;
					search(tempNode);
				}
			}
			addSqArr(curID, curSqu);
			if ( curSqu > roomSqAr.index[maxRoomID] )
				maxRoomID = curID;
		}
	}
	numRooms = curID;
	return 0;
}

int lookWall()
{
	int i,j;
	int combSqu =0;
	for( j=planN; j>=1; --j){
		for( i=0; i<=planM; ++i){
			if( j>1 ){			//检查本格北面的墙
				if( (floorPlan[i][j].wallN == 1)
						&&floorPlan[i][j].roomID != floorPlan[i][j-1].roomID){
					combSqu = roomSqAr.index[ (floorPlan[i][j].roomID) ]
						+roomSqAr.index[ (floorPlan[i][j-1].roomID) ];
					if( combSqu > theWall.combSqu){
						reflashWall(i,j, 1, combSqu);
					}
					else if(combSqu == theWall.combSqu){
						compWall( i,j, 1, combSqu);
					}
				}
			}
			if( i<planM){		//检查本格东面的墙
				if( (floorPlan[i][j].wallE == 1)
						&&floorPlan[i][j].roomID != floorPlan[i+1][j].roomID){
					combSqu = roomSqAr.index[ (floorPlan[i][j].roomID) ]
						+roomSqAr.index[ (floorPlan[i+1][j].roomID) ];
					if( combSqu > theWall.combSqu){
						reflashWall(i,j, 2, combSqu);
					}
					else if(combSqu == theWall.combSqu){
						compWall( i, j, 2, combSqu);
					}
				}
			}
		}
	}
	return 0;
}

int printAns()
{
	fprintf(fout, "%d\n%d\n",numRooms, roomSqAr.index[maxRoomID]);
	fprintf(fout, "%d\n%d %d ",theWall.combSqu,theWall.y,theWall.x);
	if( theWall.dir == 1)
		fprintf(fout, "N\n");
	else
		fprintf(fout, "E\n");
	return 0;
}

int shutdown()
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

	fclose(fin);
	fclose(fout);
	return 0;
}
//---local end-----------------------------------//

//---tool functions------------------------------//
int AddQueue(int x, int y)
{
	struct Node* swapP;
	if( bfsQue.start == NULL){
		swapP = (struct Node*)malloc(sizeof(struct Node));
	}
	else{
		swapP = bfsQue.start;
		if( bfsQue.start == bfsQue.end){
			bfsQue.start = bfsQue.end = NULL;
		}
		else{
			bfsQue.start = bfsQue.start->next;
		}
	}

	swapP->x = x;
	swapP->y = y;
	swapP->next = NULL;

	if( bfsQue.head == NULL ){
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
	return ( bfsQue.head == NULL? 1 : 0 );             
}

struct Node* popQue()
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
	return swapP;
}

int search(struct Node* tempNode)
{
	int x,y;
	x = tempNode->x;
	y = tempNode->y;
	if ( !floorPlan[x][y].wallN && !floorPlan[ x ][y-1].roomID)		AddQueue( x,  y-1);
	if ( !floorPlan[x][y].wallE && !floorPlan[x+1][ y ].roomID)		AddQueue( x+1, y );
	if ( !floorPlan[x][y].wallS && !floorPlan[ x ][y+1].roomID)		AddQueue( x,  y+1);
	if ( !floorPlan[x][y].wallW && !floorPlan[x-1][ y ].roomID)		AddQueue(x-1,  y );
	return 0;
}

int addSqArr(int ID, int squ)
{
	int* temp;
	int tempNum = roomSqAr.num;
	if ( tempNum <= ID){
		temp = (int*)malloc( sizeof(int) * (tempNum + MAXWID) );
		memset(temp, 0, sizeof(int)*(tempNum + MAXWID));
		memcpy(temp, roomSqAr.index, tempNum*sizeof(int));
		free(roomSqAr.index);
		roomSqAr.index = temp;
		roomSqAr.num += MAXWID;
	}
	roomSqAr.index[ID] = squ;
	return 0;
}

int compWall(int x, int y, int dir, int squ)
{
	if( dir == theWall.dir ){	//两墙同向
		if( x < theWall.x ){
			reflashWall(x,y,dir,squ);
			return 1;
		}
		else if( x == theWall.x && y >theWall.y ){
			reflashWall(x,y,dir,squ);
			return 1;
		}
	}
	if( dir > theWall.dir){		//新墙向东，旧墙向北
		if( x < theWall.x){
			reflashWall(x,y,dir,squ);
			return 1;
		}
	}
	if (dir < theWall.dir){	//新墙向北，旧墙向东
		if( x<= theWall.x){
			reflashWall(x,y,dir,squ);
			return 1;
		}
	}
	return 0;
}

int reflashWall(int x, int y, int dir, int squ)
{
	theWall.combSqu = squ;
	theWall.x = x;
	theWall.y = y;
	theWall.dir = dir;
	return 0;
}

//---------test function-------------------------//
int  testScene()
{
	int i,j;
	for( j=1; j<=planN; ++j){
		for( i=1; i<=planM; ++i){
			if(floorPlan[i][j].wallN == 1)
				printf("+---+");		
			else
				printf("+   +");
		}
		printf("\n");
		for( i=1; i<=planM; ++i){
			if(floorPlan[i][j].wallW == 1)
				printf("|");		
			else
				printf(" ");
			printf("%3d", floorPlan[i][j].roomID);
			if(floorPlan[i][j].wallE == 1)
				printf("|");		
			else
				printf(" ");

		}
		printf("\n");
	}
	for( i=1; i<=planM; ++i)
		printf("+---+");		
	printf("\n");

	printf("roomSqAr.num =%d\n",roomSqAr.num);
	for( i=1; i <=roomSqAr.num; ++i){
		printf("%d  ",roomSqAr.index[i]);
		if( i%10 == 0 )
			printf("\n");
	}
	return 0;
}
