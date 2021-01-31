
// FileUtilities.cpp

#include "FileUtilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Para la practica 10 ---
#include "../Practica09/CList.h"
#include "StringUtility.h"
// ---

typedef FileUtilities::FID FID;

struct FileUtilities::SFileID
{
  FILE* m_pFile;
};

FID FileUtilities::OpenFile(const char* _sFileName, const char* _sOpenMode)
{
  FID pFid_ = new FileUtilities::SFileID; // new (!)
  pFid_->m_pFile = fopen(_sFileName, _sOpenMode);
  if (pFid_->m_pFile)
  {
    return pFid_;
  }
  delete pFid_; // delete (!)
  return nullptr;
}

int FileUtilities::CloseFile(FID& _rFid)
{
  int iStatus_ = fclose(_rFid->m_pFile);
  delete _rFid; // delete (!)
  return iStatus_;
}

int FileUtilities::ReadFile(const FID& _rFid, char* _sOutput_, const unsigned int _uNum)
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

int FileUtilities::WriteFile(const FID& _rFid, const char* _sString, const unsigned int _uNum)
{
  // Comprobar el identificador y los parametros
  if (_rFid->m_pFile && _sString && _uNum != 0)
  {
    return fwrite(_sString, sizeof(char), _uNum, _rFid->m_pFile);
  }
  return -1;
}

int FileUtilities::CountStringInFile(const FID& _rFid, const char* _sString)
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
      iCharRead = FileUtilities::ReadFile(_rFid, sBuffer, uSizeBuffer - 1);
      // Reiniciar los indices del buffer para leer desde el principio
      /*unsigned */int uBufferStartIndexChecking = 0; // Para evitar el warning entre int y unsigned int
      unsigned int uBufferIndexChecking = 0;

      // Mientras que no se llegue hasta el numero de caracteres leidos o que no se haya encontrado
      // el caracter nulo al final del buffer, seguir chequeando los caracteres
      while (uBufferStartIndexChecking < iCharRead && sBuffer[uBufferIndexChecking] != '\0')
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

int FileUtilities::AddIntsInFile(const FID& _rFid, const char _cSeparator)
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
    iCharRead = FileUtilities::ReadFile(_rFid, sBuffer, uSizeBuffer - 1);
    /*unsigned*/ int uBufferIndex = 0; // No puedo comparar el unsigned int con un int, salta warning
    while (uBufferIndex < iCharRead && sBuffer[uBufferIndex] != '\0')
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


// PRACTICA 10 ------------------------------------------------------------------------------------------

int FileUtilities::GetListFromFile(const FID& _rFid, CList& rDataList_)
{
  int iListSize_ = 0;

  // Crear un buffer para la lectura de datos
  const unsigned int uSizeBuffer = 3;
  char* sBuffer = new char[uSizeBuffer + 1];
  sBuffer[uSizeBuffer] = '\0';

  // Crear un buffer del buffer para cuando un numero se quede colgado entre lecturas
  char* sHalfNumber = nullptr;

  int iCharRead = FileUtilities::ReadFile(_rFid, sBuffer, uSizeBuffer);
  sBuffer[iCharRead] = '\0';

  /*
  * Bucle principal: hasta que no se encuentran caracteres que leer en el fichero. Lo leido
  * se guarda en el buffer y se leera con otro bucle while. Dentro de este se evaluara caracter
  * a caracter hasta encontrar: una coma o un caracter terminador (\0). 
  * En el primer caso se comprueba que no exista ningun numero pendiente de la lectura anterior (en la variable sHalfNumber). De ser asi
  * se concatenaria el sHalfNumber con el buffer hasta la coma encontrada y se guarda en la lista. Si no existe numero pendiente
  * se hace una copia y se guarda en la lista.
  * En el segundo caso se comprueba que no se haya quedado ningun numero colgado en el buffer. De ser asi se guarda en la variable sHalfNumber
  * junto con los numeros pendientes de antiguas iteraciones (si los hubiera).
  */
  while (iCharRead > 0)
  {
    int uIndex = 0;
    int uNumberBeginning = 0;
    while (uIndex <= iCharRead)
    {
      // Si el elemento se corresponde con un separador...
      if (sBuffer[uIndex] == ',')
      {
        // Comprobar si hay algun numero colgado de la lectura anterior
        char* sData = nullptr;
        if (sHalfNumber)
        {
          sData = ConcatenateString(sHalfNumber, sBuffer, uIndex);
          // Ya se ha completado el numero pendiente, liberar la memoria de sHalfNumber
          delete[] sHalfNumber;
          sHalfNumber = nullptr;
        }
        else
        {
          // Crear una nueva cadena y meterla en la lista
          sData = new char[uIndex - uNumberBeginning + 1]; // Memoria del heap gestionada en la lista
          sData[uIndex - uNumberBeginning] = '\0';
          CopyString(sData, sBuffer + uNumberBeginning, uIndex - uNumberBeginning);
        }
        rDataList_.Push(sData); // Metido en la lista, una vez que esta se borre hara el delete de los datos (no se quedaran memory leaks)
        ++iListSize_;

        // El siguiente numero al separador sera el principio de la siguiente cadena
        uNumberBeginning = uIndex + 1;
      }
      // Si el elemento se corresponde con el fin del buffer
      else if (sBuffer[uIndex] == '\0')
      {
        // Hemos llegado al final del buffer, hay que comprobar si se ha quedado algun numero pendiente.
        // El unico caso de que no se quede un numero colgado es que el caracter anterior sea un separador
        if (sBuffer[uIndex - 1] != ',')
        {
          // Aqui puede pasar que al terminar de leer el buffer y dejar un numero colgado, puede ocurrir que se haya quedado otro numero pendiente de la lectura anterior
          if (!sHalfNumber) // Comprobar que no haya ningun numero pendiente
          {
            sHalfNumber = new char[uIndex - uNumberBeginning + 1];
            sHalfNumber[uIndex - uNumberBeginning] = '\0';
            CopyString(sHalfNumber, sBuffer + uNumberBeginning, uIndex - uNumberBeginning);
            // Ya esta guardada la cadena para la siguiente lectura.
          }
          else // En caso de que haya otro numero, se concatena para no perder ninguno de los dos
          {
            char* sNewHalfNumber = ConcatenateString(sHalfNumber, sBuffer);
            // Se borra el numero pendiente anterior, ya que se encuentra incluido en el nuevo numero pendiente
            delete[] sHalfNumber;
            sHalfNumber = sNewHalfNumber;
            // Ya se tiene guardada la referencia al nuevo numero pendiente. Al salir del scope se borrara sNewHalfNumber
            // pero la memoria del heap a la que apunta seguira guardada en sHalfNumber.
          }
        }
      }
      ++uIndex;
    }

    // Volver a leer el archivo
    iCharRead = FileUtilities::ReadFile(_rFid, sBuffer, uSizeBuffer);
    sBuffer[iCharRead] = '\0';
  }

  // Se comprueba que no se haya quedado ningun numero pendiente
  if (sHalfNumber)
  {
    rDataList_.Push(sHalfNumber);
    // No borrar en este caso sHalfNumber, ya que esta direccion esta guardada como dato en la lista
    sHalfNumber = nullptr;
  }

  // Borrar el buffer
  delete[] sBuffer;
  
  return iListSize_;
}