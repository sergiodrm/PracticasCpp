#pragma once

#include <map>
#include <string>

#ifdef MEMORY_LEAKS_MONITOR


#define NEW(_TYPE, _VAR_NAME, ...)                                            \
CMemoryLeakMonitor::GetInstance().Insert(#_VAR_NAME, __FILE__, __LINE__);     \
_TYPE* _VAR_NAME = new _TYPE(__VA_ARGS__)

#define NEW_ARRAY(_TYPE, _VAR_NAME, _AMOUNT)                                  \
CMemoryLeakMonitor::GetInstance().Insert(#_VAR_NAME, __FILE__, __LINE__);     \
_TYPE* _VAR_NAME = new _TYPE[_AMOUNT]

// Le cambio el nombre para que no me de redefinition con una macro de winnt.h
#define DELETE_VAR(_VAR_NAME)                                                 \
CMemoryLeakMonitor::GetInstance().Remove(#_VAR_NAME);                         \
delete _VAR_NAME

#define DELETE_ARRAY(_VAR_NAME)                                               \
CMemoryLeakMonitor::GetInstance().Remove(#_VAR_NAME);                         \
delete[] _VAR_NAME

#define CHECK_MEMORY_STATE                                                    \
CMemoryLeakMonitor::GetInstance().CheckMemoryState()

#endif // MEMORY_LEAKS_MONITOR

class CMemoryLeakMonitor
{
private:

  typedef std::pair<std::string, int>                              MemoryNewLocation;

  typedef std::map<std::string, MemoryNewLocation>::iterator       MemoryRegisterIterator;
  typedef std::map<std::string, MemoryNewLocation>::const_iterator MemoryRegisterConstIterator;

private:

  std::map<std::string, MemoryNewLocation> m_memoryRegister;

private:

  CMemoryLeakMonitor() {}

public:

  ~CMemoryLeakMonitor();
  CMemoryLeakMonitor(const CMemoryLeakMonitor&) = delete;
  void operator=(const CMemoryLeakMonitor&)     = delete;

  static CMemoryLeakMonitor& GetInstance();

  void Insert(const char* _sVarName, const char* _sFile, int _iLine);
  void Remove(const char* _sVarName);

  void CheckMemoryState() const;
};


