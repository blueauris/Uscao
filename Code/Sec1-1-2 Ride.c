/*  
 *TASK:ride  
 *UpdateDate :2007- 06- 05   
 */  
#include <stdio.h>   
int strlen(char* str)   
{   
 char *pos = str;   
 while( *pos != '\0' )  pos++;   
 return pos - str;   
}   
int strcpy(char* tar, char *sou)   
{   
 int len = strlen(sou);   
 int i = 0;   
 for (i =0; i <len;i++)   
 {   
  tar[i] = sou[i];   
 }   
 tar[i]='\0';   
 return 0;   
}   
int calHash(char* str)   
{   
 int length = strlen(str);   
 int hash =1;   
 int i =0;   
 for(i =0; i<length; i++)   
 {   
  hash = hash * ( str[i] -'A' + 1);   
 }   
 hash = hash % 47;   
 return hash;   
}   
  
int main ()    
{   
 FILE *fin  = fopen ("ride.in", "r");   
 FILE *fout = fopen ("ride.out", "w");   
 const int length =20;   
 char nameGroup[length];   
 char nameComet[length];   
 char result[10];   
 int hashGroup=1;   
 int hashComet=1;   
 fscanf(fin, "%s",nameGroup);   
 fscanf(fin, "%s",nameComet);   
 hashGroup =calHash( nameGroup);   
 hashComet = calHash( nameComet);   
 if ( hashGroup == hashComet)    
 {   
  strcpy(result ,"GO");   
 }   
 else  
 {   
  strcpy(result ,"STAY");   
 }   
 fprintf (fout, "%s\n", result);   
 fclose(fin);   
 fclose(fout);   
 return 0;   
}  
