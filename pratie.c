#include<stdio.h>
#include<stdlib.h>

int main(){
  int count[256]={0};
  int k,c;
  FILE *fp;

  fp=fopen("compress.txt","r");

  /* if file pointer is null, means file doesnot exists */
  if(fp==NULL){
    printf("file doesnot exists");
  }

  /* do this until we get the character */
  else{
    while(c=fgetc(fp)){

      /* stop when we get end of the file */
      if(c==EOF){
        break;
      }

      /* count the frequency of the character */

      else{
        count[c]+=1;
      }
    }

    /* printing the character and its frequncy */

    for(k=0;k<256;k++){
      if(count[k]>0){
        printf("frequncy of %c: %d\n",k,count[k]);
      }
    }
  }

  fclose(fp);
  return 0;
}
