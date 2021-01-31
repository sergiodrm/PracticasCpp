// Practica 15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class CStream {
public:
	CStream() { printf("Creando CStream\n"); }
	virtual ~CStream() { printf("Destruyendo CStream\n"); }

	void Initialize() { Open(); }
	virtual void Open() { printf("Abriendo fichero en CStream\n"); }
	virtual void Close() { printf("Cerrando fichero en CStream\n"); }
	virtual void Read() { printf("Leyendo fichero en CStream\n"); }
	virtual void Write() { printf("Escribiendo fichero en CStream\n"); }
};

class CFile : public CStream
{
public:
	CFile() { printf("Creando CFile\n"); }
	virtual ~CFile() { printf("Destruyendo CFile\n"); }

	virtual void Open() override { printf("Abriendo fichero en CFile\n"); }
	virtual void Close() override { printf("Cerrando fichero en CFile\n"); }
	virtual void Read() override { printf("Leyendo fichero en CFile\n"); }
	virtual void Write() override { printf("Escribiendo fichero en CFile\n"); }
};

class CTcp : public CStream
{
public:
	CTcp() { printf("Creando CTcp\n"); }
	virtual ~CTcp() { printf("Destruyendo CTcp\n"); }

	virtual void Open() override { printf("Abriendo fichero en CTcp\n"); }
	virtual void Close() override { printf("Cerrando fichero en CTcp\n"); }
	virtual void Read() override { printf("Leyendo fichero en CTcp\n"); }
	virtual void Write() override { printf("Escribiendo fichero en CTcp\n"); }
};

class CCom : public CStream
{
public:
	CCom() { printf("Creando CFile\n"); }
	virtual ~CCom() { printf("Destruyendo CFile\n"); }

	virtual void Open() override { printf("Abriendo fichero en CCom\n"); }
	virtual void Close() override { printf("Cerrando fichero en CCom\n"); }
	virtual void Read() override { printf("Leyendo fichero en CCom\n"); }
	virtual void Write() override { printf("Escribiendo fichero en CCom\n"); }
};

int main()
{
	CStream* pS = new CStream();
	CFile* pSF = new CFile();
	CTcp* pST = new CTcp();
	CCom* pSC = new CCom();

	int** pVirtualTable = reinterpret_cast<int**>(pS);
	printf("La direccion de la vtable es %08X\n", reinterpret_cast<int>(*pVirtualTable));

	int** pVirtualTableA = reinterpret_cast<int**>(pSF);
	printf("La direccion de la vtable es %08X\n", reinterpret_cast<int>(*pVirtualTableA));

	printf("sizeof CStream = %d\n", sizeof(CStream));
	printf("sizeof CFile = %d\n", sizeof(CFile));

	pS->~CStream();
	pSF->~CFile();
	pST->~CTcp();
	pSC->~CCom();
}

