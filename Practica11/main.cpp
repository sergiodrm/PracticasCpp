
#include <iostream>
#include "CList.h"


int main()
{
  //printf("------ PRACTICA 11 ------\n\n");

  CList objList;
  objList.Push("Head");
  objList.Push("Middle1");
  objList.Push("Middle2");
  objList.Push("Middle3");
  objList.Push("Tail");

  printf("Lista original: ");
  objList.PrintList();
  printf("\nLista inversa: ");
  CList inverseList = objList.GetReverseList();
  inverseList.PrintList();
  printf("\n");

  return 0;
}