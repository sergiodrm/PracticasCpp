
#include <iostream>

#include "MemoryLeakManager.h"

int main()
{
  CHECK_MEMORY_STATE;

  NEW(int, iValue, 2);

  *iValue = 4;

  CHECK_MEMORY_STATE;

  DELETE_VAR(iValue);
  CHECK_MEMORY_STATE;
  return 0;
}