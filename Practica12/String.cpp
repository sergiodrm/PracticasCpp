#include "String.h"
#include <assert.h>
#include <math.h>

#define EQUAL_STRING 0u


/**
* UTILITIES
*/
template <typename T>
inline bool InRange(T _val, T _min, T _max)
{
  return _min <= _val && _val >= _max;
}

/**
* CString definition
*/

CString::CString(const char* str)
{
  Init(str);
}

CString::CString(const CString& str)
{
  Init(str.m_pStr);
}

CString::~CString()
{
  if (m_pStr != nullptr)
    delete m_pStr;
}

bool CString::operator==(const CString& other) const
{
  return EQUAL_STRING == Compare(other);
}

bool CString::operator!=(const CString& other) const
{
  return EQUAL_STRING != Compare(other);
}

bool CString::operator<(const CString& other) const 
{
  return EQUAL_STRING < Compare(other);
}

bool CString::operator>(const CString& other) const 
{
  return EQUAL_STRING > Compare(other);
}

CString CString::operator+(const CString& other) const
{
  CString concatenatedString(*this);
  concatenatedString.Concatenate(other);
  return concatenatedString;
}

CString CString::operator+(char c) const
{
  CString concatenatedString(*this);
  concatenatedString.Concatenate(CString(&c));

  return concatenatedString;
}

CString& CString::operator=(const CString& other)
{
  // Solo reservar memoria si la actual es distinta que la nueva. 
  // Si es igual se borra lo anterior y se reutiliza.
  if (other.m_uSize != m_uSize)
  {
    // Liberar la memoria ocupada
    if (m_pStr != nullptr)
      delete m_pStr;
    // Reservar memoria para la nueva cadena
    m_uSize = other.m_uSize;
    m_pStr = new char[m_uSize];
    assert(m_pStr != nullptr);
  }
  Copy(other.m_pStr, m_pStr);
  return *this;
}

CString& CString::operator=(char c)
{
  if (m_pStr != nullptr)
    delete m_pStr;
  m_uSize = 1u;
  m_pStr = new char(c);
  return *this;
}

CString& CString::operator+=(const CString& other)
{
  Concatenate(other);
  return *this;
}

CString& CString::operator+=(char c)
{
  const char cStr[] = { c, '\0' };
  Concatenate(CString(cStr));
  return *this;
}

char& CString::operator[](unsigned int pos)
{
  assert(pos < m_uSize);
  return *(m_pStr + pos);
}

const char& CString::operator[](unsigned int pos) const
{
  assert(pos < m_uSize);
  return *(m_pStr + pos);
}

int CString::Length() const
{
  return static_cast<int>(m_uSize);
}

CString CString::FromInt(int val)
{
  int iNumber = val;
  CString stringNumber;
  if (iNumber < 0)
  {
    stringNumber += '-';
    iNumber *= -1;
  }
  stringNumber += FromInt_Internal(iNumber);
  return stringNumber;
}

CString CString::HexFromInt(int val)
{
  // A partir de mascaras, sacar los conjuntos de 4 bytes para pasarlos a hex
  int iMasc = 0x000000F;
  const int iShift = 4;
  CString hexString;

  // Contador para desplazar los bits del numero hacia la derecha una vez aplicada la mascara
  int iCounter = 0;
  while (iMasc != 0)
  {
    int hexNumber = val & iMasc;
    hexNumber = hexNumber >> (iCounter * iShift);
    if (hexNumber < 10)
    {
      hexString = FromInt(hexNumber) + hexString;
    }
    else
    {
      char cHexLetter[] = { 'A' + static_cast<char>(hexNumber - 10), '\0' };
      hexString = CString(cHexLetter) + hexString;
    }

    // Actualizar mascara y contador
    iMasc = iMasc << iShift;
    ++iCounter;

    // [TODO] falta que convierta los numeros negativos
  }

  return hexString;
}

CString CString::FromFloat(float val)
{
  // Extraer la parte entera
  int integerNum = static_cast<int>(val);
  // Parte decimal
  float decimalNum = val - static_cast<float>(integerNum);
  // Quitar la coma de la parte decimal usando la operacion resto
  while (fmodf(decimalNum, 1.f) != 0)
  {
    decimalNum *= 10.f;
  }

  CString integerString = FromInt(integerNum);
  CString decimalString = FromInt(static_cast<int>(decimalNum));

  return integerString + CString(".") + decimalString;
}

int CString::ToInt() const
{
  assert(m_pStr != nullptr);
  int iNumber = 0;
  unsigned int uIndex = m_pStr[0] == '-' ? 1 : 0;
  while (m_pStr[uIndex] != '\0' && m_pStr[uIndex] != '.')
  {
    iNumber *= 10;
    iNumber += static_cast<int>(m_pStr[uIndex] - '0');
    ++uIndex;
  }
  if (m_pStr[0] == '-')
    iNumber *= -1;
  return iNumber;
}

