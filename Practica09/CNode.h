#pragma once


class CNode
{
public:

  CNode();
  explicit CNode(const char* _sData, CNode* _pNext = nullptr);
  explicit CNode(const CNode& _rOther);
  explicit CNode(CNode&& _rOther) noexcept;
  ~CNode();

  const CNode& operator=(const CNode& _rOther);
  const CNode& operator=(CNode&& _rOther) noexcept;

  void FreeData();

  CNode* GetNextNode() const;
  const char* GetData() const;

  void SetNextNode(CNode* _pNode);
  void SetData(const char* _sData);

private:
  CNode* m_pNextNode;
  char* m_sData;
};

