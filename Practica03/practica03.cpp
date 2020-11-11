#include <iostream>


// *****************************************************************************************
// DECLARACION DE FUNCIONES
// *****************************************************************************************

/**
 * Funcion que devuelve la fila _uIndex de una tabla bidimensional de cadenas dada.
 * Si no se introduce _uIndex, se devolvera la primera cadena por defecto.
 * @param _tStrings: tabla bidimensional de cadenas.
 * @param _uSize: dimension de la tabla de cadenas.
 * @param _uIndex: fila de la tabla que se desea devolver.
 * @return cadena de la fila
*/
const char* GetString(const char** _tStrings, unsigned int _uSize, unsigned int _uIndex = 0);

/*
 * Funcion que devuelve la cadena de caracteres del indice _uIndex la tabla _tStrings de 
 * dimension _uSize invertida. Para ello dentro se hace un new para reservar memoria para la nueva
 * cadena invertida, por lo que posteriormente se debe hacer un delete de esta memoria cuando se
 * termine de usar.
 * @param _tStrings: tabla bidimensional de cadenas.
 * @param _uSize: dimension de la tabla de cadenas.
 * @param _uIndex: fila de la tabla que se desea devolver.
 * @return cadena de la fila _uIndex invertida.
*/
char* GetInvertedString(const char** _tStrings, unsigned int _uSize, unsigned int _uIndex = 0);




// *****************************************************************************************
// MAIN
// *****************************************************************************************
int main()
{
  const char* tStrings[3] = { "Hola", "que", "tal" };
  unsigned int uSizeTable = sizeof(tStrings) / sizeof(char*);
  
  // Prueba de la funcion GetString(...)
  for (unsigned int uIndex = 0; uIndex < uSizeTable; ++uIndex)
    printf("%s ", GetString(tStrings, uSizeTable, uIndex));

  char* sInvertedString = GetInvertedString(tStrings, uSizeTable, 1);
  printf("%s", sInvertedString);

  delete[] sInvertedString; // delete a la cadena de GetInvertedString

  printf("\n\n\n");
  return 0;
}



// *****************************************************************************************
// DEFINICION DE FUNCIONES
// *****************************************************************************************

const char* GetString(const char** _tStrings, unsigned int _uSize, unsigned int _uIndex)
{
  // Si _tStrings no apunta a nullptr, buscar la cadena del indice _uIndex si es menor que la dimension de la tabla
  if (_tStrings && _uIndex < _uSize)
  {
    const char* sString = *(_tStrings + _uIndex);
    // Si la cadena no es null, devolverla
    if (sString)
      return sString;
  }
  return nullptr;
}

char* GetInvertedString(const char** _tStrings, unsigned int _uSize, unsigned int _uIndex)
{
  if (_tStrings)
  {
    // Leer la cadena de la tabla
    const char* sString = GetString(_tStrings, _uSize, _uIndex);
    const unsigned int uSizeString = strlen(sString) + 1; // Hay que tener en cuenta el \0!!!


    /* Al hacer el new dentro de la funcion, se deja la responsabilidad al usuario de hacer el delete
     * cuando termine de usar la cadena (posible memory leak). Otra opcion seria recibir una cadena
     * con memoria ya reservada para hacer la inversion, pero para ello el usuario debe conocer de antemano
     * la dimension de la cadena para poder reservar suficiente memoria.
     */
    // Reservar memoria para el nuevo char* invertido
    char* sInvertedString_ = new char[uSizeString];
    // Poner el limite del string 
    *(sInvertedString_ + uSizeString - 1) = '\0';

    // Copiarla invertida
    unsigned int uInvertedIndex = uSizeString - 2;
    unsigned int uIndex = 0;
    while (*(sInvertedString_ + uIndex) != '\0')
    {
      *(sInvertedString_ + uIndex) = *(sString + uInvertedIndex);
      uInvertedIndex--;
      uIndex++;
    }
    
    return sInvertedString_;
  }

  // si algo falla, devolver nullptr
  return nullptr;
}
