#pragma once

#include <string>


#define DECLARE_ENTRY(_VALUE) _VALUE,

#define ENUM_TO_STR(_ENUM) \
if (_ENUM == _eEnum) { return #_ENUM; }

#define STR_TO_ENUM(_STR) \
if (strcmp(_sEnum, #_STR) == 0) { return _STR; }

#define CREATE_ENUM(_NAME, A, B, C)         \
struct S##_NAME                             \
{                                           \
  enum Enum : int                           \
  {                                         \
    Invalid = -1,                           \
    DECLARE_ENTRY(A)                        \
    DECLARE_ENTRY(B)                        \
    DECLARE_ENTRY(C)                        \
    Count                                   \
  };                                        \
                                            \
  static const char* AsStr(Enum _eEnum)     \
  {                                         \
    ENUM_TO_STR(A)                          \
    ENUM_TO_STR(B)                          \
    ENUM_TO_STR(C)                          \
    return "Invalid";                       \
  }                                         \
                                            \
  static Enum AsEnum(const char* _sEnum)    \
  {                                         \
    STR_TO_ENUM(A)                          \
    STR_TO_ENUM(B)                          \
    STR_TO_ENUM(C)                          \
    return Invalid;                         \
  }                                         \
}

/* Modelo de estructura */

//struct SEnum
//{
//  enum EEnum : int
//  {
//    INVALID = -1,
//    ZERO,
//    ONE,
//    TWO,
//    THREE,
//    COUNT
//  };
//
//  static const char* AsStr(EEnum _eEnum)
//  {
//    switch (_eEnum)
//    {
//    case ZERO: return "ZERO";
//    case ONE: return "ONE";
//    case TWO: return "TWO";
//    case THREE: return "THREE";
//    default: return "Invalid";
//    }
//  }
//
//  static EEnum AsEnum(const char* _sEnum)
//  {
//    if (strcmp("ZERO", _sEnum) == 0)
//    {
//      return ZERO;
//    } else if (strcmp("ONE", _sEnum) == 0)
//    {
//      return ONE;
//    } else if (strcmp("TWO", _sEnum) == 0)
//    {
//      return TWO;
//    } else if (strcmp("THREE", _sEnum) == 0)
//    {
//      return THREE;
//    }
//    return INVALID;
//  }
//};