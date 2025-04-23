#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>

int main(int argc, char* argv[])
{
   if(argc != 3)
   {
    printf("Enter correct command");
    exit(EXIT_FAILURE);
   }
   
   char * pattern = argv[1];
   char * filePath = argv[2];

   FILE * file = fopen(filePath, "r");

   if(!file)
   {
     printf("Error in opening file");
        exit(EXIT_FAILURE);
   }

   char line[1000];

   while (fgets(line, sizeof(line), file) )
   {
     if(strstr(line, pattern))
     {
        printf("%s", line);
     }
   }

   fclose(file);
   

}