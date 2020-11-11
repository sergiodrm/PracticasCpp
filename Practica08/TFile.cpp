#include "TFile.h"
#include <stdio.h>
#include <string>

typedef FileUtilities::EFilesModes FMode;
typedef FileUtilities::EFilesErrors FError;

// ************************************************************************
// DEFINICION DE FUNCIONES PARA LOS ENUM
// ************************************************************************

#define PRINT_CASE_ERROR(_VALUE, _MESSAGE)  \
case _VALUE:                                \
printf(_MESSAGE);                           \
break


const char* FileUtilities::GetModeAsStr(FMode _eMode)
{
  switch (_eMode)
  {
  case FMode::Read:
    return "r";
  case FMode::Write:
    return "w";
  case FMode::ReadWrite:
    return "a";
  default:
    return nullptr;
  }
}

FMode FileUtilities::GetStrAsMode(const char* _sMode)
{
  FMode eMode_ = FMode::Invalid;
  if (strcmp(_sMode, "r"))
  {
    eMode_ = FMode::Read;
  }
  else if (strcmp(_sMode, "w"))
  {
    eMode_ = FMode::Write;
  }
  else if (strcmp(_sMode, "a"))
  {
    eMode_ = FMode::ReadWrite;
  }
  return eMode_;
}

void FileUtilities::PrintFileError(FError _eError)
{
  switch (_eError)
  {
    PRINT_CASE_ERROR(FError::Invalid, "Sin errores.\n");
    PRINT_CASE_ERROR(FError::Success, "El proceso se completo satisfactoriamente.\n");
    PRINT_CASE_ERROR(FError::OpenModeNotValid, "El modo de apertura no es valido para el proceso que se desea realizar.\n");
    PRINT_CASE_ERROR(FError::FileAlreadyOpen, "El fichero esta actualmente abierto.\n");
    PRINT_CASE_ERROR(FError::FileNotOpen, "Aun no se ha abierto el fichero, no se puede operar sobre el.\n");
    PRINT_CASE_ERROR(FError::InputNotValid, "Los paramentros introducidos a la funcion no son validos.\n");
    PRINT_CASE_ERROR(FError::CodeEOF, "Se ha alcanzado el final del fichero [EOF].\n");
    PRINT_CASE_ERROR(FError::OpenError, "El fichero no se ha podido abrir, comprobar que existe el fichero o que se puede crear en el directorio especificado.\n");
    PRINT_CASE_ERROR(FError::CloseError, "No se ha podido cerrar el fichero.\n");
    PRINT_CASE_ERROR(FError::WriteError, "No se ha podido escribir sobre el fichero.\n");
  }
}


// ************************************************************************
// DEFINICION DE METODOS DE TFILE
// ************************************************************************

/* --- Constructores y destructor --- */

FileUtilities::TFile::TFile() : 
  m_pFid(nullptr), 
  m_eOpenMode(FMode::Invalid),
  m_sFileName(nullptr),
  m_bEOF(false),
  m_eErrorFlag(FError::Invalid)
{
}

FileUtilities::TFile::TFile(const char* _sFileName, FMode _eOpenMode)
{
  if (_sFileName)
  {
    m_sFileName = new char[strlen(_sFileName) + 1];
    strcpy(m_sFileName, _sFileName);
  }
  else m_sFileName = nullptr;
  m_eOpenMode = _eOpenMode == FMode::Count ? FMode::Invalid : _eOpenMode;
  m_pFid = nullptr;
  m_bEOF = false;
  m_eErrorFlag = FError::Invalid;
}

FileUtilities::TFile::TFile(const TFile& _oTFile) noexcept
{
  if (_oTFile.m_sFileName)
  {
    m_sFileName = new char[strlen(_oTFile.m_sFileName) + 1];
    strcpy(m_sFileName, _oTFile.m_sFileName);
  }
  else m_sFileName = nullptr;

  m_eOpenMode = _oTFile.m_eOpenMode == FMode::Count ? FMode::Invalid : _oTFile.m_eOpenMode;

  if (_oTFile.m_pFid)
  {
    OpenFile();
    m_eErrorFlag = FError::Success;
  }
  else
  {
    m_pFid = nullptr;
    m_eErrorFlag = FError::OpenError;
  }
  m_bEOF = false;
}

FileUtilities::TFile::TFile(TFile&& _oTFile) noexcept
{
  m_pFid = _oTFile.m_pFid;
  _oTFile.m_pFid = nullptr;
  m_sFileName = _oTFile.m_sFileName;
  _oTFile.m_sFileName = nullptr;
  m_eOpenMode = _oTFile.m_eOpenMode == FMode::Count ? FMode::Invalid : _oTFile.m_eOpenMode;
  m_bEOF = _oTFile.m_bEOF;
  m_eErrorFlag = _oTFile.m_eErrorFlag;
}

FileUtilities::TFile::~TFile()
{
  if (m_pFid)
  {
    CloseFile();
  }
  if (m_sFileName)
  {
    delete m_sFileName;
  }
}

/* --- Metodos de utilidad --- */

