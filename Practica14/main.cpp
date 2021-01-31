
#include <iostream>

class AVirtual
{
  int x;
public:
  AVirtual() : x(0) { foo(); }
  virtual ~AVirtual() {  }
  virtual void foo() { printf("virtual foo\n"); }
  virtual void foo2(){}
};

class ADerived : public AVirtual
{
public:
  ADerived() { foo(); }
  void foo() override { printf("virtual foo derived\n"); }
};

class A
{
  int x;
public:
  A() : x(0) {}
  ~A() {}
  void foo() { printf("foo\n"); }
};

int main()
{
  AVirtual* pAV = new AVirtual();
  A* pA = new A();
  ADerived* pAD = new ADerived();

  /**
   * El vptr es el primero en la zona de memoria de la instancia, por lo que
   * haciendo un cast a int** tendremos un puntero a vptr.
   */
  int** pVirtualTable = reinterpret_cast<int**>(pAV);
  /**
   * La vtable tendra una entrada por cada metodo virtual de la clase,
   * por lo que tendra 4 bytes * Numero de metodos virtuales.
   * La vtable se genera durante el tiempo de compilacion, por lo que su ubicacion
   * se encuentra en una zona de memoria estatica en el ejecutable.
   */
  printf("VTable direction: %08X\n", reinterpret_cast<int>(*pVirtualTable));
  /**
   * Diferencia de tamaños: al tener una clase un metodo virtual, automaticamente se genera la vtable
   * de la clase y su correspondiente vptr. Este ultimo es un puntero oculto dentro de la instancia de la clase base y
   * ocupa 4 bytes, por lo que la diferencia entre una clase virtual y no virtual será de 4 bytes.
   */
  printf("Clase no virtual: %d bytes\n", sizeof(*pA));
  printf("Clase virtual:    %d bytes\n", sizeof(*pAV));

  /**
   * Al llamar a un metodo virtual desde el constructor el compilador ya ha añadido la
   * tabla virtual de la clase por lo que se llamara a la version del metodo mas actualizada
   * en la tabla.
   */

  /**
   * La llamada a un metodo virtual de la clase consiste en mirar a traves del vptr la
   * direccion almacenada en la vtable de la version mas sobreescrita del metodo virtual.
   * Por el contrario, una llamada a un metodo no virtual unicamente es localizar la direccion
   * del metodo en memoria y ejecutarlo.
   * Se realiza un paso adicional, la busqueda del metodo a traves de la vtable.
   */
  pAV->foo();
  pAD->foo();
  pA->foo();

  delete pAV;
  delete pA;
  delete pAD;

  return 0;
}