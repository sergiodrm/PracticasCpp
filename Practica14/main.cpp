
#include <iostream>

class CBaseNoVirtual
{
public:

  CBaseNoVirtual() { printf("Creando CBaseNoVirtual\n"); }
  ~CBaseNoVirtual() { printf("Destruyendo CBaseNoVirtual\n"); }

  void PrintSize() { printf("Espacio de CBaseNoVirtual: %d bytes\n", sizeof(CBaseNoVirtual)); }

  int integer = 0;
};

class CBase
{
public:

  CBase() { 
    printf("Creando CBase\n");
    PrintSize();
  }
  virtual ~CBase() { printf("Destruyendo CBase\n"); }

  virtual void PrintSize() { printf("Espacio de CBase: %d bytes\n", sizeof(CBase)); }

  int integer = 0;
};

class CDerivedA : public CBase
{
public:
  CDerivedA() 
  { 
    printf("Creando CDerivedA\n");
    PrintSize();
  }
  virtual ~CDerivedA() { printf("Destruyendo CDerivedA\n"); }

  virtual void PrintSize() { printf("Espacio de CDerivedA: %d bytes\n", sizeof(CDerivedA)); }
};

class CDerivedB : public CBase
{
public:
  CDerivedB()
  { 
    printf("Creando CDerivedB\n"); 
    PrintSize();
  }
  virtual ~CDerivedB() { printf("Destruyendo CDerivedB\n"); }

  virtual void PrintSize() { printf("Espacio de CDerivedB: %d bytes\n", sizeof(CDerivedB)); }

};

int main()
{
  CDerivedA* pA = new CDerivedA();
  CDerivedB* pB = new CDerivedB();

  pA->PrintSize();
  pB->PrintSize();
  printf("%d bytes\n", sizeof(&(CBase::PrintSize)));
  // Se hace un reinterpret_cast a int** porque los punteros de funciones se mueven cada 4 bytes
  int** pVTableDerivedA = reinterpret_cast<int**>(pA);

  return 0;
}