
#include <iostream>
#include "FileUtilities.h"
#include "CList.h"


/* La funcion para sacar los numeros del fichero de texto esta en el proyecto de la practica 7
* y para imprimir la lista se ha hecho un metodo en la propia clase.
*/

int main()
{
  const char* sFilename = "Prueba.txt";


  printf("--- PRACTICA 10 ---");
  printf("\n\n\n\n");

  FileUtilities::FID pFileID = FileUtilities::OpenFile(sFilename, "r");
  if (!pFileID)
  {
    printf("Fallo al abrir el fichero \"%s\"\n", sFilename);
    return -1;
  }

  printf("Fichero \"%s\" abierto con exito!\n", sFilename);

  CList oMiLista;
  FileUtilities::GetListFromFile(pFileID, oMiLista);

  printf("Lista leida: ");
  oMiLista.PrintList();

  printf("\n\n\n");
  return 0;
}

