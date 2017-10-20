/*  
TASK: test 
*UpdateDate :2007- 06- 05   
*/  
  
#include    
main ()    
{   
	FILE *fin = fopen ("test.in", "r");   
	FILE *fout = fopen ("test.out", "w");   
	int a, b;   
	fscanf (fin, "%d %d", &a, &b); /* the two input integers */  
	fprintf (fout, "%d\n", a+b);   
	fclose(fin);   
	fclose(fout);   
	return 0;   
}