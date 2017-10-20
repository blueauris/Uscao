/*
ID: pallas21
LANG: C
TASK:hamming
*/

/*2-1-5-hamming.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2009- 12- 27 
 */

/*算法提要:
 *只要按递增顺序搜索要求的n个数，然后跟前面的数判断距离是否大于d，在找到一组解后它肯定是最小的，输出。
 *数据不大，暴力搜索即可
 *要点1：0必然出现，且为第一个可用编码
 *要点2：B给出了搜索的最大值：2^B-1
 *要点3：计算两个数a,b的距离，只要计算a xor b的数的二进制形式中1的个数。
 *预处理优化：可以把所有二进制中1的个数≥d的数记录下来
 本例中用distTable[i]记录i是否是满足要求的数,distTable[i]=1为满足要求，-1为不满足，0为尚未计算
 */
#define LFILE		//读本地文件
#define LTEST		//测试代码

#ifdef LFILE
#else
#endif

#ifdef LTEST
#else
#endif

#include <stdio.h>
// global constant
#define MAXN 64

// global variable
FILE *fin;
FILE *fout;
int caseN,caseB,caseD;
int numN;               //已找到的编码数
int codeworks[MAXN+1] = {0};    //可用编码表，0为默认编码
int distTable[256] = {0};       //预计算的可用间距表

// process functions
int checkDist(int codeM, int codeN);    //若dist(codeM,codeN)>=D，返回1，否则为0
int printAns();
int shutdown();

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
    int cur,pre;
    int numN;
    int checked;
    int i;
    char strTemp[5] =""; 
    char strAns[64*4] = "";
    fin  = fopen ("hamming.in", "r");
    fout = fopen ("hamming.out", "w");
    fscanf(fin,"%d%d%d",&caseN,&caseB,&caseD);

    for(cur=1, numN=1; cur<=(2<<caseB-1) && (numN<caseN); ++cur){
        for(pre=0, checked=1; pre<numN; ++pre){
            if(!checkDist( cur, codeworks[pre]) ){
                checked = 0;
                break;
            }
        }
        if(checked){
            codeworks[numN] = cur;
            ++numN;
        }

    }

    for(i=0; i<caseN; ++i){
        sprintf(strTemp,"%d",codeworks[i]);
        strcat(strAns,strTemp);
        if( i%10 == 9 )
            strcat(strAns,"\n");
        else
            strcat(strAns," ");

    }
    strAns[strlen(strAns)-1] ='\0';
    fprintf(fout,"%s\n",strAns);

    fclose(fin);
    fclose(fout);
    return 0;
}
//----------------------main function ends--------//

//--- process functions --------------------------//

int checkDist(int codeM, int codeN)
{
    int distMN = codeM ^ codeN;
    int i;
    int count = 0;
    if(distTable[distMN] == 0){
        for(i=0; i<8; ++i){
            if( (distMN & (0x01<<i)) !=0)
                ++count;
        }
        distTable[distMN] = (count>=caseD)? 1 :-1 ;
    }

    return (distTable[distMN] > 0)? 1: 0 ;
}

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
//---string functions end-------------------------//
