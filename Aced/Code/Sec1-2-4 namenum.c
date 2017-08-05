/*
ID: pallas21
LANG: C
TASK:namenum
*/

/*1-2-3-namenum.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2008- 01- 16 
 */

#include <stdio.h>
// global constant
#define CODELEN 12
const char table[][4]=
{
	"ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"
};

// global variable
FILE *fin;
FILE *fout;
FILE *fdict;

char strIn[CODELEN] ="\n";
int code[CODELEN] = {0};
int N = 0;
int total = 0;

// local functions
int char2code(char c);
int fit(char* str, int* code);

// string functions
int strlen(char* str);

//------------------------------------------------------------//
//---main function
int main () 
{
	fin  = fopen ("namenum.in", "r");
	fout = fopen ("namenum.out", "w");
	fdict = fopen ("dict.txt", "r");
	
	fscanf(fin, "%s%*c", strIn);
	N = strlen(strIn);
	
	for (int i=0; i < N; ++i){
		code[i] = strIn[i]-'0';
	}

	while ( fscanf(fdict, "%[^\n]%*c", strIn) != EOF ){
		if ( fit(strIn,code)){
			fprintf(fout, "%s\n", strIn);
			++total;
		}
	}
	if ( total ==0 ){
		fprintf(fout, "NONE\n");
	}

	fclose(fin);
	fclose(fout);
	fclose(fdict);

	return 0;
}
//---main function ends
//------------------------------------------------------------//


//---local functions------------------------------------------//
int char2code(char c)
// translate the string to code
// return the length
{
	int code =0;
		if ( c < 'Q' ){
			code = (c -'A') / 3 + 2;
		}
		else {
			code = (c -'A' - 1) / 3 + 2;
		}
	 return code;
}

int fit(char* str, int* code)
{
	int boolean = 1;
	int i = 0;
	while( str[i] !='\0' && boolean)
	{
		if ( (char2code(str[i]) != code[i])
			|| i >=N ){
			boolean =0;
		}
		++i;	
	}
	if ( i < N ) boolean = 0;
	return boolean;
}

//---local end------------------------------------------------//


//---tool functions-------------------------------------------//
int strlen(char* str)
{
	char *pos = str;
	while( *pos != '\0' )
		pos++;
	return pos - str ;
}

