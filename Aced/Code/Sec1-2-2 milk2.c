/*
ID: pallas21
LANG: C
TASK: milk2
*/

/*1-2-1-milk2.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 01- 05 
 */

#include <stdio.h>
#include <string.h>

#define maxN 5000
int N;
int sPoint[maxN];		//开始时间
int ePoint[maxN];			//结束时间
struct STimeNode
{
	int time;
	int prop;
};
struct STimeNode timeLine[2*maxN];
int NLine;
int maxOn, maxOff;

int sort( int * tar);
int connect();
int calCow();
int test();

main ()
{
	int i;

	FILE *fin  = fopen ("milk2.in", "r");
	FILE *fout = fopen ("milk2.out", "w");
	N=0,NLine =0;
	memset(sPoint, 0, sizeof(int) * maxN);
	memset(ePoint, 0, sizeof(int) * maxN);
	memset(timeLine, 0, sizeof(struct STimeNode) * maxN*2);
	maxOn=0, maxOff=0;

	fscanf( fin, "%d%*c",&N);
	NLine = 2*N;
	for(i=0; i<N; ++i)
	{
		fscanf(fin, "%d %d%*c", &sPoint[i], &ePoint[i]);
	}

	sort(sPoint);
	sort(ePoint);
	connect();
	calCow();
//	test();
	fprintf(fout, "%d %d\n", maxOn, maxOff);
	fclose(fin);
	fclose(fout);
	return 0;
}

int sort( int * tar)
{
	int i, j;
	int pos =0;
	int temp;
	for( i=0; i < N; ++i)
	{
		pos = i;
		for( j = i; j < N; ++j)
		{
			if( tar[pos] > tar[j] )
				pos = j;
		}
		temp = tar[i];
		tar[i]= tar[pos];
		tar[pos] = temp;
	}
	return 0;
}

int connect()
{
	int iLine,iStart,iEnd;
	int tempTime;
	iLine = iStart =iEnd=0;
	while(( iStart < N ) && ( iEnd < N ))
	{
		if(sPoint[iStart] < ePoint[iEnd])
		{
			timeLine[iLine].time =sPoint[iStart];
			timeLine[iLine].prop =1;
			++iLine,++iStart;
		}
		else if(sPoint[iStart] > ePoint[iEnd])
		{
			timeLine[iLine].time =ePoint[iEnd];
			timeLine[iLine].prop = -1;
			++iLine,++iEnd;
		}
		else 	// ==
		{
			++iStart, ++iEnd;
			NLine -= 2;
		}
	}
	while( iEnd < N )
	{
		timeLine[iLine].time =ePoint[iEnd];
		timeLine[iLine].prop = -1;
		++iLine,++iEnd;
	}

	return 0;
}

int calCow()
{
	int state = 0;
	int i = 0;
	int start, end;
	int timeOn,timeOff = 0;
	end = 0;
	start = timeLine[0].time;
	for( i=0; i < NLine; ++i)
	{
		state += timeLine[i].prop;
		if( state == 0 )
		{
			end = timeLine[i].time;
			timeOn = end - start;
			if( i < NLine -1 )
			{
				start = timeLine[ i+1 ].time;
				timeOff = start -end;
			}
			maxOn = (maxOn > timeOn) ? maxOn : timeOn;
			maxOff = (maxOff > timeOff) ? maxOff : timeOff;
		}
	}
	return 0;
}

int test()
{
	int i;
	printf("---------------\n");
	for( i=0; i < N; ++i)
	{
		printf(" %d  %d\n", sPoint[i],ePoint[i]);
	}
	printf("---------------\n");

	for( i=0; i <NLine; ++i)
	{
		printf(" %d", timeLine[i].time);
	}
	printf("\n---------------\n");

	return 0;
}

