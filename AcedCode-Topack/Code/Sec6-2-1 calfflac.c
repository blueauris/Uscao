/*
ID: pallas21
LANG: C
TASK:calfflac
*/

/*1-3-3-calfflac.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 10- 03 
 */
#include <stdio.h>
// global constant
#define N 20000

// global variable
FILE *fin;
FILE *fout;

char oriString[N]= "";		//原串
char zipString[N] = "";		//规格化串
int oriLength = 0;			//原串长度
int zipLength =  0;			//规格化串长度

struct index
{
	int zip;
	int ori;
};				//规格化串中的某字符在原串中对应位置
struct index HashTable[N];  //字符对应表，仅记录变化量
int tableLength = 0;

struct range
{
	int start;
	int end;
};				//回文所在区域
struct range zipPalin,oriPalin;
int maxLength =0;

// local functions
int hashStr();		//规格化原始串
int searchPalin();		//在目标串中搜索回文
int findChar(int oriPos);		//搜索回文在原串中的位置
int printout();


//----------------------main function-----------------------//
int main () 
{
	fin  = fopen ("calfflac.in", "r");
	fout = fopen ("calfflac.out", "w");
	fread(oriString,sizeof(char), N+1, fin);

	hashStr();
	searchPalin();
	oriPalin.start = findChar( zipPalin.start);
	oriPalin.end = findChar( zipPalin.end);
	printout();
	
	fclose(fin);
	fclose(fout);
	return 0;
}
//----------------------main function ends-----------------//


//---local functions-----------------------------//
int hashStr()
{
	int i = 0;	//pos in oriStr
	int j  =0;  //pos in zipStr
	int k = 0;  //pos in hashTable
	int dirty = 1;	//recode of the change

	char tempCh ;
	while(  (tempCh = oriString[i]) != '\0')
	{
		if(   (tempCh >= 'a' && tempCh <= 'z')
				||(tempCh >= 'A' && tempCh <= 'Z')	)
		{
			if( tempCh >='a')
				zipString[j] = tempCh;
			else 
				zipString[j] = tempCh + 'a'-'A';

			if( dirty ){
				HashTable[k].ori = i;
				HashTable[k].zip = j;
				++k;
				dirty = 0;
			}

			++i,++j;
		}
		else{
			dirty = 1;
			++i;
		}
	}

	oriLength = i;
	zipLength = j;
	tableLength = k;
	zipString[zipLength+1] = '\0';
	HashTable[tableLength].ori = oriLength;
	HashTable[tableLength].zip = zipLength;


	return 0;
}

int searchPalin()
{
	//以当前字符为中心,向两侧搜索回文,分奇数和偶数两种情况
	int cen = 0;		//当前处理的中心字符
	int dist = 0;		//向两侧拓展的距离

	int oddMax = 0;		//奇数情况最大回文半长度  不含中心
	int evenMax = 0;	//偶数情况最大回文半长度  
	int oddPos = 0;		//奇数情况最大回文中心位置  
	int evenPos = 0;	//偶数情况最大回文中心左位置

	//奇数情况 cen为中心位 半长度不含中心
	for( cen = 1;cen <= zipLength-oddMax; ++cen)
	{
		if ( zipString[cen-oddMax] != zipString[cen+oddMax] ) continue;

		for( dist = 1; dist<=cen && dist<=(zipLength-cen); ++dist)
			if( zipString[ cen-dist ] != zipString[ cen+dist ] ) break;

		if ( oddMax < dist-1 )
		{
			oddMax = dist -1;
			oddPos = cen;
		}

	}

	//偶数情况 cen为中心空格左侧字符 半长度含中心
	for( cen = 0;cen <= zipLength-oddMax; ++cen)
	{
		if ( zipString[cen-oddMax+1] != zipString[cen+oddMax] ) continue;

		for( dist = 1; dist<=cen+1 && dist<=(zipLength-cen); ++dist)
			if( zipString[ cen-dist+1 ] != zipString[ cen+dist ] ) break;

		if ( evenMax < dist-1 )
		{
			evenMax = dist-1;
			evenPos = cen;
		}

	}

	if( 2*oddMax+1 > 2* evenMax)
	{
		zipPalin.start= oddPos-oddMax;
		zipPalin.end = oddPos+oddMax;
		maxLength = 2*oddMax+1;

	}
	else
	{
		zipPalin.start= evenPos-evenMax+1;
		zipPalin.end = evenPos+evenMax;
		maxLength = 2* evenMax;
	}

	return 0;
}

int findChar(int oriPos)
{
	int i;
	int tar;
	for(i=0; i<= tableLength; ++i)
		if( oriPos < HashTable[i].zip ) break;

	--i;	//found the range in hashtable;
	tar = oriPos - HashTable[i].zip + HashTable[i].ori;
	return tar;
}

int printout()
{
	int i;
	fprintf(fout,"%d\n",maxLength);
	for( i=oriPalin.start; i <= oriPalin.end; ++i)
	{
		fputc(oriString[i],fout);
	}
	fputc('\n',fout);
	return 0;
}

//---local end-----------------------------------//

