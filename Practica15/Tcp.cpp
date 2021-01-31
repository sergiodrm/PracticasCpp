#include "Tcp.h"

#include <cstdio>

CTcp::CTcp() : Super()
{
  printf("Creando stream TCP...\n");
}

CTcp::~CTcp()
{
  printf("Destruyendo stream TCP...\n");
}

void CTcp::Open(const char* _sStreamName)
{
  Super::Open(_sStreamName);
  printf("Abriendo stream TCP...\n");
}

void CTcp::Read()
{
  Super::Read();
  printf("Leyendo stream TCP...\n");
}

void CTcp::Write()
{
  Super::Write();
  printf("Escribiendo stream TCP...\n");
}

void CTcp::Close()
{
  Super::Close();
  printf("Cerrando stream TCP...\n");
}
