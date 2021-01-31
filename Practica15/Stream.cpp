#include "Stream.h"
#include <cstdio>

CStream::CStream() : m_pStreamId(nullptr)
{
  printf("Creando stream base...\n");
}

CStream::~CStream()
{
  printf("Destruyendo stream base...\n");
}

void CStream::Open(const char* _sStreamName)
{
  printf("Abriendo stream base...\n");
}

void CStream::Read()
{
  printf("Leyendo stream base...\n");
}

void CStream::Write()
{
  printf("Escribiendo stream base...\n");
}

void CStream::Close()
{
  printf("Cerrando stream base...\n");
}
