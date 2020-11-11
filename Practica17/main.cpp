
#include <iostream>
#include <string>
#include <stdarg.h>

//#ifdef _DEBUG
//// Debug
//#else
//// No debug
//#endif
//
//#define DEBUG_PRINT(...) _DebugPrint(__FILE__, __LINE__, __VA_ARGS__);
//
//#define EXECUTE_ACTION(_VALUE, _TRIGGER, _ACTION) \
//  if (_VALUE == _TRIGGER) DEBUG_PRINT("Action executed: %s\n", #_ACTION); \
//  else DEBUG_PRINT("Not an action!\n");
//
//#define ACTIONS_LIST(_VALUE, _CALL) \
//  _CALL(_VALUE, 0, Fire) \
//  _CALL(_VALUE, 1, Jump) \
//  _CALL(_VALUE, 2, Crouch) \
//  _CALL(_VALUE, 3, SpecialAbility)
//
//#define CHECK_ACTION(_VALUE) ACTIONS_LIST(_VALUE, EXECUTE_ACTION)
//
//
//void _DebugPrint(const char* _sFilename, int _iLineNumber, const char* _sFormat, ...);

#define DECLARE_ENUM_ENTRY(_VALUE) _VALUE,

#define CONVERT_ENUM_TO_CHAR(_VALUE) \
if (_VALUE == _eEnum) { return #_VALUE; }


#define CONVERT_CHAR_TO_ENUM(_VALUE) \
if (strcmp(_sValue, #_VALUE) == 0) { return _VALUE; }

#define DECLARE_ENUM(_NAME, A, B, C)        \
struct _NAME                                \
{                                           \
  enum Enum                                 \
  {                                         \
    Invalid = -1,                           \
    DECLARE_ENUM_ENTRY(A)                   \
    DECLARE_ENUM_ENTRY(B)                   \
    DECLARE_ENUM_ENTRY(C)                   \
    Count                                   \
  };                                        \
  static const char* AsStr(Enum _eEnum)     \
  {                                         \
    CONVERT_ENUM_TO_CHAR(A)                 \
    CONVERT_ENUM_TO_CHAR(B)                 \
    CONVERT_ENUM_TO_CHAR(C)                 \
    CONVERT_ENUM_TO_CHAR(Count)             \
    return "Invalid";                       \
  }                                         \
  static Enum AsEnum(const char* _sValue)   \
  {                                         \ 
    CONVERT_CHAR_TO_ENUM(A)                 \
    CONVERT_CHAR_TO_ENUM(B)                 \
    CONVERT_CHAR_TO_ENUM(C)                 \
    CONVERT_CHAR_TO_ENUM(Count)             \
    return Invalid;                         \
  }                                         \
};

//struct EMiEnum
//{
//  enum MyEnum
//  {
//    Invalid = -1,
//    A,
//    B,
//    C,
//    Count
//  };
//
//  const char* AsStr(MyEnum _eEnum)
//  {
//    if (_eEnum == Invalid)
//    {
//      return "Invalid";
//    }
//    if (_eEnum == A)
//    {
//      return "A";
//    }
//    // ...
//  }
//  MyEnum AsEnum(const char* _sValue)
//  {
//    return A;
//  }
//};

DECLARE_ENUM(EActions, Fire, Jump, Crouch)

int main()
{
  /*for (unsigned int uAction = 0; uAction < 5; ++uAction)
    CHECK_ACTION(uAction);*/


  

  return 0;
}

//void _DebugPrint(const char* _sFilename, int _iLineNumber, const char* _sFormat, ...)
//{
//  printf("[%s:%d] ", _sFilename, _iLineNumber);
//
//  va_list argptr;
//  va_start(argptr, _sFormat);
//  vprintf(_sFormat, argptr);
//  va_end(argptr);
//}
