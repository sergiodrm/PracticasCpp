#pragma once

class CNode;

class CList
{
public:

  explicit CList();
  /*explicit*/ CList(const CList& _rOther);     // Practica 11
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

  // Practica 11
  /* 
  
  CList GetReverseList(CList _lstSrc);

  * Al diseñar asi la declaracion de la funcion ocurren varias cosas:
  *   - El parametro sera pasado por copia por lo que ocupara mas memoria de lo debido ademas de la llamada al constructor copia de la clase que conlleva
  *   - Se hace otra llamada adicional al constructor copia al devolver el objeto que se modifique dentro del metodo.
  *   - Al pasar la lista que se desea invertir como parametro, no hace falta usar una instancia de la clase por lo que se puede hacer static.
  * Mejoras propuestas:
  
  CList GetReverseList(); // Para hacer la inversa sobre la propia instancia desde la que se llama al metodo
  static void GetReverseList(CList&); // Para hacer la inversa sobre la instancia pasada como referencia en el argumento
  static void GetReverseList(const CList&, CList&); // Para guardar la inversa sobre el segundo parametro pasado como referencia

  */

private:

  void CopyList(const CList& _rOther);

  CNode* m_pHead;
  CNode* m_pIterator;
  unsigned int m_uListSize;
};

