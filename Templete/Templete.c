/*
ID: pallas21
LANG: C
TASK:PROGRAM_NAME
*/

/*1-0-1-PROGRAM_NAME.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2009- 01- 05 
 */

/*算法提要:
 *
 *
 */
#define LTEST		//测试代码

#ifdef LTEST
#else
#endif

#include <stdio.h>

// global constant


// global variable


// tool functions

// test function
int  testScene();
int  testRound();

// string functions
int strlen(char* str);
int strncpy(char* tar, char *sou,int length);
int strcat(char *dest,char *src);
int strcomp(char * str1, char *str2);

//----------------------main function--------------//
int main () 
{
	FILE *fin;
	FILE *fout;
	int N;
	
	fin  = fopen ("PROGRAM_NAME.in", "r");
	fout = fopen ("PROGRAM_NAME.out", "w");
	
	//ToDo:
	//getData
	
	//calculate
	
	//printAns

	
	fclose(fin);
	fclose(fout);
	return 0;
}


//--- tool functions -----------------------------//

//---tool functions end---------------------------//

//---------test function--------------------------//
int  testScene()
{
	return 0;
}

int  testRound()
{
	return 0;
}
//---test functions end---------------------------//


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
//---string functions end-------------------------//
