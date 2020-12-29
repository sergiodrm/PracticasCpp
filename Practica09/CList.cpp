#include "CList.h"
#include <string>
#include <assert.h>


CList::CList() :
  m_pHead(nullptr),
  m_pIterator(nullptr),
  m_uListSize(0)
{}

CList::CList(const CList& _rOther)
{
  CopyList(_rOther);
}

CList::CList(CList&& _rOther) noexcept
{
  // Robar los punteros
  m_pHead = _rOther.m_pHead;
  m_pIterator = _rOther.m_pIterator;
  m_uListSize = _rOther.m_uListSize;
  _rOther.m_pHead = nullptr;
  _rOther.m_pIterator = nullptr;
}

CList::~CList()
{
  Reset();
}

CList& CList::operator=(const CList& _rOther)
{
  Reset();
  CopyList(_rOther);
  return *this;
}

CList& CList::operator=(CList&& _rOther)
{
  Reset();
  // Robar los punteros
  m_pHead = _rOther.m_pHead;
  m_pIterator = _rOther.m_pIterator;
  m_uListSize = _rOther.m_uListSize;
  _rOther.m_pHead = nullptr;
  _rOther.m_pIterator = nullptr;
  return *this;
}

unsigned int CList::Size() const
{
  return m_uListSize;
}

int CList::Push(const char* _sData)
{
  assert(_sData != nullptr);
  if (m_pHead)
  {
    // Crear un ptr para recorrer la lista y no tener que modificar la posicion de m_pIterator
    SNode* pIt = m_pHead;
    // Buscar el ultimo elemento de la lista actual
    while (pIt->GetNextNode() != nullptr)
    {
      pIt = pIt->GetNextNode();
    }
    // Cambiar la referencia del siguiente nodo al elemento creado
    pIt->m_pNext = new SNode();
    pIt->m_pNext->m_sData = CopyData(_sData);
  }
  else
  {
    m_pHead = new SNode();
    m_pHead->m_sData = CopyData(_sData);
    m_pHead->m_pNext = nullptr;
    m_pIterator = m_pHead;
  }
  ++m_uListSize;
  return m_uListSize;
}

const char* CList::First() const
{
  if (m_pHead)
  {
    return m_pHead->GetData();
  }
  else return nullptr;
}

const char* CList::Next()
{
  assert(m_pIterator != nullptr);
  const char* sData_ = m_pIterator->GetData();
  if (m_pIterator->GetNextNode() == nullptr)
  {
    m_pIterator = m_pHead;
  }
  else
  {
    m_pIterator = m_pIterator->GetNextNode();
  }
  return sData_;
}

const char* CList::Pop()
{
  if (m_pHead)
  {
    // Guardar el siguiente nodo del head para referenciarlo luego
    SNode* pNextHead = m_pHead->GetNextNode();
    if (m_pHead == m_pIterator)
    {
      m_pIterator = pNextHead;
    }

    const char* sOutput_ = CopyData(m_pHead->GetData());
    delete m_pHead->m_sData;
    delete m_pHead;
    m_pHead = pNextHead;
    m_uListSize--;
    return sOutput_;
  }
  // No hay elementos en la lista
  return nullptr;
}

void CList::Reset()
{
  while (m_pHead != nullptr)
  {
    SNode* pNext = m_pHead->GetNextNode();
    delete m_pHead->m_sData;
    delete m_pHead;
    m_pHead = pNext;
  }
  m_pIterator = nullptr;
  m_uListSize = 0;
}

void CList::PrintList(const char* _sSeparator) const
{
  if (_sSeparator)
  {
    SNode* pIndexNode = m_pHead;
    while (pIndexNode != nullptr)
    {
      printf("%s", pIndexNode->GetData());
      pIndexNode = pIndexNode->GetNextNode();
      if (pIndexNode)
        printf("%s", _sSeparator);
    }
  }
}

//CList CList::GetReverseList(CList _lstSrc)
//{
//  if (_lstSrc.Size() == 0)
//    return CList();
//
//  CList reversedList;
//
//  SNode* pIndex = new SNode();
//  assert(pIndex != nullptr);
//  SNode* pReverseIndex = GetPreviousNode(_lstSrc, nullptr);
//  assert(pReverseIndex != nullptr);
//  pIndex->m_sData = CopyData(pReverseIndex->GetData());
//  reversedList.m_pHead = pIndex;
//  reversedList.m_pIterator = pIndex;
//  reversedList.m_uListSize++;
//
//  while (pReverseIndex != _lstSrc.m_pHead)
//  {
//    pReverseIndex = GetPreviousNode(_lstSrc, pReverseIndex);
//    assert(pReverseIndex != nullptr);
//    pIndex->m_pNext = new SNode();
//    assert(pIndex != nullptr);
//    pIndex = pIndex->GetNextNode();
//    pIndex->m_sData = CopyData(pReverseIndex->GetData());
//  }
//  return reversedList;
//}

CList CList::GetReverseList() const
{
  assert(m_pHead != nullptr);
  CList reversedList;

  SNode* pIndex = new SNode();
  assert(pIndex != nullptr);
  SNode* pReverseIndex = GetPreviousNode(*this, nullptr);
  assert(pReverseIndex != nullptr);
  pIndex->m_sData = CopyData(pReverseIndex->GetData());
  reversedList.m_pHead = pIndex;
  reversedList.m_pIterator = pIndex;
  reversedList.m_uListSize++;

  while (pReverseIndex != m_pHead)
  {
    pReverseIndex = GetPreviousNode(*this, pReverseIndex);
    assert(pReverseIndex != nullptr);
    pIndex->m_pNext = new SNode();
    assert(pIndex != nullptr);
    pIndex = pIndex->GetNextNode();
    pIndex->m_sData = CopyData(pReverseIndex->GetData());
  }
  return reversedList;
}

void CList::CopyList(const CList& _rOther)
{
  m_pHead = new SNode();
  m_pIterator = m_pHead;
  m_uListSize = 1;
  m_pHead->m_sData = CopyData(_rOther.m_pHead->GetData());
  SNode* pIndex = m_pHead;
  SNode* pIndexOther = _rOther.m_pHead->GetNextNode();
  while (pIndexOther != nullptr)
  {
    pIndex->m_pNext = new SNode();
    assert(pIndex->GetNextNode() != nullptr);
    pIndex->m_pNext->m_sData = CopyData(pIndexOther->GetData());
    pIndex = pIndex->GetNextNode();
    pIndexOther = pIndexOther->GetNextNode();
    m_uListSize++;
  }
}

char* CList::CopyData(const char* _sData)
{
  assert(_sData != nullptr);
  char* copiedData = new char[strlen(_sData) + 1];
  strcpy(copiedData, _sData);
  return copiedData;
}

SNode* CList::GetPreviousNode(const CList& _list, const SNode* _pNode)
{
  SNode* pIndex = _list.m_pHead;
  while (pIndex->GetNextNode() != _pNode)
  {
    pIndex = pIndex->GetNextNode();
  }
  return pIndex;
}
