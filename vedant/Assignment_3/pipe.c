#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    int fd[2];
    if(argc != 3)
    {
        printf("3 arg only");
        return 1;
    }

    if(pipe(fd)==-1)
    {
        printf("Pipe creation failed");
        return 1;
    }

    int src = open(argv[1],O_RDONLY);
    if(src==-1){printf("Error in opening source file"); return 1;}

    dup2(src,STDIN_FILENO);
    close(src);

    pid_t pidValue= fork();
    if(pidValue>0)
    {
        // parent sort
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execl("/usr/bin/sort","sort",NULL);
        perror("Exe fail");
    }else if (pidValue==0)
    {
        // child process 
        dup2(fd[0],STDIN_FILENO);
        close(fd[1]);

        int dest_file= open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
        if(dest_file==-1){printf("Error in opening dest file"); return 1;}

        dup2(dest_file,STDOUT_FILENO);
        close(dest_file);
        close(fd[0]);
        execl("/usr/bin/uniq","uniq",NULL);
        perror("Error in child process");
    }else 
    {
        printf("Error in forking");
        return 1;
    }

    return 0;

    
}