void FileUtilities::TFile::OpenFile()
{
  if (!m_pFid)
  {
    const char* sOpenMode = GetModeAsStr(m_eOpenMode);
    if (m_sFileName && sOpenMode)
    {
      m_pFid = fopen(m_sFileName, sOpenMode);
      if (m_pFid)
      {
        m_eErrorFlag = FError::Success;
      }
      else m_eErrorFlag = FError::OpenError;
    }
    else m_eErrorFlag = FError::OpenModeNotValid;
  } else m_eErrorFlag = FError::FileAlreadyOpen;
  
}

void FileUtilities::TFile::CloseFile()
{
  if (m_pFid)
  {
    int iCloseStatus = fclose(m_pFid);
    m_pFid = nullptr;
    m_eErrorFlag = iCloseStatus == 0 ? FError::Success : FError::CloseError;
  }
  else m_eErrorFlag = FError::FileNotOpen;
}

int FileUtilities::TFile::ReadFile(char* _sOutput_, unsigned int _uNum)
{
  // Inicializar variables
  int iCharRead_ = 0;
  m_eErrorFlag = FError::Success;

  // Comprobar que no se ha llegado ya al EOF
  if (!m_bEOF)
  {
    // Comprobar que el fichero esta abierto y que el buffer pasado por parametro no esta en nullptr.
    if (m_pFid && _sOutput_)
    {
      // Chequear el numero de caracteres que se desean leer
      if (_uNum != 0)
      {
        // Comprobar los permisos con los que se abrio el fichero
        if (m_eOpenMode == FMode::Read || m_eOpenMode == FMode::ReadWrite)
        {
          iCharRead_ = fread(_sOutput_, sizeof(char), _uNum, m_pFid);
          if (iCharRead_ == 0 && feof(m_pFid) != 0)
          {
            // Se ha llegado al final del fichero
            m_bEOF = true;
          }
        }
        else
        {
          // Los permisos no son validos para leer el fichero
          m_eErrorFlag = FError::OpenModeNotValid;
        }
      }
    }
    else
    {
      // EL fichero no esta abierto o la entrada no es valida (string = nullptr)
      m_eErrorFlag = m_pFid ? FError::InputNotValid : FError::FileNotOpen;
    }
  }
  else
  {
    // Si ya se habia llegado al EOF, marcarlo en la errorflag
    m_eErrorFlag = FError::CodeEOF;
  }

  return m_eErrorFlag == FError::Success ? iCharRead_ : -1;
}

int FileUtilities::TFile::WriteFile(const char* _sString, unsigned int _uNum)
{
  int iCharWritten_ = 0;
  m_eErrorFlag = FError::Success;

  // Comprobar que el fichero esta abierto y que la cadena pasada por parametro no esta en nullptr.
  if (m_pFid && _sString)
  {
    // Chequear el numero de caracteres que se desean leer
    if (_uNum != 0)
    {
      // Comprobar los permisos con los que se abrio el fichero
      if (m_eOpenMode == FMode::Write || m_eOpenMode == FMode::ReadWrite)
      {
        iCharWritten_ = fwrite(_sString, sizeof(char), _uNum, m_pFid);
      }
      else
      {
        // Los permisos no son validos para escribir el fichero
        m_eErrorFlag = FError::OpenModeNotValid;
      }
    }
  }
  else
  {
    m_eErrorFlag = m_pFid ? FError::InputNotValid : FError::FileNotOpen;
  }
  return 0;
}

/* --- Operadores --- */

const FileUtilities::TFile& FileUtilities::TFile::operator=(const FileUtilities::TFile& _oTFile)
{
  if (this != &_oTFile)
  {
    m_eOpenMode = _oTFile.m_eOpenMode == FMode::Count ? FMode::Invalid : _oTFile.m_eOpenMode;
    // Copia del nombre del fichero
    if (_oTFile.m_sFileName)
    {
      m_sFileName = new char[strlen(_oTFile.m_sFileName) + 1];
      strcpy(m_sFileName, _oTFile.m_sFileName);
    }
    // Abrir el fichero si estaba abierto
    if (_oTFile.m_pFid)
    {
      OpenFile();
    }
    else m_pFid = nullptr;
  }
  return *this;
}

const FileUtilities::TFile& FileUtilities::TFile::operator=(FileUtilities::TFile&& _oTFile) noexcept
{
  if (this != &_oTFile)
  {
    m_eOpenMode = _oTFile.m_eOpenMode == FMode::Count ? FMode::Invalid : _oTFile.m_eOpenMode;
    // Robo de punteros! :O
    m_sFileName = _oTFile.m_sFileName;
    _oTFile.m_sFileName = nullptr;

    m_pFid = _oTFile.m_pFid;
    _oTFile.m_pFid = nullptr;

    m_bEOF = _oTFile.m_bEOF;
  }
  return *this;
}

const char* FileUtilities::TFile::GetFilename()
{
  return m_sFileName;
}

FError FileUtilities::TFile::GetErrorFlag()
{
  return m_eErrorFlag;
}

FMode FileUtilities::TFile::GetOpenMode()
{
  return m_eOpenMode;
}

bool FileUtilities::TFile::GetEOF()
{
  return m_bEOF;
}
