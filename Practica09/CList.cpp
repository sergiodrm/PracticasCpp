#include "CList.h"
#include "CNode.h"
#include <string>


CList::CList() :
  m_pHead(nullptr),
  m_pIterator(nullptr),
  m_uListSize(0)
{
}

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

const CList& CList::operator=(const CList& _rOther)
{
  Reset();
  CopyList(_rOther);
  return *this;
}

const CList& CList::operator=(CList&& _rOther)
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
  if (_sData)
  {
    if (m_pHead)
    {
      // Crear un ptr para recorrer la lista y no tener que modificar la posicion de m_pIterator
      CNode* pIt = m_pHead;
      // Buscar el ultimo elemento de la lista actual
      while (pIt->GetNextNode() != nullptr)
      {
        pIt = pIt->GetNextNode();
      }
      // Cambiar la referencia del siguiente nodo al elemento creado
      pIt->SetNextNode(new CNode(_sData, nullptr));
    }
    else
    {
      m_pHead = new CNode(_sData, nullptr);
      m_pIterator = m_pHead;
    }
    return ++m_uListSize;
  }
  else return -1;
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
  // Comprobar que los punteros no son nullptr
  if (m_pHead && m_pIterator)
  {
    // Guardar el siguiente nodo del head para referenciarlo luego
    CNode* pNextHead = m_pHead->GetNextNode();
    if (m_pHead == m_pIterator)
    {
      m_pIterator = pNextHead;
    }

    // Por como se ha diseñado CNode, se pueden referenciar los punteros del dato
    // y hacer un FreeData para que cuando se haga un delete no borrar toda la lista.
    const char* sOutput_ = m_pHead->GetData();
    m_pHead->FreeData();

    // Ahora es seguro hacer un delete sin borrar ni el dato ni los siguientes nodos
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
  /*
  * Tal como se ha diseñado CNode, al hacer un delete de
  * m_pHead, se hara un delete de todos los nodos enlazados.
  */
  if (m_pHead) delete m_pHead;
  m_pHead = nullptr;
  m_pIterator = nullptr;
  m_uListSize = 0;
}

void CList::PrintList(const char* _sSeparator) const
{
  if (_sSeparator)
  {
    CNode* pIndexNode = m_pHead;
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
//  // TODO: Tabla de direcciones de nodo para hacer las redirecciones.
//  // En la tabla se guardan todas las direcciones y se modifican desde ahi.
//  const unsigned int uListSize = _lstSrc.Size();
//  CNode** tListNodes = new CNode*[uListSize];
//  unsigned int uIndex = 0;
//  // Bucle para almacenar las direcciones de los nodos de la lista en la tabla de nodos
//  while (_lstSrc.m_pIterator != nullptr)
//  {
//    tListNodes[uIndex] = _lstSrc.m_pIterator;
//    _lstSrc.m_pIterator = _lstSrc.m_pIterator->GetNextNode();
//    ++uIndex;
//  }
//
//  // Bucle para redireccionar los enlaces entre los nodos
//  for (uIndex = 0; uIndex < uListSize; ++uIndex)
//  {
//    CNode* pNextNode = uIndex == 0 ? nullptr : tListNodes[uIndex - 1];
//    tListNodes[uIndex]->SetNextNode(pNextNode);
//  }
//
//  // Redireccionar la cabeza de la lista
//  _lstSrc.m_pHead = tListNodes[uListSize - 1];
//  _lstSrc.m_pIterator = _lstSrc.m_pHead;
//
//  delete[] tListNodes; // Eliminar la tabla de direcciones creada en el heap
//
//  return _lstSrc;
//}

void CList::CopyList(const CList& _rOther)
{
  /* Hacer una copia de cada uno de los nodos de la lista pasada por parametro */
  m_pHead = new CNode(*(_rOther.m_pHead));
  m_pIterator = m_pHead;
  m_uListSize = _rOther.m_uListSize;
}
