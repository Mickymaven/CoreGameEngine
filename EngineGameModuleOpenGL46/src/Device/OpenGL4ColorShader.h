#if !defined (OPENGL4COLORSHADER_H)
#define OPENGL4COLORSHADER_H

#include <fstream>
using namespace std;


#include "OpenGL4Object.h"

class OpenGL4ColorShader
{

private:
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	unsigned int m_shaderProgram;


public:
	OpenGL4ColorShader();
	~OpenGL4ColorShader();

	bool Initialize(OpenGL4Object * object, HWND hwnd);
	void Shutdown(OpenGL4Object * object, HWND hwnd);
	void SetShader(OpenGL4Object * object);
	bool SetShaderParameters(OpenGL4Object * object, float * worldMatrix, float * viewMatrix, float * projectionMatrix);
	
private:
	bool InitializeShader(char * vsFilename, char * fsFilename, OpenGL4Object * object, HWND hwnd);
	char* LoadShaderSourceFile(char * path);
	void OutputShaderErrorMessage(OpenGL4Object* object, HWND hwnd, unsigned int id, char * path);
	void OutputLinkerErrorMessage(OpenGL4Object* object, HWND hwnd, unsigned int id);
	void ShutdownShader(OpenGL4Object * object);


};


#endif