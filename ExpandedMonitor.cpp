#include "monitor.h"
#include <iostream>

using namespace std;

ExpandedMonitor::ExpandedMonitor(int no)
{
  bufferNumber=no;
  size=0;
  for (int i=0; i < BUFFERSIZE ; ++i)
  {
    buffer[i]='-';
  }
  printElements();
}
ExpandedMonitor::~ExpandedMonitor()
{
}


/*----------------------------------- PRODUKCJA/USUWANIE 1 ELEMENTU -----------------------------------*/

void ExpandedMonitor::insert(char element) // wlozenie pojedynczego elementu
{
  enter();
  if(size==BUFFERSIZE) wait(full); //jezeli jest pelen bufor, czekamy zmiennej warunkowej
    cout << "(Producent) Dodaje element do bufora nr: "<< bufferNumber <<  endl;
   buffer[size++] = element;
   printElements();
   if(size==1) signal(empty); // jezeli to jest pierwszy element, odwieszamy watek czekajacy i opuszczamy monitor
   leave();
}

void ExpandedMonitor::take(int cnum) //zabranie pojedynczego elementu
{
  enter();
  if(size==0) wait(empty);
  printf("\n(Konsument nr: %d) Zabieram element z bufora %d\n",cnum,bufferNumber );
  buffer[--size] = '-';
  printElements();
  if(size==BUFFERSIZE-1) signal(full);
  leave();
}


/*Funkcja pomocnicza do wypisywania elementow bufora*/
void ExpandedMonitor::printElements() // wyswietlenie wszystkich elementow
{
  cout << "Zawartosc Bufora " << bufferNumber << " : ";
  for (int i=0; i < BUFFERSIZE ; ++i)
  {
    cout << buffer[i];
  }
  cout << "\n";
}

int ExpandedMonitor::sizeofbuffer()
{
  return size;
}