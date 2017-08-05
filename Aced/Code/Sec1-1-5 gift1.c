/*
ID: pallas21
LANG: C
TASK:gift1
*/

/*1-1-1-gift1.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2007- 06- 05 
 */


#include <stdio.h>

#define maxNP  15
#define maxNameLen  20

char liName[maxNP][maxNameLen];
struct people
{
	int payout;
	int income;
	int moneyTotal;
	int numFri;
	int liFri[maxNP];
};
struct people group[maxNP];
int numPer;

int strlen(char* str);
int strncpy(char* tar, char *sou,int length);
int strcat(char *dest,char *src);
int strcomp(char * str1, char *str2);

void setLiFriZero( struct people *curPer);
int findID(char* name);

int getData();
int Test();
int cal();
int saveData();

//////////////////
//main function
/////////////////
int main () 
{
	getData();
//	Test();
	cal();
//	Test();
	saveData();
	return 0;
}
/////////////////
//main function ends
/////////////////

int getData()
{
	FILE *fin  = fopen ("gift1.in", "r");
	int i,j,k;
	char curName[maxNameLen];
	int curID;
	int curPay;
	int curNumFri;
	char curFriName[maxNameLen];
	int curFriID;

	fscanf(fin, "%d", &numPer);
	fgetc(fin);
	for( i = 0; i < numPer; i++)
	{
		fgets(liName[i], maxNameLen, fin);
	}

	for( i = 0; i <  numPer; i++)
	{
		fgets(curName, maxNameLen, fin);
		fscanf(fin, "%d", &curPay);
		fscanf(fin, "%d", &curNumFri);
		fgetc(fin);
		curID = findID(curName);
		group[curID].payout = curPay;
		group[curID].income = 0;
		group[curID].numFri = curNumFri;
		setLiFriZero(&group[curID]);

		for( j =0; j < curNumFri; j++ )
		{
			fgets(curFriName, maxNameLen, fin);
			curFriID = findID(curFriName);
			group[curID].liFri[curFriID] = 1;
		}
	}
	fclose(fin);
}

int Test()
{
	int i, j;
	for( i=0; i<numPer; i++)
	{
		printf("%s",liName[i]);
	}
	printf("\n");

	for( i=0; i< numPer; i++)
	{
		printf("%s   %4d %4d %4d %4d\n", liName[i],
				group[i].payout, group[i].income, group[i].moneyTotal , group[i].numFri);
		for( j=0; j<numPer; j++)
			printf("%d",group[i].liFri[j]);
		printf("\n\n");
	}
	return 0;
}

int cal()
{
	int i,j;
	int payPerPer =0;
	int rest=0;
	for( i=0; i< numPer; i++)
	{
		if ( group[i].numFri != 0 )
		{
			payPerPer = (group[i].payout) / (group[i].numFri);
			rest = group[i].payout % group[i].numFri;
		}
		else 
		{
			payPerPer = 0;
			rest = group[i].payout;
		}

		for( j=0; j < numPer; j++)
		{
			if( group[i].liFri[j] )
				group[j].income +=payPerPer;
		}
		group[i].income += rest;
	}
	for( i=0; i< numPer; i++)
	{
		group[i].moneyTotal = group[i].income - group[i].payout;
	}	
	return 0;
}

int saveData()
{
	FILE *fout = fopen ("gift1.out", "w");
	int i;
	char result[ maxNameLen + 10 ];
	char ItoA[10];
	for( i=0; i<numPer; i++)
	{
		sprintf(ItoA," %d\n", group[i].moneyTotal);
		strncpy(result, liName[i], maxNP);
		strcat(result, ItoA);
		fprintf(fout,"%s", result);
	}
	fclose(fout);
	return 0;
}

//////////////
//string functions
int strlen(char* str)
{
	char *pos = str;
	while( *pos != '\0' )		pos++;
	return pos - str ;
}


int strncpy(char* tar, char *sou,int length)
{
	int len = strlen(sou);
	len = (len<length)?len:length;
	int i = 0;
	for (i =0; i <len;i++)
	{
		tar[i] = sou[i];
	}
	tar[i]='\0';
	return 0;
}

int strcat(char *dest,char *src)
{
	int lenSrc = strlen(src);
	int lenDest = strlen(dest);
	int i ;
	for (i = 0 ; i < lenSrc; i++)
		dest[ i+lenDest - 1 ] = src[i];

	dest[i+lenDest-1 ] = '\0';
	return 0;
}



int strcomp(char * str1, char *str2)
{
	if (strlen(str1) != strlen(str2))
		return -1;
	while( *str1 == *str2)
	{
		if( *str1 != '\0' )
			str1++,str2++;
		else return 0;
	}
	return 1;
}

void setLiFriZero( struct people *curPer)
{
	int i ;
	for(i = 0; i < maxNP; i++)
		curPer->liFri[i] = 0;
	return;
}

int findID(char* name)
{
	int i;
	for( i =0; i < maxNP; i++)
		if ( !strcomp(liName[i], name) )
			return i;
	return -1;
}
