
#include <iostream>

#define MEMORY_LEAKS_MONITOR
#include "MemoryLeakManager.h"

class CVector
{
public:

  float m_fX;
  float m_fY;

  CVector() : m_fX(0.f), m_fY(0.f) {}
  CVector(float _fX, float _fY) :
  m_fX(_fX), m_fY(_fY) {}
};

int main()
{
  CHECK_MEMORY_STATE;

  NEW(int, pValue, 2);
  NEW(CVector, pPosition, 2.3f, 1.5f);
  NEW(CVector, pSize);

  CHECK_MEMORY_STATE;
  pSize->m_fX++;
  DELETE_VAR(pValue);
  DELETE_VAR(pPosition);
  DELETE_VAR(pSize);
  CHECK_MEMORY_STATE;

  NEW_ARRAY(char, sStr, 10);
  CHECK_MEMORY_STATE;
  DELETE_ARRAY(sStr);
  CHECK_MEMORY_STATE;
  return 0;
}