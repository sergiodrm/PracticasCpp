#include <stdio.h>
#include <string.h>

#define DECLARE_SUPER(_CLASS) typedef _CLASS Super

#define SAFE_DELETE(_PTR)  \
if (_PTR) \
{ \
  delete _PTR; \
  _PTR = nullptr; \
}

#define DECLARE_ENUM_ENTRY(_VALUE) _VALUE,

#define CONVERT_CHAR_TO_ENUM(_VALUE) \
if (strcmp(_sValue, #_VALUE) == 0) \
{ \
  return _VALUE; \
}

#define CONVERT_ENUM_TO_CHAR(_VALUE) \
if (_eEnum == _VALUE) \
{ \
  return #_VALUE; \
}

//#define DECLARE_ENUM(_NAME, _LIST) \
//struct _NAME \
//{ \
//  enum Enum \
//  { \
//    Invalid = -1, \
//    _LIST(DECLARE_ENUM_ENTRY) \
//    Count \
//  }; \
//  static Enum AsEnum(const char* _sValue) \
//  { \
//    _LIST(CONVERT_CHAR_TO_ENUM) \
//    if (strcmp(_sValue, "Count") == 0) \
//    { \
//      return Count; \
//    } \
//    return Invalid; \
//  } \
//  static const char* AsStr(Enum _eEnum) \
//  { \
//    _LIST(CONVERT_ENUM_TO_CHAR) \
//    if (_eEnum == Count) \
//    { \
//      return "Count"; \
//    } \
//    return "Invalid"; \
//  } \
//};
//
//#define MI_ENUM_VALUES(_CALL) \
//  _CALL(A) \
//  _CALL(B) \
//  _CALL(C)
//
//DECLARE_ENUM(EMiEnum, MI_ENUM_VALUES)

#define EXPAND(x) x
#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, NAME) NAME
// Foreach macros FE
#define FE_1(_WHAT, X) _WHAT(X)
#define FE_2(_WHAT, X, ...) EXPAND(_WHAT(X)FE_1(_WHAT, __VA_ARGS__))
#define FE_3(_WHAT, X, ...) EXPAND(_WHAT(X)FE_2(_WHAT, __VA_ARGS__))
#define FE_4(_WHAT, X, ...) EXPAND(_WHAT(X)FE_3(_WHAT, __VA_ARGS__))
#define FE_5(_WHAT, X, ...) EXPAND(_WHAT(X)FE_4(_WHAT, __VA_ARGS__))
#define FE_6(_WHAT, X, ...) EXPAND(_WHAT(X)FE_5(_WHAT, __VA_ARGS__))
#define FE_7(_WHAT, X, ...) EXPAND(_WHAT(X)FE_6(_WHAT, __VA_ARGS__))
// La macro que itera cada uno los argumentos
#define MACRO_FOR_EACH_ARGUMENT(_ACTION, ...) \
 EXPAND(GET_MACRO(__VA_ARGS__, FE_7, FE_6, FE_5, FE_4, FE_3, FE_2, FE_1)(_ACTION, __VA_ARGS__))

#define DECLARE_ENUM(_NAME, ...) \
struct _NAME \
{ \
  enum Enum \
  { \
    Invalid = -1, \
    MACRO_FOR_EACH_ARGUMENT(DECLARE_ENUM_ENTRY, __VA_ARGS__) \
    Count \
  }; \
  static Enum AsEnum(const char* _sValue) \
  { \
    MACRO_FOR_EACH_ARGUMENT(CONVERT_CHAR_TO_ENUM, __VA_ARGS__) \
    if (strcmp(_sValue, "Count") == 0) \
    { \
      return Count; \
    } \
    return Invalid; \
  } \
  static const char* AsStr(Enum _eEnum) \
  { \
    MACRO_FOR_EACH_ARGUMENT(CONVERT_ENUM_TO_CHAR, __VA_ARGS__) \
    if (_eEnum == Count) \
    { \
      return "Count"; \
    } \
    return "Invalid"; \
  } \
};

DECLARE_ENUM(EMiEnumA, A, B, C, D, E, F, G)

DECLARE_ENUM(EFaction, Player, NPC, Enemy)

int main()
{

  printf("Enum Values\n");
  for (unsigned int uIndex = 0; uIndex < EMiEnum::Count; ++uIndex)
  {
    printf("%s\n", EMiEnum::AsStr(EMiEnum::Enum(uIndex)));
  }


  EMiEnum::Enum eA = EMiEnum::AsEnum("A");
  printf("A: %s\n", EMiEnum::AsStr(eA));
  EMiEnum::Enum eB = EMiEnum::AsEnum("B");
  printf("B: %s\n", EMiEnum::AsStr(eB));
  EMiEnum::Enum eC = EMiEnum::AsEnum("C");
  printf("C: %s\n", EMiEnum::AsStr(eC));

}
