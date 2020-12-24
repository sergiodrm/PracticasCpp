#include "String.h"
#include <assert.h>

#define EQUAL_STRING 0u

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
  CString concatenatedString;
  concatenatedString.Concatenate(other);
  //concatenatedString.m_uSize = m_uSize + other.m_uSize;
  //concatenatedString.m_pStr = new char[concatenatedString.m_uSize];
  //assert(concatenatedString.m_pStr != nullptr);
  //Copy(m_pStr, concatenatedString.m_pStr);
  //Copy(other.m_pStr, concatenatedString.m_pStr + m_uSize);
  return concatenatedString;
}

CString CString::operator+(char c) const
{
  CString concatenatedString;
  concatenatedString.Concatenate(CString(&c));
  //concatenatedString.m_uSize = m_uSize + 1;
  //concatenatedString.m_pStr = new char[concatenatedString.m_uSize];
  //assert(concatenatedString.m_pStr != nullptr);
  //Copy(m_pStr, concatenatedString.m_pStr);
  //concatenatedString[m_uSize] = c;
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
  Concatenate(CString(&c));
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
  return CString();
}

CString CString::HexFromInt(int val)
{
  return CString();
}

CString CString::FromFloat(float val)
{
  return CString();
}

int CString::ToInt() const
{
  return 0;
}

float CString::ToFloat() const
{
  return 0.0f;
}

const char* CString::ToCString() const
{
  return nullptr;
}

CString CString::Left(int n) const
{
  return CString();
}

CString CString::Right(int n) const
{
  return CString();
}

CString CString::Mid(int ofs, int n)
{
  return CString();
}

CString CString::Replace(const CString& find, const CString& rep) const
{
  return CString();
}

int CString::Find(const CString& str, int ofs) const
{
  return 0;
}

CString CString::ToUpper() const
{
  return CString();
}

CString CString::ToLower() const
{
  return CString();
}

CString CString::LTrim() const
{
  return CString();
}

CString CString::RTrim() const
{
  return CString();
}

CString CString::Trim() const
{
  return CString();
}

CString CString::LSet(int len, char c) const
{
  return CString();
}

CString CString::RSet(int len, char c) const
{
  return CString();
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

CString CString::Read(const CString& filename)
{
  return CString();
}

void CString::Write(const CString& filename, bool append) const
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
