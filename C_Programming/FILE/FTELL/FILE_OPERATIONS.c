#include<stdio.h>
int main(){
int i=1,line=0;
  //pgm to copy data from one file to another as caps
    // #include<stdio.h>
    // int main(){
    int i=1,line=0;
    FILE *fp,*fp1;
    char x;
    char c[60]="hello";
 /*    fp=fopen("file.txt","r");
    fp1=fopen("file1.txt","w+");
        fseek(fp,0,SEEK_END);   //move to last of the file
        int z=ftell(fp);        //prints the current position o pointwr
        rewind(fp);             //returns back
    while(i<=z)
    {
      x=fgetc(fp);
      if(islower(x))            //checks the value is upprcase or not
      {
          x=x-32;
      }
      i++;
      fputc(x,fp1);
    }
    fclose(fp1);
    fclose(fp);
}
   */
   
/* finding length of file   */
   
   
    fp=fopen("file.txt","r");
    if(fp==NULL)
    {
        printf("the file cannot be created/found");
        return -1;
    }
if(fgets(*c,40,fp)!=NULL)
{
        printf("%s",c);
 }       rewind(fp);// this function puts the pointer to the starting of the file again.
        system("pause");  // this is a function used to pause the execution at the curent line

    fclose(fp);
    fp=NULL;
    return 0;
       fseek(fp,0,SEEK_END);
       int z=ftell(fp);
       printf("%d\n",z);
       rewind(fp);
       int y=ftell(fp);
       printf("the length is %d",z-y);
       fclose(fp);
}

    //program find total no of lines
//#include<stdio.h>
//int main(){
//    int i=1,line=0;
//    FILE *fp;
//    char x;
//  //  char c[60]="hello";
//    fp=fopen("file.txt","r");
//           fseek(fp,0,SEEK_END);
//           int z=ftell(fp);
//           rewind(fp);
//while(i<=z)
//{
//    x=fgetc(fp);
//    if(x=='\n')
//    {
//      line++;

//     }
//    i++;


//}
//printf("total no of lines is %d",line);
//fclose(fp);
//}

// pgm to repliicate a file by convrting its charters to uppercase into new file
//#include<stdio.h>
//int main(){
//    int i=1,line=0;
//    FILE *fp,*fp1;
//    char x;
//  //  char c[60]="hello";
//    fp=fopen("file.txt","r");
//    fp1=fopen("file1.txt","w+");
//               fseek(fp,0,SEEK_END);
//               int z=ftell(fp);
//               rewind(fp);
//    while(i<=z)
//    {
//      x=fgetc(fp);
//      if(islower(x))
//      {
//          x=x-32;
//      }
//      i++;
//      fputc(x,fp1);
//    }
//    fclose(fp1);
//    fclose(fp);
//}

