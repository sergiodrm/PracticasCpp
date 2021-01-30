#pragma once

#include <assert.h>

template <typename T>
struct SNode
{
  T m_pData;
  SNode<T>* m_pNext;
  SNode() : m_pData(), m_pNext(nullptr) {}
};

template <typename T>
class CList
{
private:

  SNode<T>* m_pHead;
  SNode<T>* m_pIterator;
  unsigned int m_uSize;

public:

  CList() : m_pHead(nullptr), m_pIterator(nullptr), m_uSize(0)
  {}

  unsigned int Push(const T& _data)
  {
    SNode<T>* pNewData = new SNode<T>();
    pNewData->m_pData = _data;
    if (m_pHead == nullptr)
    {
      m_pHead = pNewData;
      m_pIterator = pNewData;
    }
    else
    {
      m_pIterator->m_pNext = pNewData;
      m_pIterator = m_pIterator->m_pNext;
    }
    m_uSize++;
    return m_uSize;
  }

  const T& First() const
  {
    if (m_pHead != nullptr)
    {
      return m_pHead->m_pData;
    }
    return T();
  }

  const T& Next()
  {
    T* data = &m_pIterator->m_pData;
    m_pIterator = m_pIterator->m_pNext == nullptr ? m_pHead : m_pIterator->m_pNext;
    return *data;
  }

  const T& Pop()
  {
    assert(m_pHead != nullptr);
    T* data = &m_pHead->m_pData;
    if (m_pIterator == m_pHead)
    {
      m_pIterator = m_pIterator->m_pNext;
    }
    m_pHead = m_pHead->m_pNext;
    m_uSize--;
    return *data;
  }

  inline unsigned int Size() const { return m_uSize; }

};

