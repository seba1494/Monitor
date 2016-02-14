#include "monitor.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/select.h>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;
void *consumer(void *arg); // numer konsumenta
void *producer(void *arg); //
vector<ExpandedMonitor> bufferList;
int K, M;
int producerRun=1;
const int czas_konsumenta = 3;
const int czas_producenta = 1;


int main()
{
  cout << "Podaj ilosc buforow                           : ";
  cin >> M;
  cout << "Podaj ilosc konsumentow                       : ";
  cin >> K;
  
  if (M<1 || K < 2)
  {
    cout << "Zla ilosc konsumentow lub buforow\n";
    return 1;
  }
  
  /*Inicjalizacja buforow*/
  cout << "BUFFERSIZE = 10\n";
  for (int i = 0 ; i < M ; ++i)
  {
    ExpandedMonitor m(i+1);
    bufferList.push_back(m);
  }

  pthread_t producerThread;
  pthread_t consumerThreadList[K];

  /*Tworzenie watka producenta*/
  pthread_create(&producerThread, NULL, producer, NULL);

  /*Tworzenie watkow konsumenta*/
  for (int i = 0; i < K ; ++i)
  {
    pthread_create(&consumerThreadList[i], NULL, consumer, (void*)(intptr_t)(i+1));
    sleep(czas_konsumenta);
  }

  /*Oczekiwanie na zamkniecie operacji konsumentow: */
  for (int i = 0; i < K ; ++i)
  {
    pthread_join(consumerThreadList[i], NULL);
  }
  //sleep(3);
  producerRun = 0; /*Konczymy dzialanie producenta*/
  pthread_kill(producerThread, SIGKILL); // zakonczenie watku producenta
 
  return 0;
}

/*-----------------------------------------------------------------------PRODUCENT-----------------------------------------------------------------------*/

void *producer(void *arg)
{
  int taskNo=0;
  int randomBuffer;
  while (producerRun) /*Dopoki nie zakoncza sie watki konsumenta, producerRun==1*/
  {
    sleep(czas_producenta);
    randomBuffer = rand()%M;
        
    bufferList[randomBuffer].insert('O');
    cout<< "\n";      
         
  } 
}

/*-----------------------------------------------------------------------KONSUMENT-----------------------------------------------------------------------*/

void *consumer(void *arg)
{
  int consumerNumber = (intptr_t) arg;
  int randomBuffer;
  
    
    for( int tmp = M; tmp >= 1 ; tmp--)
    {
      if(bufferList[tmp].sizeofbuffer() == 0)
      {
	continue;
      }
      else
      {
	bufferList[tmp].take(consumerNumber);
	cout<<"\n";
	break;
      }
    }
  
}
