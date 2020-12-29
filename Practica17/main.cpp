
#include <iostream>
#include "Macros.h"

#define EXPAND(X) X
#define GET_SIXTH_ARGUMENT(a1, a2, a3, a4, a5, a6, ...) a6
#define COUNT_ARGUMENT(...) \
EXPAND(GET_SIXTH_ARGUMENT(__VA_ARGS__, 5, 4, 3, 2, 1, 0))


CREATE_ENUM(WarriorTypes, Weak, Normal, Strong);

int main()
{
  if (SWarriorTypes::AsEnum("Weak") == SWarriorTypes::Weak)
    printf("%s\n", SWarriorTypes::AsStr(SWarriorTypes::Weak));
  if (SWarriorTypes::AsEnum("Normal") == SWarriorTypes::Normal)
    printf("%s\n", SWarriorTypes::AsStr(SWarriorTypes::Normal));
  if (SWarriorTypes::AsEnum("Strong") == SWarriorTypes::Strong)
    printf("%s\n", SWarriorTypes::AsStr(SWarriorTypes::Strong));
  
  return 0;
}