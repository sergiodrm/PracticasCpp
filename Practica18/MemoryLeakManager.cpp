#define _CRT_SECURE_NO_WARNINGS 1
#include "MemoryLeakManager.h"
#include <assert.h>
#include <Windows.h>
#include <debugapi.h>

CMemoryLeakMonitor::~CMemoryLeakMonitor()
{
  assert(m_memoryRegister.empty());
}

CMemoryLeakMonitor& CMemoryLeakMonitor::GetInstance()
{
  static CMemoryLeakMonitor instance;
  return instance;
}

void CMemoryLeakMonitor::Insert(const char* _sVarName, const char* _sFile, int _iLine)
{
  assert(_sVarName != nullptr && _sFile != nullptr);

  MemoryRegisterIterator iterator = m_memoryRegister.find(_sVarName);
  if (iterator == m_memoryRegister.end())
  {
    std::pair<std::string, MemoryNewLocation> newItem(_sVarName, MemoryNewLocation(_sFile, _iLine));
    m_memoryRegister.insert(newItem);
  }
}

void CMemoryLeakMonitor::Remove(const char* _sVarName)
{
  assert(_sVarName != nullptr);
  MemoryRegisterIterator iterator = m_memoryRegister.find(_sVarName);
  if (iterator != m_memoryRegister.end())
  {
    m_memoryRegister.erase(_sVarName);
  }
}

void CMemoryLeakMonitor::CheckMemoryState() const
{
  if (!m_memoryRegister.empty())
  {
    for (MemoryRegisterConstIterator iterator = m_memoryRegister.begin(); iterator != m_memoryRegister.end(); iterator++)
    {
      char outputString[256];
      std::string sFile(iterator->second.first);
      int iLine(iterator->second.second);
      std::string sVarName(iterator->first);
      sprintf(outputString, "%s(%d) : %s is still in heap memory.\n", sFile.c_str(), iLine, sVarName.c_str());
      OutputDebugStringA(outputString);
    }
  }
  else OutputDebugString(L"No vars in heap! :)\n");
}
