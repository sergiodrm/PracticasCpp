
#include <iostream>
#include "FileUtilities.h"


int main()
{
  printf("--- PRACTICA 7 ---\n\n");
  /* Chequeo funcion de contar cadenas*/
  {
    printf("\n--- Funcion para contar las veces que aparece una cadena en un fichero ---\n\n");
    const char* sFileName = "prueba contar cadenas.txt";
    const char* sOpenMode = "r";
    FileUtilities::FID myFid = FileUtilities::OpenFile(sFileName, sOpenMode);

    if (myFid)
    {
      printf("Fichero abierto correctamente! (%s en modo %s)\n", sFileName, sOpenMode);

      // Cadena que se desea contar
      const char sStringToCount[] = "hola";
      
      unsigned int uApariciones = FileUtilities::CountStringInFile(myFid, sStringToCount);
      printf("Veces que aparece la cadena \"%s\": %d\n", sStringToCount, uApariciones);

      if (!FileUtilities::CloseFile(myFid))
      {
        printf("Fichero cerrado correctamente! (%s)\n", sFileName);
      }
      else printf("Fallo al cerrar el fichero... (%s)\n", sFileName);
    }
  }

  /* Chequeo funcion sumar ints desde fichero */
  {
    printf("\n--- Funcion para sumar los ints separados por comas encontrados en un fichero ---\n\n");
    const char* sFileName = "prueba sumar ints desde fichero.txt";
    const char* sOpenMode = "r";
    FileUtilities::FID myFid = FileUtilities::OpenFile(sFileName, sOpenMode);
    if (myFid)
    {
      printf("Fichero abierto correctamente! (%s en modo %s)\n", sFileName, sOpenMode);
      int iSuma = FileUtilities::AddIntsInFile(myFid);
      printf("Resultado de la suma: %d\n", iSuma);
      if (!FileUtilities::CloseFile(myFid))
      {
        printf("Fichero cerrado correctamente!\n");
      }
      else printf("Fallo al cerrar el fichero...\n");
    }
  }
  printf("\n\n\n");
  return 0;
}