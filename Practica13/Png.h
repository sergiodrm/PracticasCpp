#include "Imagen.h"

class CPng : public CImagen
{
public:
	int SetPngFile(const char *pszFile);

	void DeleteAlphaChannel();
	static void DeleteAlphaChannelFromImages(CImagen* _tImages, unsigned int _uLength);

private:
	int UncompressImage();
};