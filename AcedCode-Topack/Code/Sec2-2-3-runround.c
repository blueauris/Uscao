/*
ID: pallas21
LANG: C
TASK:runround
*/

/*2-2-3-runround.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2010- 12- 23 
 */

/*算法提要:
 *从初始数值递增并检验即可。
 *为提高效率可预校验，方法为：
 *  检验是否有0，有0的数位增为1
 *  检验是否有重复数，重复数中的较低位增1
 *  检验各位数之和是否为长度的整倍数
 *从当前数开始，预判并递增，可快速滑动到疑似的循环数
 */


#include <stdio.h>
#define WIDE_N 16
int length = 0;		//数长
int digits[WIDE_N] = {0};	//各位置上的数字

// process functions
long int calculate(long int);
int splitNum(long int);			//数值字符化，统计
int preCheck();		//向前滑动数值，直到所有预校验通过
int checkRound();
int increase();
int scanList(int* );
long int regenNum();
// tool functions


//----------------------main function--------------//
int main () 
{
	long int start_num = 0;
	long int goal_num = 0;

	FILE *fin;
	FILE *fout;

	fin  = fopen ("runround.in", "r");
	fscanf(fin, "%ld", &start_num);
	fclose(fin);
	
	goal_num = calculate(start_num);

	fout = fopen ("runround.out", "w");
	fprintf(fout, "%ld\n", goal_num);
	fclose(fout);
	return 0;
}
//----------------------main function ends--------//


//--- process functions --------------------------//

long int calculate(long int sou)
{
	long int goal=0;
	splitNum(sou);

	increase();
	while(1){
		preCheck();

		if( checkRound() ){
			break;
		}
		else{
			increase();
		}
	}

	goal = regenNum();
	return goal;
}

//--- process functions end-----------------------//

//--- tool functions -----------------------------//
int splitNum(long int target )
{
	int i = 0;
	long int obj = target;
	int tail = 0;
	//初始化
	while(obj){
		tail = obj % 10;
		digits[i] = tail;
		obj /= 10;
		++i;
	}
	length = i;
	return i;
}

int scanList(int* count )
{
	int i = 0;
	int pdigit = 0;
	int is_multi = 0;
	int sum = 0;
	int ll = 0;

	for( i=0; i<WIDE_N; ++i)	{count[i]=0;}

	for( i=0; i<length; ++i){
		pdigit = digits[i];
		sum += pdigit;

		if(pdigit == 0) { return 10;}

		++count[pdigit];
		if( count[pdigit] >1){ is_multi = 11;}

	}
	if (is_multi){return 11;}
	ll = sum % length;
	if( ll ) {return length - ll;}
	else {return 0;}
}

int preCheck()
{
	int i = 0;
	int result = 0;
	int b_format = 0;
	int count[16] = {0};

	while( result = scanList(count) ){
		switch (result){
			case 10:             //有零
				for( i=0; i<length; ++i){
					if( digits[i] == 0 ){digits[i] = 1;}
				}
				break;
			case 11:             //有重复数
				for( i=0; i<length; ++i){
					if( count[digits[i]] >1){
						++digits[i];
						if (digits[i] >=10){ b_format =1;}
						break;
					}
				}
				break;
			default:             //总和有余数 1-9
				digits[0] += result;
				if (digits[0] >=10){b_format =1;}
				break;
		}

		if(b_format){
			for( i=0; i<length; ++i){
				if( digits[i] >=10 ){
					digits[i+1] += digits[i] /10;
					digits[i] %= 10;					
				}
			}
			if (digits[length] != 0){ ++length;};
		}
	}
	return 0;
}

int checkRound()    //返回值1 校验通过
{
    int i = 0;
    int pos = 0;
    int dist = 0;
    int mark[WIDE_N] = {0};

    for(i= pos = length-1; i >= 0; --i){
        mark[pos] += 1;

        if( mark[pos] >1 ){return 0;}
        pos = pos-digits[pos];
		while( pos < 0 ){ pos +=length;}

    }
    if(pos != length-1 ) { return 0;}
    for(i=0; i<length; ++i){
    	if(mark[i] >1 || mark[i] ==0)   {return 0;}
	}
	return 1;
}

int increase()
{
	int i = 0;
	++digits[0];
	
	for( i=0; i<length; ++i){
		if( digits[i] >=10 ){
			digits[i+1] += digits[i] /10;
			digits[i] %= 10;					
		}
	}
	if (digits[length] != 0){ ++length;};
	
	return 1;
}

long int regenNum()
{
	long int result = 0;
	int i = length;
	while( i >= 0){
		result *= 10;
		result += digits[i];
		--i;
	}
	return result;
}

//---tool functions end---------------------------//

