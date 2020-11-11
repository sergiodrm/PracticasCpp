
#include <iostream>

int main()
{

  /* Ejercicio 1: Dado un entero obtener por separado cada uno de los bytes que lo forman,
   * usar un casting y aritmetica de punteros.
   */
  // Imprimir hexadecimal con printf -> "%02hhX\n"

  printf("- Ejercicio 1: obtener los bytes de un numero entero.\n");

  int iValue = 8; // Valor de prueba
  int* pValue = &iValue;
  printf("Numero entero: %d\n", iValue);

  // Hacer un reinterpret_cast<char*> para poder movernos byte a byte con punteros
  char* pCharValue = reinterpret_cast<char*>(pValue);
  for (unsigned int uIndex = 0; uIndex < sizeof(iValue); uIndex++)
  {
    printf("Byte %d contiene: 0x%02hhX\n", uIndex, *(pCharValue + uIndex));
  }
  printf("\n");
  // Fin ejercicio 1



  /* Ejercicio 2: dada la siguiente tabla de enteros, 
   * obtener el entero mayor usando aritmetica de punteros
   */
  printf("- Ejercicio 2: dada una tabla de numeros enteros, devolver el mayor usando punteros.\n");
  int tabla[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 2 };
  unsigned int uSizeTabla = sizeof(tabla) / sizeof(int);

  int iMaxValue(INT32_MIN); // Donde se guardara el valor maximo encontrado
  printf("Tabla: ");
  for (unsigned int uIndex = 0; uIndex < uSizeTabla; uIndex++)
  {
    printf("%d ", *(tabla + uIndex));
    if (*(tabla + uIndex) > iMaxValue)
      iMaxValue = *(tabla + uIndex);
  }
  printf("\nMaximo de la tabla: %d\n\n", iMaxValue);

  // Fin ejercicio 2



  /* Ejercicio 3: dada la tabla del ejercicio anterior,
   * obtener el byte de mayor valor.
   */
  // Se usa la misma tabla
  printf("- Ejercicio 3: de la tabla anterior, devolver el mayor byte usando punteros.\n");
  char* pCharTabla = reinterpret_cast<char*>(tabla);

  // Para hacer el bucle, el tamanio de la tabla sera el antiguo tamanio por lo que ocupa un int (4 byte)
  // De esta manera, con el puntero char se puede avanzar byte a byte hasta el final de la tabla.
  unsigned int uSizeCharTabla = uSizeTabla * sizeof(int);
  char cMaxCharValue = *pCharTabla;
  for (unsigned int uIndex = 1; uIndex < uSizeCharTabla; uIndex++)
  {
    if (*(pCharTabla + uIndex) > cMaxCharValue)
      cMaxCharValue = *(pCharTabla + uIndex);
  }

  printf("Valor del mayor byte encontrado en la tabla: 0x%02hhX.\n\n", cMaxCharValue);

  /* { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 2 }
   * 1 -> 00000000 00000000 00000000 00000001
   * 3 -> 00000000 00000000 00000000 00000011
   * 2 -> 00000000 00000000 00000000 00000010
   * 5 -> 00000000 00000000 00000000 00000101 -> este ultimo byte es el mayor
   * F -> 11111111 11111111 11111111 11111111
   */

  // Fin ejercicio 3



  /* Ejercicio 4: Darle la vuelta a una cadena de caracteres */
  printf("- Ejercicio 4: darle la vuelta a una cadena de caracteres.\n");
  char sCadena[] = "Hola";
  char* pBegin = sCadena;
  char* pEnd = sCadena + strlen(sCadena) - 1; // Apuntando al ultimo caracter distinto de '\0'
  char cLetraAux; // Variable auxiliar para el intercambio de caracteres dentro de la tabla

  printf("Cadena original: %s\n", sCadena);
  // Mientras que la direccion almacenada en pBegin sea menor que la almacenada en pEnd, 
  // seguir dandole la vuelta
  while (pBegin < pEnd)
  {
    cLetraAux = *pBegin;
    *pBegin = *pEnd;
    *pEnd = cLetraAux;
    pBegin++;
    pEnd--;
  }
  printf("Cadena dada la vuelta: %s\n", sCadena);



  printf("\n\n\n");
  return 0;
}
