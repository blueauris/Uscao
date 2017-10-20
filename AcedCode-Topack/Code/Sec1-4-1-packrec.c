/*
ID: pallas21
LANG: C
TASK:packrec
*/

/*1-4-1-packrec.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 10- 15 
 */

#include <stdio.h>
#include <malloc.h>
// global constant
#define N 4

//确定顺序的四个矩形 共有五种放置方式，对应五个包围面积
//枚举每个方块的选择顺序和放置方向（横放还是纵放），分别对五种方式计算面积即可
// global variable
FILE *fin;
FILE *fout;

struct rect
{
	int x;
	int y;
};				//存储时 x>y 默认横放

struct rect sourRect[N];	//original four rectangle
int order[N] ={0};		//4个矩形的排列 0-3表示正常横放，4-7表示旋转纵放

int minSquare;
struct node
{
	int x;
	int y;
	struct node* next;
};						//存贮解的列表

struct node* head = NULL;
struct node* tail = NULL;;

// local functions
int getInput();
int genOrder(int n);		// 生成全部排列中的第n个
int calSquare();
int compareSquare(int S, int H, int W);		//比较面积，放入解集
int cleanNode();							//清除原有解集
int addNode(int X, int Y );					//向解集中增加一个解		
int printResult();

int max(int a, int b, int c, int d)
{
	int m,n,p;
	m = a>b?a:b;
	n = c>d?c:d;
	p = m>n?m:n;
	return p;
}

