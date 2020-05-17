#if !defined (OPENGL4TEXTURESHADER_H)
#define OPENGL4TEXTURESHADER_H

#include <fstream>
using namespace std;

#include "OpenGL4Object.h"

class OpenGL4TextureShader
{
private:
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	unsigned int m_shaderProgram;

public:
	OpenGL4TextureShader();
	OpenGL4TextureShader(const OpenGL4TextureShader &);
	~OpenGL4TextureShader();

	bool ShaderInitialize(OpenGL4Object * openGL, HWND hwnd);
	void Shutdown(OpenGL4Object * openGL);
	void SetShader(OpenGL4Object * openGL);
	bool SetShaderParameters(OpenGL4Object * openGL, float* worldMatrix, float* viewMatrix, float* projectionMatrix, int textureUnit);

private:
	bool InitializeShader(char *vsFilename, char* fsFilename, OpenGL4Object * openGL, HWND hwnd);
	char * LoadShaderSourceFile(char*filename);
	void OutputShaderErrorMessage(OpenGL4Object * openGL, HWND hwnd, unsigned int shaderId, char * shaderFilename);
	void OutputLinkerErrorMessage(OpenGL4Object * openGL, HWND hwnd, unsigned int programId);
	void ShutdownShader(OpenGL4Object * openGL);
	
};

#endif