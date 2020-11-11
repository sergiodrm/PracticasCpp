#include "CNode.h"
#include <string>

CNode::CNode() :
  m_pNextNode(nullptr),
  m_sData(nullptr)
{
}

CNode::CNode(const char* _sData, CNode* _pNext) :
  m_pNextNode(_pNext)
{
  if (_sData)
  {
    unsigned int uStrSize = strlen(_sData) + 1;
    m_sData = new char[uStrSize];
    m_sData[uStrSize - 1] = '\0';
    strcpy(m_sData, _sData);
  }
  else m_sData = nullptr;
}

CNode::CNode(const CNode& _rOther)
{
  if (_rOther.m_sData)
  {
    unsigned int uStrSize = strlen(_rOther.m_sData) + 1;
    m_sData = new char[uStrSize];
    m_sData[uStrSize - 1] = '\0';
    strcpy(m_sData, _rOther.m_sData);
  }
  else m_sData = nullptr;
  // m_pNextNode = _rOther.m_pNextNode; // Esto haria que los dos nodos tuvieran el mismo nextnode
  if (_rOther.m_pNextNode)
  {
    m_pNextNode = new CNode(*(_rOther.m_pNextNode));
  }
  else m_pNextNode = nullptr;
}

CNode::CNode(CNode&& _rOther) noexcept
{
  m_sData = _rOther.m_sData;
  m_pNextNode = _rOther.m_pNextNode;
  _rOther.m_pNextNode = nullptr;
  _rOther.m_sData = nullptr;
}

CNode::~CNode()
{
  /*
  * Si se borra el puntero m_pNextNode, 
  * hace una reaccion en cadena que borra toda la lista.
  * ¿Util para el reset de la lista?
  */
  if (m_pNextNode) delete m_pNextNode;
  if (m_sData) delete m_sData;
}

const CNode& CNode::operator=(const CNode& _rOther)
{
  if (m_sData)
  {
    delete m_sData;
  }
  if (m_pNextNode)
  {
    delete m_pNextNode;
  }
  return *(new CNode(_rOther));
}

const CNode& CNode::operator=(CNode&& _rOther) noexcept
{
  if (m_sData)
  {
    delete m_sData;
  }
  if (m_pNextNode)
  {
    delete m_pNextNode;
  }
  m_sData = _rOther.m_sData;
  m_pNextNode = _rOther.m_pNextNode;
  _rOther.m_sData = nullptr;
  _rOther.m_pNextNode = nullptr;
  return *(this);
}

void CNode::FreeData()
{
  // Cuidado con los memory leaks! 
  // llamar al metodo cuando se hayan referenciado 
  // los punteros que se vayan a liberar
  m_sData = nullptr;
  m_pNextNode = nullptr;
}

CNode* CNode::GetNextNode() const
{
    return m_pNextNode;
}

const char* CNode::GetData() const
{
  return m_sData;
}

void CNode::SetNextNode(CNode* _pNode)
{
  m_pNextNode = _pNode;
}

void CNode::SetData(const char* _sData)
{
  if (m_sData)
  {
    delete m_sData;
  }
  m_sData = new char[strlen(_sData) + 1];
  strcpy(m_sData, _sData);
}
