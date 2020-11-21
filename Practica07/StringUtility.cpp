
#include "StringUtility.h"

#include <iostream>

void CopyString(char* _sDestiny_, const char* _sOrigin, unsigned int _uSizeToCopy)
{
  if (_sDestiny_ && _sOrigin)
  {
    unsigned int uIndex = 0;
    while (uIndex < _uSizeToCopy && _sDestiny_[uIndex] != '\0')
    {
      _sDestiny_[uIndex] = _sOrigin[uIndex];
      ++uIndex;
    }
  }
  else printf("[Function: CopyString, Line: %d] Input arguments error.\n", __LINE__);
}

char* ConcatenateString(const char* _sString1, const char* _sString2, unsigned int _uSizeToConcatenate)
{
  if (!_sString1 && !_sString2)
    return nullptr;

  unsigned int uSizeString1 = strlen(_sString1);
  unsigned int uSizeString2 = _uSizeToConcatenate == 0 ? strlen(_sString2) : _uSizeToConcatenate;

  unsigned int uNewSize = uSizeString1 + uSizeString2 + 1;
  char* sNewString = new char[uNewSize];
  sNewString[uNewSize - 1] = '\0';

  unsigned int uIndexNewString = 0;
  const char* pIterator = _sString1;

  while (sNewString[uIndexNewString] != '\0')
  {
    sNewString[uIndexNewString] = *pIterator;
    ++uIndexNewString;
    ++pIterator;
    if (*pIterator == '\0')
      pIterator = _sString2;
  }
  return sNewString;
}
