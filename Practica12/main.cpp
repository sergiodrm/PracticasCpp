
#include "String.h"
#include <string>

int main()
{
	char* m_pszBuffer = new char[32];
	strcpy(m_pszBuffer, "Hola");
	printf("%s\n", m_pszBuffer);
	if (m_pszBuffer)
	{
		char* pszAux = m_pszBuffer;
		m_pszBuffer = new char[32];
		_itoa(atoi(pszAux) + 1, m_pszBuffer, 10);
		delete[]pszAux;
	}
	printf("%s\n", m_pszBuffer);
  return 0;
}