float CString::ToFloat() const
{
  assert(m_pStr != nullptr);
  // Parte entera
  float fNumber = static_cast<float>(ToInt());
  // Encontrar la coma
  unsigned int uIndex = 0;
  while (m_pStr[uIndex] != '.' && m_pStr[uIndex] != '\0')
  {
    ++uIndex;
  }
  // Si hay coma, extraer la parte decimal y sumarla a la parte entera
  if (m_pStr[uIndex] == '.')
  {
    CString decimalString(m_pStr + uIndex + 1);
    float fDecimal = static_cast<float>(decimalString.ToInt());
    fDecimal /= powf(10.f, static_cast<float>(decimalString.m_uSize - 1));
    fNumber += fDecimal;
  }
  return fNumber;
}

const char* CString::ToCString() const
{
  assert(m_pStr != nullptr);
  return m_pStr;
}

CString CString::Left(int n) const
{
  // Devolver los primeros n caracteres empezando por la izquierda
  assert(m_pStr != nullptr);
  assert(static_cast<unsigned int>(n) < m_uSize);
  char charSaved = m_pStr[n];
  m_pStr[n] = '\0';
  CString leftString(m_pStr);
  m_pStr[n] = charSaved;
  return leftString;
}

CString CString::Right(int n) const
{
  // Devolver los primeros n caracteres empezando por la derecha
  assert(m_pStr != nullptr);
  assert(static_cast<unsigned int>(n) < m_uSize);
  CString rightString(m_pStr + m_uSize - 1 - n);
  return rightString;
}

CString CString::Mid(int ofs, int n)
{
  // Devolver n caracteres desde el numero ofs
  assert(m_pStr != nullptr);
  assert(static_cast<unsigned int>(ofs + n) < m_uSize);
  char charSaved = m_pStr[ofs + n];
  m_pStr[ofs + n] = '\0';
  CString middleString(m_pStr + ofs);
  m_pStr[ofs + n] = charSaved;
  return middleString;
}

CString CString::Replace(const CString& find, const CString& rep) const
{
  assert(m_pStr != nullptr);
  assert(find.m_pStr != nullptr);
  assert(rep.m_pStr != nullptr);

  int stringToReplaceIndex = Find(find, 0);
  CString replacedString(m_pStr);
  if (stringToReplaceIndex >= 0)
  {
    char charSaved = replacedString[stringToReplaceIndex + rep.m_uSize - 1];
    Copy(rep.m_pStr, replacedString.m_pStr + stringToReplaceIndex);
    replacedString[stringToReplaceIndex + rep.m_uSize - 1] = charSaved;
  }
  return replacedString;
}

int CString::Find(const CString& str, int ofs) const
{
  // Empezar a buscar la cadena str a partir del elemento ofs
  assert(m_pStr != nullptr);
  assert(str.m_pStr != nullptr);
  assert(static_cast<unsigned int>(ofs) < m_uSize);

  int iWantedString = -1;
  if (m_uSize >= str.m_uSize)
  {
    // Dos indices: uno para la cadena donde se esta buscando y otro para la buscada
    unsigned int uIndexOriginal = ofs;
    unsigned int uIndexStrWanted = 0;
    while (m_pStr[uIndexOriginal] != '\0' && str[uIndexStrWanted] != '\0')
    {
      // Avanzar ambos indices si los caracteres son iguales
      if (m_pStr[uIndexOriginal] == str[uIndexStrWanted])
      {
        uIndexStrWanted++;
      }
      else
      {
        uIndexStrWanted = 0;
      }
      uIndexOriginal++;
    }
    // Si se ha llegado al final de la cadena buscada, devolver el indice del inicio de esta
    if (str[uIndexStrWanted] == '\0')
    {
      iWantedString = uIndexOriginal - uIndexStrWanted;
    }
  }
  return iWantedString;
}

CString CString::ToUpper() const
{
  assert(m_pStr != nullptr);
  CString upperString(*this);
  unsigned int uIndex = 0;
  while (upperString[uIndex] != '\0')
  {
    if (InRange<char>(upperString[uIndex], 'a', 'z'))
    {
      upperString[uIndex] -= 'a';
      upperString[uIndex] += 'A';
    }
    ++uIndex;
  }
  return upperString;
}

CString CString::ToLower() const
{
  assert(m_pStr != nullptr);
  CString lowerString(*this);
  unsigned int uIndex = 0;
  while (lowerString[uIndex] != '\0')
  {
    if (InRange<char>(lowerString[uIndex], 'A', 'Z'))
    {
      lowerString[uIndex] -= 'A';
      lowerString[uIndex] += 'a';
    }
    ++uIndex;
  }
  return lowerString;
}

CString CString::LTrim() const
{
  assert(m_pStr != nullptr);

  unsigned int uIndex = 0;
  while (m_pStr[uIndex] == ' ' && m_pStr[uIndex] != '\0');
  {
    uIndex++;
  }
  CString ltrimString(m_pStr + uIndex);

  return ltrimString;
}

