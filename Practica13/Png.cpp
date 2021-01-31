#define _CRT_SECURE_NO_WARNINGS 1
#include "Png.h"
#include <string>
#include <assert.h>

// **************************************************************
//
// **************************************************************
int CPng::SetPngFile(const char* /*pszPngFile*/)
{
	printf("Lectura del fichero comprimido Png\n");
	UncompressImage();
	return 0;
}

// **************************************************************
//
// **************************************************************
void CPng::DeleteAlphaChannel()
{
	assert(m_pBuffer != nullptr);
	m_uColorBytes = 3;
	m_uSize	= m_uResX * m_uResY * m_uColorBytes;
	unsigned char* pNewBuffer = new unsigned char[m_uSize];
	unsigned int uIndex = 0;
	unsigned int uPixel = 0;
	while (uIndex < m_uSize)
	{
		pNewBuffer[uIndex] = m_pBuffer[uPixel + uIndex];
		uIndex++;
		if (uIndex % 3 == 0)
			uPixel++;
	}
	delete m_pBuffer;
	m_pBuffer = pNewBuffer;
}

// **************************************************************
//
// **************************************************************
void CPng::DeleteAlphaChannelFromImages(CImagen* _tImages, unsigned int _uLength)
{
	assert(_tImages != nullptr);
	for (unsigned int uIndex = 0; uIndex < _uLength; uIndex++)
	{
		CPng* pPngImage = reinterpret_cast<CPng*>(_tImages + uIndex);
		if (pPngImage != nullptr)
		{
			pPngImage->DeleteAlphaChannel();
		}
	}
}

// **************************************************************
//
// **************************************************************
int CPng::UncompressImage()
{
	printf("Descompresión de Imagen Png\n");
	m_uResX				= 480;
	m_uResY				= 320;
	m_uColorBytes	= 4;
	m_uSize				= m_uResX * m_uResY * m_uColorBytes;
	m_pBuffer			= new unsigned char[m_uSize];
	strcpy(reinterpret_cast<char *>(m_pBuffer), "Bytes del buffer descomprimido desde Png");
	return 0;
}