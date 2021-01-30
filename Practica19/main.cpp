
#include <iostream>
#include "List.h"


int main()
{
  
  {
    CList<float> floatList;
    floatList.Push(0.1f);
    floatList.Push(0.2f);
    floatList.Push(0.3f);
    floatList.Push(0.4f);

    while (floatList.Size() != 0)
    {
      printf("%f\n", floatList.Pop());
    }
  }

  {
    CList<std::string> stringList;
    stringList.Push("Hola");
    stringList.Push("Cara");
    stringList.Push("Cola");
    while (stringList.Size() != 0)
    {
      printf("%s\n", stringList.Pop().c_str());
    }
  }

  {
    CList<const char*> stringList;
    stringList.Push("Hola");
    stringList.Push("Cara");
    stringList.Push("Cola");
    while (stringList.Size() != 0)
    {
      printf("%s\n", stringList.Pop());
    }
  }
  return 0;
}