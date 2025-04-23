#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>

void simulatecp(const char * source, const char * destination)
{
  struct stat buffer ;
  if(stat(source, &buffer) != 0)
  {
    printf("not able to access file. not available or permission error");
    return;
  }

  pid_t pid = fork();

  if(pid < 0 )
  {
    printf("Error in creating child process");
    perror("fork failed");
    exit(EXIT_FAILURE);
  }
  else if (pid == 0)
  {
    //child process
    printf("child pid : %d , parent pid : %d\n", getpid(), getppid());
    execlp("./mycp", "mycp", source, destination, NULL);
    perror("execlp failed");
    exit(EXIT_FAILURE);
  }
  else 
  {
    wait(NULL);
    printf("copy pasting completed");
  }

  
}

void simulategrep(const char * pattern, const char * file)
{ 
    struct stat buffer;
    if(stat(file, &buffer) != 0)
    {
         printf("not able to access file. not available or permission error");
         return;
    }

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
            //child process
        printf("child pid : %d , parent pid : %d\n", getpid(), getppid());
        execlp("grep", "grep", pattern, file, NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
        
    }
    else 
    {
        wait(NULL);
        printf("pattern found");
    }

}



int main()
{
    int ch;
    char source[100], destination[100], pattern[100], file[100];

    printf("1. cp \n 2. grep \n Enter the choise");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        printf("enter the source file : ");
        scanf("%s", source);
        printf("enter the destination file : ");
        scanf("%s", destination);
        simulatecp(source, destination);
        break;
    case 2:
        printf("enter the pattern to find : ");
        scanf("%s", pattern);
        printf("enter the file to be searched in : ");
        scanf("%s", file);
        simulategrep(pattern, file);
        break;
    
    default:
        printf("Enter valid option");
        break;
    }
    

}