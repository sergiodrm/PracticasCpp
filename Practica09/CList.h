#pragma once

class CNode;

class CList
{
public:

  explicit CList();
  explicit CList(const CList& _rOther);
  explicit CList(CList&& _rOther) noexcept;
  ~CList();

  const CList& operator=(const CList& _rOther);
  const CList& operator=(CList&& _rOther);

  unsigned int Size() const;
  int Push(const char* _sData);
  const char* First() const;
  const char* Next();
  const char* Pop();
  void Reset();

  void PrintList(const char* _sSeparator = ", ") const;

private:

  void CopyList(const CList& _rOther);

  CNode* m_pHead;
  CNode* m_pIterator;
  unsigned int m_uListSize;
};

