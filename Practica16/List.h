#pragma once

#include "RenderableObject.h"

struct SNode
{
  SNode* m_pNext;
  IRenderableObject* m_pData;

  explicit SNode() : m_pNext(nullptr), m_pData(nullptr) {}
};

class CList
{

public:

  explicit CList();
  explicit CList(const CList& _otherList);
  explicit CList(CList&& _otherList);
  ~CList();

  CList& operator=(const CList& _otherList);
  CList& operator=(CList&& _otherList);

  int Size() const;
  int Push(IRenderableObject& _item);
  IRenderableObject* First() const;
  IRenderableObject* Next();
  IRenderableObject* Pop();
  void Reset();

private:

  void CopyList(const CList& _other);
  SNode* GetLastNode() const;

private:

  SNode* m_pHead;
  SNode* m_pIterator;
  unsigned int m_uSize;
};

