
// FileUtilities.cpp

#define _CRT_SECURE_NO_WARNINGS 1

#include "FileUtilities.h"
#include <stdio.h>

struct SFileID
{
  FILE* m_pFile;
};

FID OpenFile(const char* _sFileName, const char* _sOpenMode)
{
  FID pFid_ = new SFileID; // new (!)
  pFid_->m_pFile = fopen(_sFileName, _sOpenMode);
  if (pFid_->m_pFile)
  {
    return pFid_;
  }
  delete pFid_; // delete (!)
  return nullptr;
}

int CloseFile(FID& _rFid)
{
  int iStatus_ = fclose(_rFid->m_pFile);
  delete _rFid; // delete (!)
  return iStatus_;
}

int ReadFile(const FID& _rFid, char* _sOutput_, const unsigned int _uNum)
{
  // Comprobar el idenficador
  if (_rFid->m_pFile)
  {
    // Comprobar los parametros
    if (_uNum != 0 && _sOutput_)
    {
      return fread(_sOutput_, sizeof(char), _uNum, _rFid->m_pFile);
    }
  }
  return -1; // La lectura ha fallado por el identificador o por el modo de apertura.
}

int WriteFile(const FID& _rFid, const char* _sString, const unsigned int _uNum)
{
  // Comprobar el identificador y los parametros
  if (_rFid->m_pFile && _sString && _uNum != 0)
  {
    return fwrite(_sString, sizeof(char), _uNum, _rFid->m_pFile);
  }
  return -1;
}
