/*
ID: pallas21
LANG: C
TASK: beads
*/

/*1-1-3-beads.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris  
 *All rights reserved
 *UpdateDate :2007- 06- 04 
 */
#include <stdio.h>
#include <stdlib.h>

#define BEAD_MAX 350
char oriLace[BEAD_MAX +1] ="";
int len;

enum BeadColor
{
	white=0,
	black=1,
	red  =2,
};

struct SBead
{
	enum BeadColor color;	
	int amount;
	struct SBead *prev;
	struct SBead *next;
};

struct SBead *necklace = NULL;
//	struct SBead* newSBead(char color);
int compressNecklace();
int searchMax();
int searchLeft (enum BeadColor, struct SBead*);
int searchRight(enum BeadColor, struct SBead*);
int deleteNecklace();


main ()
{
	FILE *fin  = fopen ("beads.in", "r");
	FILE *fout = fopen ("beads.out", "w");
	int maximum;
	fscanf( fin, "%d%*c", &len);
	fscanf( fin, "%s", oriLace);
	compressNecklace();
	maximum =searchMax();
	fprintf(fout,"%d\n",maximum);

	deleteNecklace();
	fclose(fin);
	fclose(fout);
	return 0;
}

int compressNecklace()
{
	int i=0, j=0 ;
	char c_i, c_j;
	int color =0;
	int count = 0;
	struct SBead *pBead,*curBead;

	i=0; 
	while( i<len )
	{
		c_i = oriLace[i];
		pBead = (struct SBead *)malloc( sizeof(struct SBead));

		switch(c_i)
		{
		case 'w': color = 0;
			break;
		case 'b': color =1;
			break;
		case 'r': color = 2;
			break;
		default: break;
		}
		pBead->color =color;

		for(j=i; j<len; j++)
		{
			c_j = oriLace[j];
			if(c_j != c_i)
				break;
		}
		pBead->amount= j-i;
	
		if( necklace == NULL)
		{
			necklace = curBead =pBead;
			pBead->next = curBead;
			pBead->prev = necklace;
		}
		else
		{
			necklace->prev = curBead->next = pBead;
			pBead->prev = curBead;
			pBead->next = necklace;
			curBead = pBead;
		}
		i = j;
	}
	return 0;
}

int searchMax()
{
	struct SBead *pBead,*curBead;
	int rl,rr,bl,br;	//red_left,red_right,black_lest,black_right
	int max_l,max_r,max = 0;
	if(necklace->next == necklace)
		return necklace->amount;

	pBead = necklace;
	do
	{
		rl = searchLeft(red, pBead);
		bl = searchLeft(black, pBead);
		rr = searchRight(red, pBead);
		br = searchRight(black, pBead);

		max_l =(rl>bl)?rl:bl;
		max_r =(rr>br)?rr:br;
		max= ((max_l+max_r) > max)?(max_l+max_r):max;
		pBead = pBead->next;
	}while( pBead != necklace);
	max = (len>max)?max:len;
	return max;
}

int searchLeft (enum BeadColor souColor, struct SBead* souBead)
{
	int cumulative =0;
	struct SBead *pBead = souBead;
	if( (pBead->color != souColor ) && (pBead->color != white) )
		return 0;
	else
		cumulative = pBead->amount;
	
	pBead = pBead->prev;
	while( (pBead != souBead)
			&&	((pBead->color == souColor)
				||(pBead->color == white)
				)
		 )
	{
		cumulative+= pBead->amount;
		pBead = pBead->prev;
	}
	return cumulative;
}

int searchRight(enum BeadColor souColor, struct SBead* souBead)
{
	int cumulative =0;
	struct SBead *pBead ;
	pBead = souBead = souBead->next;
	if( (pBead->color != souColor ) && (pBead->color != white) )
		return 0;
	else
		cumulative = pBead->amount;
	
	pBead = pBead->next;
	while( (pBead != souBead)
			&&	((pBead->color == souColor)
				||(pBead->color == white)
				)
		 )
	{
		cumulative+= pBead->amount;
		pBead = pBead->next;
	}
	return cumulative;

	return 0;
}

int deleteNecklace()
{
	struct SBead *pBead,*curBead;
	pBead = necklace;
	necklace->prev->next = NULL;
	while( pBead != NULL )
	{
		curBead = pBead;
		pBead = pBead->next;
		free(curBead);
	}
	return 0;
}