//----------------------main function-----------------------//
int main () 
{
	int i;
	fin  = fopen ("packrec.in", "r");
	fout = fopen ("packrec.out", "w");

	getInput();
	for(i=0; i< 8*6*4*2; ++i){
		genOrder(i);
		calSquare();
	}
	printResult();
	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int getInput()
{
	int m,n,maxEdge;
	int i;
	for( i=0, maxEdge=0; i<N; i++){
		fscanf(fin,"%d %d%*c",&m,&n);
		if(m >= n)
			sourRect[i].x=m, sourRect[i].y=n;
		else
			sourRect[i].x=n,sourRect[i].y=m;
		maxEdge += sourRect[i].x;
	}

	minSquare = maxEdge *maxEdge;
	return 0;
}

int genOrder(int n)
{	
	int i, j;				//循环变量
	int m;					//选择元素时的计数
	int list[N]={0};		//每次可行的选择,list[i]表示第i次取剩余元素中的第list[i]个
	int mark[N] = {0};		//标记元素被选择的情况
	for( i=0; i<N; ++i){	//偶数为横放状况  奇数为纵放状况
		j = 2*(N-i);
		list[i] = n % j;
		n = n/j;
	}						

	for( i=0; i<N; ++i){
		for(j=0,m=0; j<N; ++j){
			if(mark[j]==0){
				if( m == list[i]/2 ){
					order[i] = j;
					mark[j] = 1;
					break;
				}
				else
					++m;
			}
		}
		if(list[i] %2 ==1)	order[i] = order[i]+4;// <4为横放状况  >=4为纵放状况
	}
	return 0;
}

int calSquare()
{
	int i;
	int h[N+1]={0};		//四个矩形的高
	int w[N+1]={0};		//四个矩形的宽
	int H=0,W=0, S=0;

	for(i=0; i<N; ++i){
		if(order[i] <=3){			//横放状况
			w[i+1] = sourRect[ order[i] ].x;
			h[i+1] = sourRect[ order[i] ].y;
		}
		else{						//纵放状况
			w[i+1] = sourRect[ order[i]-4 ].y;
			h[i+1] = sourRect[ order[i]-4 ].x;
		}
	}

	// 分五种情况 计算并判断

	H=max(h[1],h[2],h[3],h[4]);				
	W=w[1]+w[2]+w[3]+w[4];					
	S= H*W;									// 形状1|2|3|4
	if(S<=minSquare) compareSquare(S, H, W);// w=w1+w2+w3+w4；h=max(h1,h2,h3,h4)

	H=max(h[1],h[2],h[3]+h[4],0);			//         3
	W=w[1]+w[2]+max(w[3],w[4],0,0);			//形状 1|2---
	S= H*W;									//         4
	if(S<=minSquare) compareSquare(S, H, W);// w=w1+w2+max(w3,w4)；h=max(h1,h3+h4,h2)

	H=max(h[1],h[2],h[3],0)+h[4];			//      1|2|3
	W=max(w[1]+w[2]+w[3],w[4],0,0);			// 形状-------
	S= H*W;									//        4
	if(S<=minSquare) compareSquare(S, H, W);// w=max(w1+w2+w3,w4)；h=max(h1,h2,h3)+h4

	H=max(h[1]+h[3],h[2]+h[3],h[4],0);		//      1|2
	W=max(w[1]+w[2],w[3],0,0)+w[4];			// 形状-----|4
	S= H*W;									//       3
	if(S<=minSquare) compareSquare(S, H, W);// w=max(w1+w2,w3)+w4；h=max(h1+h3,h2+h3,h4)

	//      1|2
	// 形状----		3，4底边对齐，按h3 h4的大小细分w为五种情况 
	//      3|4
	// h=max(h1+h3,h2+h4) 
	H=max(h[1]+h[3],h[2]+h[4],0,0);
	if( h[3] >= h[2]+h[4] )		W=max(w[1],w[3]+w[2],w[3]+w[4],0); 						// h3 >= h2+h4；w=max(w1,w3+w2,w3+w4)
	else if( (h[3] < h[2]+h[4]) &&(h[3]>h[4]) ) W= max(w[1]+w[2],w[3]+w[2],w[3]+w[4],0);// h4<h3<h2+h4；w=max(w1+w2,w2+w3,w3+w4)
	else if( h[3]==h[4] ) W= max(w[1]+w[2],w[3]+w[4],0,0);								// h3=h4；w=max(w1+w2,w3+w4)
	else if( h[3]<h[4] && h[4] < h[1]+h[3] ) W=max(w[1]+w[2],w[1]+w[4],w[3]+w[4],0);	// h3<h4<h1+h3；w=max(w1+w2,w1+w4,w3+w4)
	else if( h[4] >= h[1]+h[3] ) W=max(w[2],w[1]+w[4],w[3]+w[4],0); 					// h4 >= h1+h3；w=max(w2,w1+w4,w3+w4)
	S= H*W;
	if(S<=minSquare) compareSquare(S, H, W);

	return 0;
}


int compareSquare(int S, int H, int W)
{
	int P,Q;
	P = (H<=W)? H: W;
	Q = (H<=W)? W: H;
	if( S <minSquare){
		cleanNode();
		minSquare = S;
	}
	addNode(P, Q);
	return 0;
}

int cleanNode()
{
	
	struct node *p,*q;
	p= head;
	while(p!=NULL){
		q=p;
		p= p->next;
		free(q);
	}
	head = NULL;

	return 0;

}

int addNode(int X, int Y )
{
	struct node *p,*q,*cur;
	p = q =head;

	while(p!=NULL && p->x < X){
		q=p;
		p=p->next;
	}
	if( p!=NULL && p->x == X )	return 0;

	cur = (struct node*)malloc(sizeof(struct node));
	cur->x = X, cur->y = Y;
	cur->next = p;
	if( head == NULL) head = cur;
	if( head == p)  head = cur;
	if( q != p ) q->next = cur;

	return 0;

}

int printResult()
{
	struct node *p, *q;
	p=head;
	fprintf( fout,"%d\n", minSquare);
	while( p!=NULL){
		fprintf( fout,"%d %d\n", p->x,p->y);
		q = p;
		p = p->next;
		free(q);
	}
	return 0;
}

//---local end-----------------------------------//
