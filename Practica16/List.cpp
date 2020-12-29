#include "List.h"
#include <assert.h>

CList::CList()
  : m_pHead(nullptr), m_pIterator(nullptr), m_uSize(0u)
{}

CList::CList(const CList& _otherList)
{
  CopyList(_otherList);
}

CList::CList(CList&& _otherList)
{
  m_pHead     = _otherList.m_pHead;
  m_pIterator = _otherList.m_pIterator;
  m_uSize     = _otherList.m_uSize;
  _otherList.m_pHead = nullptr;
  _otherList.m_pIterator = nullptr;
}

CList::~CList()
{
  Reset();
}

CList& CList::operator=(const CList& _otherList)
{
  Reset();
  CopyList(_otherList);
  return *this;
}

CList& CList::operator=(CList&& _otherList)
{
  Reset();
  m_pHead = _otherList.m_pHead;
  m_pIterator = _otherList.m_pIterator;
  m_uSize = _otherList.m_uSize;
  _otherList.m_pHead = nullptr;
  _otherList.m_pIterator = nullptr;
  return *this;
}

int CList::Size() const
{
  return m_uSize;
}

int CList::Push(IRenderableObject& _item)
{
  SNode* pLastNode = GetLastNode();
  if (pLastNode == nullptr)
  {
    m_pHead = new SNode();
    m_pIterator = m_pHead;
    m_pHead->m_pData = &_item;
  }
  else
  {
    pLastNode->m_pNext = new SNode();
    pLastNode->m_pNext->m_pData = &_item;
  }
  m_uSize++;
  return m_uSize;
}

IRenderableObject* CList::First() const
{
  return m_pHead == nullptr ? nullptr : m_pHead->m_pData;
}

IRenderableObject* CList::Next()
{
  if (m_pIterator == nullptr)
  {
    return nullptr;
  }
  IRenderableObject* pData = m_pIterator->m_pData;
  m_pIterator = m_pIterator->m_pNext == nullptr ? m_pHead : m_pIterator->m_pNext;
  return pData;
}

IRenderableObject* CList::Pop()
{
  if (m_pHead == nullptr)
  {
    return nullptr;
  }
  IRenderableObject* pData = m_pHead->m_pData;
  SNode* nextHeadNode = m_pHead->m_pNext;
  if (m_pIterator == m_pHead)
    m_pIterator = nextHeadNode;
  delete m_pHead;
  m_pHead = nextHeadNode;
  m_uSize--;
  return pData;
}

void CList::Reset()
{
  while (m_pHead != nullptr)
  {
    SNode* pHeadNode = m_pHead;
    m_pHead = m_pHead->m_pNext;
    delete pHeadNode;
  }
  m_pIterator = nullptr;
  m_uSize = 0;
}

void CList::CopyList(const CList& _other)
{
  m_pHead = new SNode();
  m_pIterator = m_pHead;
  m_uSize = 1;
  m_pHead->m_pData = _other.m_pHead->m_pData;
  SNode* pIndex = m_pHead;
  SNode* pIndexOther = _other.m_pHead->m_pNext;
  while (pIndexOther != nullptr)
  {
    pIndex->m_pNext = new SNode();
    assert(pIndex->m_pNext != nullptr);
    pIndex->m_pNext->m_pData = pIndexOther->m_pData;
    pIndex = pIndex->m_pNext;
    pIndexOther = pIndexOther->m_pNext;
    m_uSize++;
  }
}

SNode* CList::GetLastNode() const
{
  if (m_pHead == nullptr) 
    return nullptr;

  SNode* pIndex = m_pIterator;
  while (pIndex->m_pNext != nullptr)
  {
    pIndex = pIndex->m_pNext;
  }
  return pIndex;
}
