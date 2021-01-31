// Practica 14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>

class CParentNoVirtual
{
public:
	CParentNoVirtual() { printf("Creando CParent\n"); }
	~CParentNoVirtual() { printf("Destruyendo CParent\n"); }

	void Initialize() { Prueba(); }
	void Prueba() { printf("Llamando a Prueba() en CParent\n"); }

	int i = 2;
};

class CParent
{
public:
	CParent() { printf("Creando CParent\n"); }
	virtual ~CParent() { printf("Destruyendo CParent\n"); }

	void Initialize() { Prueba(); }
	virtual void Prueba() { printf("Llamando a Prueba() en CParent\n"); }

	int i = 2;
};

class CA : public CParent
{
public:
	CA() { printf("Creando CA\n"); }
	virtual ~CA() { printf("Destruyendo CA\n"); Prueba(); }

	virtual void Prueba() override { printf("Llamando a Prueba() en CA\n"); }

	float f = 37.f;
};

class CB : public CA
{
public:
	CB() { printf("Creando CB\n"); }
	virtual ~CB() { printf("Destruyendo CB\n"); }

	virtual void Prueba() override { printf("Llamando a Prueba() en CB\n"); }

	int j = 967;
};

int main()
{
	CB* pB = new CB();
	CB* pB2 = new CB();
	CA* pA = new CA();
	CParentNoVirtual* pCNV = new CParentNoVirtual();

	// vpointer
	// CParent int
	// CA float
	// CB int

	int** pVirtualTable = reinterpret_cast<int**>(pB);
	printf("La direccion de la vtable es %08X\n", reinterpret_cast<int>(*pVirtualTable));

	//**pVirtualTable = 5;

	int** pVirtualTable2 = reinterpret_cast<int**>(pB2);
	printf("La direccion de la vtable es %08X\n", reinterpret_cast<int>(*pVirtualTable2));

	int** pVirtualTableA = reinterpret_cast<int**>(pA);
	printf("La direccion de la vtable es %08X\n", reinterpret_cast<int>(*pVirtualTableA));

	printf("sizeof CParent = %d\n", sizeof(CParent));
	printf("sizeof CParentNoVirtual = %d\n", sizeof(CParentNoVirtual));

	printf("Llamando a metodo virtual:\n");
	pB->Prueba();
	printf("Llamando a metodo no virtual:\n");
	pCNV->Prueba();

	delete pB;

	printf("\n\nPreguntas practica 14:");
	printf("\n\n- Cuanto espacio ocupa la tabla de funciones virtuales?");
	printf("\n8 Bytes (aplicando sizeof sobre CParent)\n");
	printf("\n- Donde esta situada la tabla de funciones virtuales?");
	printf("\n00C79BF0 segun la direccion de su puntero\n");
	printf("\n- Cuanto espacio ocupa adicionalmente un objeto por tener una tabla de funciones virtuales?");
	printf("\n4 Bytes (sizeof CParent - sizeof CParentNoVirtual)\n");
	printf("\n- Que pasa si llamo a un metodo virtual desde el constructor?");
	printf("\nSe considera peligroso. Cuando se llama dentro del constructor se comportará como un método no virtual.\n");
	printf("\n- Comparar la llamada a una funcion virtual con la llamada a una funcion no virtual.");
	printf("\n- Cuantos pasos adicionales tienen que realizarse para llamar a una funcion cuando esta es virtual?");
	printf("\nNo hay pasos adicionales debido a que redefinimos el método en la clase derivada.\n");
	printf("\n\n\n");


}

