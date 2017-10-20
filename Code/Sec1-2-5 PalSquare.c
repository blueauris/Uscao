/*
ID: pallas21
LANG: C
TASK:palsquare
*/

/*1-2-4-palsquare.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 01- 27 
 */

#include <stdio.h>
// global variable
FILE *fin;
FILE *fout;

int format;
int square;					// 平方值
int souDigit[18] = {0};		// 新进制 基数
int tarDigit[18] = {0};		// 新进制 平方
int souLen = 0;				// 基数长
int tarLen = 0;				// 平方长
char souStr[18] = "";		// 基数打印
char tarStr[18] = "";		// 平方打印

// local functions
int tranFormat(int* digit, int ori, int format);	//转进制
int IsPal(int* digit, int len);						// 检验回文
int digToStr(char* str, int* digit, int len);		//输出辅助

//------------------------------------------------------------//
//---main function
int main () 
{
	int N =1;
	fin  = fopen( "palsquare.in", "r");
	fout = fopen( "palsquare.out", "w");
	fscanf( fin,  "%d", &format);
	for (N = 1; N <= 300; ++N){
		square = N*N ;
		tarLen = tranFormat( tarDigit, square, format);
		if ( IsPal(tarDigit, tarLen) ){
			souLen = tranFormat( souDigit, N, format);
			digToStr( souStr, souDigit, souLen);
			digToStr( tarStr, tarDigit, tarLen);
			fprintf( fout, "%s %s\n", souStr, tarStr);
		}
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
//---main function ends
//------------------------------------------------------------//


//---local functions------------------------------------------//
int tranFormat(int* digit, int ori, int format)
{
	int i = 0;
	while ( ori > 0 ){
		digit[i] = ori % format;
		ori = ori/format;
		++i;
	}
	return i ;
}

int IsPal(int* digit, int len)
{
	int i = 0;
	for ( i = 0; i <= (len/2 -1); ++i){
		if (digit[i] != digit[len-i-1] ){
			return 0;
		}
	}
	
	return 1;
}

int digToStr(char* str, int* digit, int len)
{
	char printMap[21] = {"0123456789ABCDEFGHIJ"};	// 打印对照表
	int i;
	for ( i= len -1; i>=0 ; --i){
		if ( digit[i] <= 9 ){
			str[len - i - 1] = digit[i] + '0';
		}
		else{
			str[len - i - 1] = digit[i] -10 +'A';
		}
	}
	str[len] = '\0';
	return 0;
}
//---local end------------------------------------------------//

