#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t wrt;
pthread_mutex_t mutex;
int bookcount = 100;
int numreader = 0;

void *addBook(void *wno)
{
  int booksadd = 20;
  sem_wait(&wrt);
  bookcount += booksadd;
  printf("%d books added , bookscount: %d",booksadd, bookcount);
  sem_post(&wrt);
}

void *removeBook(void *wno)
{
  int booksremove = 20;
  sem_wait(&wrt);
  bookcount -= booksremove;
  printf("%d books removed , bookscount: %d",booksremove, bookcount);
  sem_post(&wrt);
}

void *read(void *rno)
{
   //entry section
   pthread_mutex_lock(&mutex);
   numreader++ ;
   if(numreader == 1) 
   {
    sem_wait(&wrt);
   }
   pthread_mutex_unlock(&mutex);

   //critical section
   printf("Reader is reading total books bookcount : %d",bookcount);

   //exit section
   pthread_mutex_lock(&mutex);
   numreader-- ;
   if(numreader == 0)
   {
    sem_post(&wrt);
   }
   pthread_mutex_unlock(&mutex);

}

int main()
{   
   pthread_t readerThreads[10], librarianThreads[5];
   int ids[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    char actions[] = {'R', 'A', 'A', 'R', 'A'};

    //active / initialise the mutexs, semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0,1);

    //5 readers
    for (int i = 0; i < 5; i++)
    {
       pthread_create(&readerThreads[i], NULL, read, (void *)&ids[i]);
    }
    

    //10 writers
    for (int i = 0; i < 10; i++)
    {
        if(actions[i] == 'A')
        {
            pthread_create(&librarianThreads[i], NULL, addBook, (void *)&ids[i]);
        }
        else
        {
             pthread_create(&librarianThreads[i], NULL, removeBook, (void *)&ids[i]);
        }
    }
    

    //5 readers
    for (int i = 0; i < 5; i++)
        {
        pthread_create(&readerThreads[i], NULL, read, (void *)&ids[i]);
        }
    

    //wait for all treads to complete
    for (int i = 0; i < 10; i++)
    {
        pthread_join(readerThreads[i],NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(librarianThreads[i],NULL);
    }
    

    //clean up the resorces
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);


    return 0 ;



}