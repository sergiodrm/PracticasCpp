#pragma once


namespace FileUtilities
{
  // Forward declaration.
  struct SFileID;
  typedef SFileID* const FID;

  /*
  * Funcion encargada de crear/abrir un fichero para su
  * lectura y/o escritura. Esta devolvera un tipo FID que
  * contendra el identificador del fichero abierto.
  * @param _sFileName: nombre del fichero
  * @param _sOpenMode: modo de apertura (los mismos que fopen)
  * @return variable tipo FID que identifica el fichero abierto
  */
  FID OpenFile(const char* _sFileName, const char* _sOpenMode);

  /*
  * Funcion que cierra el fichero identificado por _rFid. Tras cerrarlo,
  * se eliminara el contenido de este y se devolvera un codigo de estado,
  * 0 en caso de haberlo cerrado correctamente o un numero negativo en caso contrario.
  * @param _rFid: identificador del fichero que se desea cerrar.
  * @return entero con codigo de estado de la operacion.
  */
  int CloseFile(FID& _rFid);

  /*
  * Funcion para leer una cadena de caracteres desde un fichero identificado por
  * _rFid. La funcion devolvera el numero de caracteres leidos, que debera coincidir con _uNum.
  * Se colocaran los _uNum caracteres leidos en la cadena _sOutput_, por lo que esta debera
  * En caso contrario, es posible que se haya alcanzado el final del fichero o haya habido
  * un error de lectura.
  * @param _sOutput_: cadena de caracteres donde se guardaran los caracteres leidos del fichero.
  * Esta cadena debe tener reservada suficiente memoria para poder llevar a cabo esta accion.
  * @param _uNum: numero de caracteres que se desea leer. Tener en cuenta que el ultimo de ellos sera el caracter nulo \0.
  * @return numero de caracteres leidos. En caso de que sea menor que _uNum, se ha llegado al final del fichero.
  */
  int ReadFile(const FID& _rFid, char* _sOutput_, const unsigned int _uNum);

  /*
  * Funcion para escribir la cadena de caracteres _sString en el fichero identificado por _rFid.
  * Se escribiran _uNum caracteres de la cadena introducida.
  * @param _rFid: identificador del fichero.
  * @param _sString: cadena de caracteres que se desea escribir en el fichero.
  * @param _uNum: numero de caracteres que se desea escribir.
  * @return numero de caracteres escritos. En caso de que sea distinto que _uNum, se ha producido un error
  * en el proceso y no se ha podido llevar a cabo.
  */
  int WriteFile(const FID& _rFid, const char* _sString, const unsigned int _uNum);

  /*
  * Funcion para contar el numero de veces que aparece la cadena _sString
  * en el fichero identificado por _rFid.
  * @param _rFid: identificador del fichero.
  * @param _sString: cadena de caracteres que se desea contar en el fichero.
  * @return numero de veces que aparece la cadena en el fichero. Devolvera un numero
  * negativo si ha habido algun error en el proceso.
  */
  int CountStringInFile(const FID& _rFid, const char* _sString);

  /*
  * Funcion que devuelve la suma de los enteros separados por coma encontrados en
  * el fichero identificado por _rFid.
  * @param _rFid: identificador del fichero.
  * @param _cSeparator: caracter que separa los numeros que se desean sumar en el fichero.
  * @return: suma de los enteros encontrados.
  */
  int AddIntsInFile(const FID& _rFid, const char _cSeparator = ',');
}