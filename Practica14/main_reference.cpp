// ConsoleApplication5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

int mainReference()
{
	CB* pB = new CB();
	CB* pB2 = new CB();
	CA* pA = new CA();

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

	delete pB;
	return 0;
}