CString CString::RTrim() const
{
  assert(m_pStr != nullptr);
  unsigned int uIndex = m_uSize - 2; // m_uSize - 1 = '\0'
  while (m_pStr[uIndex] == ' ' && uIndex >= 0)
  {
    uIndex--;
  }

  return Left(uIndex);
}

CString CString::Trim() const
{
  assert(m_pStr != nullptr);

  CString leftTrimString(LTrim());
  return leftTrimString.RTrim();
}

CString CString::LSet(int len, char c) const
{
  assert(m_pStr != nullptr);

  char stringFill[] = { c,'\0' };

  CString leftFilledString(*this);
  while (leftFilledString.m_uSize < static_cast<unsigned int>(len))
  {
    leftFilledString = CString(stringFill) + leftFilledString;
  }
  return leftFilledString;
}

CString CString::RSet(int len, char c) const
{
  assert(m_pStr != nullptr);
  CString rightFilledString(*this);
  while (rightFilledString.m_uSize < static_cast<unsigned int>(len))
  {
    rightFilledString += c;
  }
  return rightFilledString;
}

CString CString::StripExt() const
{
  return CString();
}

CString CString::StripDir() const
{
  return CString();
}

CString CString::ExtractExt() const
{
  return CString();
}

CString CString::ExtractDir() const
{
  return CString();
}

CString CString::RealPath() const
{
  return CString();
}

CString CString::Read(const CString& /*filename*/)
{
  return CString();
}

void CString::Write(const CString& /*filename*/, bool /*append*/) const
{
}

void CString::Init(const char* _str)
{
  m_pStr = nullptr;
  m_uSize = 0;

  if (_str != nullptr)
  {
    m_uSize = Length(_str);
    m_pStr = new char[m_uSize];
    assert(m_pStr != nullptr);
    Copy(_str, m_pStr);
  }
}

int CString::Compare(const CString& _other) const
{
  // Se inicializa una variable iEqual que marca la igualdad entre los strings. 
  // Se resta caracter a caracter y si la resta es 0, son iguales. 
  // Sino, se devolvera un numero <0 || >0 en funcion del resultado de la resta.
  unsigned int uIndex = 0;
  int iEqual = EQUAL_STRING;
  while (iEqual == EQUAL_STRING)
  {
    iEqual = m_pStr[uIndex] - _other.m_pStr[uIndex];
  }
  return 0;
}

void CString::Copy(const char* _origin, char* _destiny)
{
  // Se asume que la cadena de salida ya tiene reservada memoria suficiente para hacer la copia
  assert(_origin != nullptr);
  assert(_destiny != nullptr);
  unsigned int uIndex = 0;
  while (_origin[uIndex] != '\0')
  {
    _destiny[uIndex] = _origin[uIndex];
    ++uIndex;
  }
  // Añadir el caracter nulo en el destino para marcar el final del string
  _destiny[uIndex] = '\0';
}

int CString::Length(const char* _str)
{
  assert(_str != nullptr);
  unsigned int uIndex = 0;
  while (_str[uIndex] != '\0')
  {
    ++uIndex;
  }
  // Incluir el caracter nulo en la dimension devuelta
  ++uIndex;
  return uIndex;
}

void CString::Concatenate(const CString& _str)
{
  // Usar el metodo de copiar para concatenar ambas cadenas en la instancia del objeto que llama al metodo
  assert(m_pStr != nullptr);
  assert(_str.m_pStr != nullptr);
  unsigned int uNewSize = m_uSize + _str.m_uSize;
  char* concatenatedString = new char[uNewSize];
  assert(concatenatedString != nullptr);
  Copy(m_pStr, concatenatedString);
  Copy(_str.m_pStr, concatenatedString + m_uSize - 1);

  // Liberar la memoria utilizada en el antiguo string y redireccionar el puntero
  delete m_pStr;
  m_pStr = concatenatedString;
  m_uSize = uNewSize - 1;
}

CString CString::Concatenate(const CString& _str1, const CString& _str2)
{
  CString concatenatedString;
  concatenatedString.m_uSize = _str1.m_uSize + _str2.m_uSize;
  concatenatedString.m_pStr = new char[concatenatedString.m_uSize];
  assert(concatenatedString.m_pStr != nullptr);

  Copy(_str1.m_pStr, concatenatedString.m_pStr);
  Copy(_str2.m_pStr, concatenatedString.m_pStr + _str1.m_uSize);

  return concatenatedString;
}

CString CString::FromInt_Internal(int val)
{
  // Averiguar el resto de la division del numero entre 10 para obtener el ultimo digito
  int iRemainder = val % 10;
  // Castearlo a char y añadir el offset del codigo ascii
  char cNumber[2] = { static_cast<char>(iRemainder) + '0', '\0' };
  if (val < 10)
  {
    // Si el parametro es menor que 10 no hay mas numeros que convertir.
    return CString(cNumber);
  } // Si es mayor volver a llamar al metodo con el parametro quitando el ultimo digito
  else return FromInt_Internal(static_cast<int>(val / 10)) + CString(cNumber);
}



