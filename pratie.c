#include<stdio.h>
#include<stdlib.h>

int main() 
{
int count[256] = { 0 }; 

  int k,c;

  FILE *fp;
  fp = fopen("filehandling.txt", "r");
  
  if(fp == NULL)
  {
  	printf("coudn't able to open the file \n");
  }
  else
  {
  while((c=fgetc(fp)))
  	 {
	   if(c == EOF) break;
	   count[c]+=1;                  // adding  1 to the particular character
	   }
  }

  /* now printing the results  */
  
  for(k=0; k<256; k++) {
    if(count[k] > 0) {
       printf("%c: %d times\t", k, count[k]);
    }
  }
  
  fclose(fp);                      //closing the file


}
