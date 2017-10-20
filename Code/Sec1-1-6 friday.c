/*
ID: pallas21
LANG: C
TASK: friday
*/

/*1-1-2-friday.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2007- 06- 10 
 */

#include <stdio.h>
#define NumMonth 12
#define NumWeek 7

int isLeapYear(int curYear)
{
	if( curYear % 4 != 0)
		return 0;		// normal year
	else if (curYear % 100 !=0)
		return 1;		// normal leap year
	else if( curYear % 400 != 0)
		return 0;		//  1800 1900 2100
	else return 1;		//  1600 2000 
}
main ()
{
	FILE *fin  = fopen ("friday.in", "r");
	FILE *fout = fopen ("friday.out", "w");
	const int month[NumMonth] = {31,31,28,31,30,31,
							30,31,31,30,31,30}; //month 12 To month 11
	const int oriday = 3; //  1899-12-31 is Wednesday
	
	int N=0;
	int today=oriday;
	int week[NumWeek] = {0,0,0,0,0,0,0};

	int i,j,k;
	fscanf(fin,"%d", &N);
	for( i=0; i < N; i++)
	{
//		printf("year %d:  ", i +1900);
		for( j=0; j<NumMonth; j++)
		{
			today += month[j];
			if( (j == 2 ) && isLeapYear( i+1900) )
				today++;
			today =today % NumWeek;
//			printf("%d ",today);
			week[ today ] ++;
		}
//		printf("\n");
	}

	fprintf(fout,"%d %d %d %d %d %d %d\n",
			week[6],week[0], week[1],week[2],week[3],week[4],week[5]);
	fclose(fin);
	fclose(fout);
	return 0;
}

