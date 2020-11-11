
#include <iostream>
#include "TFile.h"


int main()
{
  printf("\n--- PRACTICA 8 ---\n\n");

  const char* sFilename = "Prueba.txt";

  // Prueba de escritura
  {
    FileUtilities::TFile oMyFile;
    oMyFile = FileUtilities::TFile(sFilename, FileUtilities::EFilesModes::Write);
    oMyFile.OpenFile();
    if (oMyFile.GetErrorFlag() == FileUtilities::EFilesErrors::Success)
    {
      printf("Fichero \"%s\" abierto correctamente.\n", oMyFile.GetFilename());
      const char* sTextToWrite = "Hola esto es una prueba a ver que tal funciona la practica 8\n Hasta luego!";
      oMyFile.WriteFile(sTextToWrite, strlen(sTextToWrite));
      if (oMyFile.GetErrorFlag() == FileUtilities::EFilesErrors::Success)
        printf("Se ha escrito correctamente en el fichero.\n");
      oMyFile.CloseFile();
    }
    else FileUtilities::PrintFileError(oMyFile.GetErrorFlag());
  }

  // Prueba de lectura
  {
    FileUtilities::TFile oMyReadFile(sFilename, FileUtilities::EFilesModes::Read);
    oMyReadFile.OpenFile();
    if (oMyReadFile.GetErrorFlag() == FileUtilities::EFilesErrors::Success)
    {
      printf("Fichero \"%s\" abierto correctamente.\n", oMyReadFile.GetFilename());

      const unsigned int uSize = 50;
      char* sTextRead = new char[uSize + 1];
      sTextRead[uSize] = '\0';
      int iTextRead = oMyReadFile.ReadFile(sTextRead, uSize-10);
      sTextRead[iTextRead] = '\0';
      if (oMyReadFile.GetErrorFlag() == FileUtilities::EFilesErrors::Success)
      {
        printf("Lectura correcta!\nTexto leido: \"%s\".\n", sTextRead);
      }
      else FileUtilities::PrintFileError(oMyReadFile.GetErrorFlag());
      oMyReadFile.CloseFile();
    }
    else FileUtilities::PrintFileError(oMyReadFile.GetErrorFlag());
  }
  return 0;
}