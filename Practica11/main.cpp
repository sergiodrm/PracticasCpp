
#include <iostream>
#include "CList.h"

class A
{
public:

  A() : x(0.f) {}

  A& GetNewA() const
  {
    A* a = new A;
    a->x = 2.f;
    return *a;
  }
  ~A() {}

  float x;
};

int main()
{
  //printf("------ PRACTICA 11 ------\n\n");

  //CList objList;
  //objList.Push("Head");
  //objList.Push("Middle1");
  //objList.Push("Middle2");
  //objList.Push("Middle3");
  //objList.Push("Tail");

  //printf("Lista original: ");
  //objList.PrintList();
  //printf("\nLista inversa: ");
  //objList.GetReverseList(objList).PrintList();
  //printf("\n");
  A a;
  A* pA;

  {
    A a2;
    pA = &a2;

    a2 = a.GetNewA();
  }

  return 0;
}