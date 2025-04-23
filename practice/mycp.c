#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <string.h>

int main(int argc, char * argv[])
{
   if(argc != 3)
   {
    printf("Enter correct command");
    exit(EXIT_FAILURE);
   }

   char *srcfile = argv[1];
   char *destfile = argv[2];

    FILE *src = fopen(srcfile, "r");
    if(!src)
    {
        printf("Error in opening file src");
        exit(EXIT_FAILURE);
    }


    FILE *dest = fopen(destfile, "w");
    if(!dest)
    {
        printf("Error in opening file dest");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char *buffer[1000];
    int bytes;

    while ((bytes = fread(buffer, 1, 1000, src)) > 0)
    {
        if( fwrite(buffer, 1, bytes, dest) != bytes)
        {
            printf("Error in copy pasting..");
            fclose(src);
            fclose(dest);
            exit(EXIT_FAILURE);
        }
    }

    fclose(src);
    fclose(dest);

    printf("Task of copy paste is done"); 


}