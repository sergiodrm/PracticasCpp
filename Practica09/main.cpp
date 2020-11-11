
#include <iostream>
#include "CList.h"


int main()
{
  printf("--- PRACTICA 9 ---\n\n");
  CList oMyList;

  oMyList.Push("Hola");
  oMyList.Push("Cara");
  oMyList.Push("Cola");
  
  for (unsigned int uIndex = 0; uIndex < oMyList.Size(); ++uIndex)
  {
    printf("-Elemento %d de %d: %s\n", uIndex, oMyList.Size(), oMyList.Next());
  }

  CList oMyCopyList(oMyList);

  while (oMyList.Size() != 0)
  {
    printf("Borrando cadena \"%s\" de la lista.\n", oMyList.Pop());
    printf("Quedan %d cadenas.\n", oMyList.Size());
  }

  for (unsigned int uIndex = 0; uIndex < oMyCopyList.Size(); ++uIndex)
  {
    printf("-Elemento %d de %d: %s\n", uIndex, oMyCopyList.Size(), oMyCopyList.Next());
  }

  printf("\n\n\n");
  return 0;
}