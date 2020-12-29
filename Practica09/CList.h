#pragma once

/**
* Estructura nodo para guardar los datos de la lista
*/
struct SNode
{
  char* m_sData;
  SNode* m_pNext;

  explicit SNode() : m_sData(nullptr), m_pNext(nullptr) {}
  inline SNode* GetNextNode()   { return m_pNext; }
  inline const char* GetData()  { return m_sData; }
};

/**
* Clase lista
*/
class CList
{
public:

  explicit CList();
  /*explicit*/ CList(const CList& _rOther);     // Practica 11
  explicit CList(CList&& _rOther) noexcept;
  ~CList();

  CList& operator=(const CList& _rOther);
  CList& operator=(CList&& _rOther);

  unsigned int Size() const;
  int Push(const char* _sData);
  const char* First() const;
  const char* Next();
  const char* Pop();
  void Reset();

  // Practica 10
  void PrintList(const char* _sSeparator = ", ") const;

  // Practica 11
  
  CList GetReverseList(CList _lstSrc);
  /* 

  * Al diseñar asi la declaracion de la funcion ocurren varias cosas:
  *   - El parametro sera pasado por copia por lo que ocupara mas memoria de lo debido, ademas de la llamada adicional al constructor copia para el parametro.
  *   - Se hace otra llamada adicional al constructor copia al devolver el objeto que se crea dentro del metodo.
  *   - Al pasar el parametro por copia, se llama a su destructor al finalizar el metodo ya que la copia solo existe dentro del metodo.
  *   - Al pasar la lista que se desea invertir como parametro, no hace falta usar una instancia de la clase por lo que se puede hacer static.
  * 
  * 
  * Mejoras propuestas:
  CList GetReverseList() const; // Para hacer la inversa sobre la propia instancia desde la que se llama al metodo
  static CList GetReverseList(const CList&); // Pasar la lista como referencia constante y devolver una nueva
  static void GetReverseList(const CList&, CList&); // Para guardar la inversa sobre el segundo parametro pasado como referencia. Para ello el parametro de salida debe ser inicializado anteriormente.

  */
  // Implementacion final (practica 11)
  CList GetReverseList() const;

private:

  void CopyList(const CList& _rOther);
  static char* CopyData(const char* _sData);
  static SNode* GetPreviousNode(const CList& _list, const SNode* _pNode);

private:

  SNode* m_pHead;
  SNode* m_pIterator;
  unsigned int m_uListSize;
};

