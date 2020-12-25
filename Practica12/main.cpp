
#include "String.h"
#include <string>

int main()
{
  //CString myString1("Hola");
  //CString myString2(myString1);
  //if (myString1 == myString2)
  //{
  //  printf("Cadenas iguales\n");
  //}
  //else printf("Cadenas distintas\n");

  //CString myString;
  //myString = CString::HexFromInt(87523);
  //printf("%s\n", myString.ToCString());

  //myString = CString::FromInt(12345);
  //printf("%s\n", myString.ToCString());
  //printf("%d\n", myString.ToInt());
  //myString = CString::FromFloat(231.645f);
  //printf("%s\n", myString.ToCString());
  //printf("%f\n", myString.ToFloat());

  CString myString("Hola como estas!");
  int index = myString.Find("estas", 0);
  printf("%s\n", myString.Mid(index, 6).ToCString());
  CString otherString = myString.Replace("estas", "andas!");
  printf("%s\n", otherString.Mid(index, 6).ToCString());
  
  

  return 0;
}