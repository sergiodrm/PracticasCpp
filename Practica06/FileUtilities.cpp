
// FileUtilities.cpp
#define _CRT_SECURE_NO_WARNINGS 1
#include "FileUtilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

struct SFileID
{
  FILE* m_pFile;
};

FID OpenFile(const char* _sFileName, const char* _sOpenMode)
{
  FID pFid_ = new SFileID; // new (!)
  pFid_->m_pFile = fopen(_sFileName, _sOpenMode);
  if (pFid_->m_pFile)
  {
    return pFid_;
  }
  delete pFid_; // delete (!)
  return nullptr;
}

int CloseFile(FID& _rFid)
{
  int iStatus_ = fclose(_rFid->m_pFile);
  delete _rFid; // delete (!)
  return iStatus_;
}

int ReadFile(const FID& _rFid, char* _sOutput_, const unsigned int _uNum)
{
  // Comprobar el idenficador
  if (_rFid->m_pFile)
  {
    // Comprobar los parametros
    if (_uNum != 0 && _sOutput_)
    {
      return fread(_sOutput_, sizeof(char), _uNum, _rFid->m_pFile);
    }
  }
  return -1; // La lectura ha fallado por el identificador o por el modo de apertura.
}

int WriteFile(const FID& _rFid, const char* _sString, const unsigned int _uNum)
{
  // Comprobar el identificador y los parametros
  if (_rFid->m_pFile && _sString && _uNum != 0)
  {
    return fwrite(_sString, sizeof(char), _uNum, _rFid->m_pFile);
  }
  return -1;
}

int CountStringInFile(const FID& _rFid, const char* _sString)
{
  /* 
  Se ha chequeado que encuentre bien las coincidencias aunque se encuentren en
  lecturas del buffer distintas.
  */
  if (_sString)
  {
    unsigned int uNumApariciones_ = 0;
    char sBuffer[10];
    const unsigned int uSizeBuffer = sizeof(sBuffer) / sizeof(char);
    sBuffer[uSizeBuffer - 1] = '\0';
    int iCharRead;
    unsigned int uStrIndexChecking = 0;
    // Leer con la funcion ReadFile hasta que no se haya leido nada (EOF)
    do
    {
      iCharRead = ReadFile(_rFid, sBuffer, uSizeBuffer - 1);
      // Reiniciar los indices del buffer para leer desde el principio
      unsigned int uBufferStartIndexChecking = 0;
      unsigned int uBufferIndexChecking = 0;

      // Mientras que no se llegue hasta el numero de caracteres leidos o que no se haya encontrado
      // el caracter nulo al final del buffer, seguir chequeando los caracteres
      while (static_cast<int>(uBufferStartIndexChecking) < iCharRead && sBuffer[uBufferIndexChecking] != '\0')
      {
        // Si se llega al final del string, sumar a las apariciones y reiniciar indices
        if (_sString[uStrIndexChecking] == '\0')
        {
          uNumApariciones_++;
          uStrIndexChecking = 0;
          uBufferStartIndexChecking++;
          uBufferIndexChecking = uBufferStartIndexChecking;
        }
        // Si el caracter del buffer y el del string son iguales, aumentar los indices para seguir comparando
        else if (_sString[uStrIndexChecking] == sBuffer[uBufferIndexChecking])
        {
          uBufferIndexChecking++;
          uStrIndexChecking++;
        }
        // Si no coincide, reiniciar indices de buffer y string
        else {
          uStrIndexChecking = 0;
          uBufferStartIndexChecking++;
          uBufferIndexChecking = uBufferStartIndexChecking;
        }
      }
    } while (iCharRead != 0);
    return uNumApariciones_;
  }
  return -1;
}

int AddIntsInFile(const FID& _rFid, const char _cSeparator)
{
  int iSuma_ = 0;
  char sBuffer[10]; // Buffer de lectura de fichero
  const unsigned int uSizeBuffer = sizeof(sBuffer) / sizeof(char);
  sBuffer[uSizeBuffer - 1] = '\0';

  int iCharRead;
  int iNumberBuffer = 0; // Buffer numerico
  bool bNegativo = false;
  do
  {
    iCharRead = ReadFile(_rFid, sBuffer, uSizeBuffer - 1);
    unsigned int uBufferIndex = 0;
    while (static_cast<int>(uBufferIndex) < iCharRead && sBuffer[uBufferIndex] != '\0')
    {
      // Si el caracter leido coincide con el separador, sumar el numero almacenado en
      // el buffer numerico con el contador de la suma y reiniciar el buffer.
      if (sBuffer[uBufferIndex] == _cSeparator)
      {
        iSuma_ += iNumberBuffer;
        iNumberBuffer = 0;
        bNegativo = false;
      }
      // Si el caracter leido es un numero, se multiplica por 10 la cuenta llevada y se suma el nuevo numero
      else if (sBuffer[uBufferIndex] >= '0' && sBuffer[uBufferIndex] <= '9')
      {
        // Cada caracter leido que sea un digito se multiplicara por 10 para aumentar el orden de magnitud.
        iNumberBuffer *= 10;
        // Comprobar signo del numero que hemos leido hasta ahora!!!
        if (!bNegativo)
        {
          iNumberBuffer += sBuffer[uBufferIndex] - '0';
        }
        else iNumberBuffer -= (sBuffer[uBufferIndex] - '0');
      }
      else if (sBuffer[uBufferIndex] == '-' && !bNegativo)
      {
        bNegativo = true;
      } // else // Caracter no permitido!!! Warning y break?

      /* Los caracteres que se encuentren entre los numeros van a ser ignorados.
      Deberia ponerse un warning o algo por el estilo para avisar de que el fichero 
      contiene algo mas que numeros. Si se encuentra el simbolo - entre los numeros tambien se ignorara,
      pero si se encuentra despues de la coma y antes del primer numero se considerara numero negativo.
      */

      // Seguir leyendo el buffer
      uBufferIndex++;
    }
  } while (iCharRead != 0);
  
  // Siempre se va a quedar un numero almacenado en iNumberBuffer pendiente por sumar al terminar el fichero.
  iSuma_ += iNumberBuffer;
  return iSuma_;
}