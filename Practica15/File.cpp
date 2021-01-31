#include "File.h"
#include <cstdio>


CFile::CFile() : Super()
{
  printf("Creando stream archivo...\n");
}

CFile::~CFile()
{
  printf("Destruyendo stream archivo...\n");
}

void CFile::Open(const char* _sStreamName)
{
  Super::Open(_sStreamName);
  printf("Abriendo stream archivo...\n");
}

void CFile::Read()
{
  Super::Read();
  printf("Leyendo stream archivo...\n");
}

void CFile::Write()
{
  Super::Write();
  printf("Escribiendo stream archivo...\n");
}

void CFile::Close()
{
  Super::Close();
  printf("Cerrando stream archivo...\n");
}
