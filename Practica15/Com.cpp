#include "Com.h"
#include <cstdio>

CCom::CCom() : Super()
{
  printf("Creando stream puerto serie...\n");
}

CCom::~CCom()
{
  printf("Destruyendo stream puerto serie...\n");
}

void CCom::Open(const char* _sStreamName)
{
  Super::Open(_sStreamName);
  printf("Abriendo stream puerto serie...\n");
}

void CCom::Read()
{
  Super::Read();
  printf("Leyendo stream puerto serie...\n");
}

void CCom::Write()
{
  Super::Write();
  printf("Escribiendo stream puerto serie...\n");
}

void CCom::Close()
{
  Super::Close();
  printf("Cerrando stream puerto serie...\n");
}
