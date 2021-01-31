
#include <cstdio>

#include "Com.h"
#include "File.h"
#include "Stream.h"
#include "Tcp.h"


int main()
{
  {
    printf("STREAM ARCHIVOS:\n");
    CFile oFile;
    oFile.Open("Filename");
    oFile.Read();
    oFile.Write();
    oFile.Close();
  }
  {
    printf("\n\nSTREAM PUERTO COM:\n");
    CCom oCom;
    oCom.Open("COM name");
    oCom.Read();
    oCom.Write();
    oCom.Close();
  }
  {
    printf("\n\nSTREAM TCP:\n");
    CTcp oTcp;
    oTcp.Open("IP");
    oTcp.Read();
    oTcp.Write();
    oTcp.Close();
  }
  return 0;
}