#if !defined (TEXTURECLASS_H)
#define TEXTURECLASS_H

#include <stdio.h>
#include "../Device/OpenGL4Object.h"

class TextureClass
{

private:
	//variables
	
	bool loaded;
	unsigned int m_textureID;
	
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	TextureClass();
	TextureClass(const TextureClass &);
	~TextureClass();

	bool Initialize(OpenGL4Object * openGL, char * filename, unsigned int textureUnit, bool wrap);
	void Shutdown();

private:
	bool LoadTarga(OpenGL4Object * openGL, char * filename, unsigned int textureUnit, bool wrap); //'Load Targe'





};


#endif