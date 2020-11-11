
#include <iostream>
#include "FileUtilities.h"

int main()
{

  /* *** Abrir, escribir y cerrar *** */

  FID myFidWrite = OpenFile("prueba.txt", "w");

  if (myFidWrite) // El fichero se ha podido abrir
  {
    const char* sStringToWrite = "Hola que tal, esto es un\ndocumento de prueba para ver que tal funcionan las funciones \n de la practica.";
    const unsigned int uSizeString = strlen(sStringToWrite);

    int iAmountWritten = WriteFile(myFidWrite, sStringToWrite, uSizeString);

    printf("Cadena escrita: \"%s\"\n", sStringToWrite);
    printf("Dimension de la cadena: %d\n", uSizeString);
    printf("Caracteres escritos: %d\n", iAmountWritten);
    if (CloseFile(myFidWrite) == 0)
    {
      printf("Fichero cerrado correctamente.\n");
    } else printf("Fichero no se ha podido cerrar correctamente.\n");
  }

  printf("\n\n");

  /* *** Abrir, leer y cerrar *** */

  FID myFidRead = OpenFile("prueba.txt", "r");

  if (myFidRead) // El fichero se ha podido abrir
  {
    char sStringRead[30];
    sStringRead[29] = '\0';
    const unsigned int uAmountToRead = 29;

    int uAmountRead = ReadFile(myFidRead, sStringRead, uAmountToRead);
    printf("Numero de caracteres para leer: %d\n", uAmountToRead);
    printf("Cadena leida: \"%s\"\n", sStringRead);
    printf("Caracteres leidos: %d\n", uAmountRead);

    
    if (CloseFile(myFidRead) == 0)
    {
      printf("Fichero cerrado correctamente.\n");
    }
    else printf("Fichero no se ha podido cerrar correctamente.\n");
  }


  printf("\n\n\n");
  return 0;
}
