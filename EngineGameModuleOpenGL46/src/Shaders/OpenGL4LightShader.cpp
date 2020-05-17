#include "OpenGL4LightShader.h"

OpenGL4LightShader::OpenGL4LightShader()
{
}

OpenGL4LightShader::OpenGL4LightShader(const OpenGL4LightShader &)
{
}

OpenGL4LightShader::~OpenGL4LightShader()
{
}

bool OpenGL4LightShader::Initialize(OpenGL4Object * openGL, HWND hwnd)
{
	bool result;
	
	result = InitializeShader("Resources/Shaders/lightVS.glsl", "Resources/Shaders/lightPS.glsl", openGL, hwnd);
	if (!result) return false;

	return true;
}

void OpenGL4LightShader::Shutdown(OpenGL4Object * openGL)
{
	ShutdownShader(openGL);

	return;
}

void OpenGL4LightShader::SetShader(OpenGL4Object * openGL)
{
	openGL->glUseProgram(m_shaderProgram);

	return;
}

bool OpenGL4LightShader::InitializeShader(char * vsFilename, char * fsFilename, OpenGL4Object * openGL, HWND hwnd)
{

	const char * vertexShaderBuffer;
	const char * fragmentShaderBuffer;
	int status;

	vertexShaderBuffer = LoadShaderSourceFile(vsFilename);
	if (!vertexShaderBuffer) return false;

	fragmentShaderBuffer = LoadShaderSourceFile(fsFilename);
	if (!fragmentShaderBuffer) return false;

	m_vertexShader = openGL->glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = openGL->glCreateShader(GL_FRAGMENT_SHADER);

	openGL->glShaderSource(m_vertexShader, 1, &vertexShaderBuffer, NULL);
	openGL->glShaderSource(m_fragmentShader, 1, &fragmentShaderBuffer, NULL);

	delete[] vertexShaderBuffer;
	vertexShaderBuffer = 0;

	delete[] fragmentShaderBuffer;
	fragmentShaderBuffer = 0;

	openGL->glCompileShader(m_vertexShader);
	openGL->glCompileShader(m_fragmentShader);

	openGL->glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		OutputShaderErrorMessage(openGL, hwnd, m_vertexShader, vsFilename);
		return false;
	}

	openGL->glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		OutputShaderErrorMessage(openGL, hwnd, m_fragmentShader, fsFilename);
		return false;
	}

	m_shaderProgram = openGL->glCreateProgram();

	openGL->glAttachShader(m_shaderProgram, m_vertexShader);
	openGL->glAttachShader(m_shaderProgram, m_fragmentShader);

	openGL->glBindAttribLocation(m_shaderProgram, 0, "inputPosition");
	openGL->glBindAttribLocation(m_shaderProgram, 1, "inputTexCoord");
	openGL->glBindAttribLocation(m_shaderProgram, 2, "inputNormal");

	openGL->glLinkProgram(m_shaderProgram);

	openGL->glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);

	if (status != 1)
	{
		OutputLinkerErrorMessage(openGL, hwnd, m_shaderProgram);
		return false;
	}

	return true;
}


char * OpenGL4LightShader::LoadShaderSourceFile(char * filename)
{
	ifstream fin;
	int fileSize;
	char input;
	char* buffer;

	fin.open(filename);
	if (fin.fail()) return 0;

	fileSize = 0;
	fin.get(input);
	
	while (!fin.eof())
	{
		fileSize++;
		fin.get(input);
	}
	fin.close();

	buffer = new char[fileSize + 1];
	if (!buffer) return 0;
	
	fin.open(filename);
	
	fin.read(buffer, fileSize);
	fin.close();

	buffer[fileSize] = '\0';

	return buffer;
}

void OpenGL4LightShader::OutputShaderErrorMessage(OpenGL4Object * openGL, HWND hwnd, unsigned int shaderId, char * shaderFilename)
{
	int logSize, i;
	char * infoLog;
	ofstream fout;

	wchar_t newString[128];

	unsigned int error, convertedChars;

	openGL->glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	logSize++;

	infoLog = new char[logSize];

	if (!infoLog) return;

	openGL->glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

	fout.open("shader-error.txt");

	for (i = 0; i < logSize; i++)
	{
		fout << infoLog[i];
	}

	fout.close();

	error = mbstowcs_s(&convertedChars, newString, 128, shaderFilename, 128);
	if (error != 0) return;

	MessageBoxW(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", newString, MB_OK);

	return;
}

void OpenGL4LightShader::OutputLinkerErrorMessage(OpenGL4Object * openGL, HWND hwnd, unsigned int programId)
{
	int logSize, i;
	char * infoLog;
	ofstream fout;

	unsigned int error, convertedChars;

	openGL->glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

	logSize++;

	infoLog = new char[logSize];

	if (!infoLog) return;

	openGL->glGetProgramInfoLog(programId, logSize, NULL, infoLog);

	fout.open("linker-error.txt");

	for (i = 0; i < logSize; i++)
	{
		fout << infoLog[i];
	}

	fout.close();

	MessageBoxW(hwnd, L"Error compiling linker. Check linker-error.txt for message.", L"Linker Error", MB_OK);

	return;
}

void OpenGL4LightShader::ShutdownShader(OpenGL4Object * openGL)
{
	openGL->glDetachShader(m_shaderProgram, m_vertexShader);
	openGL->glDetachShader(m_shaderProgram, m_fragmentShader);

	openGL->glDeleteShader(m_vertexShader);
	openGL->glDeleteShader(m_fragmentShader);

	openGL->glDeleteProgram(m_shaderProgram);
}


bool OpenGL4LightShader::SetShaderParameters(OpenGL4Object * openGL, float* worldMatrix, float* viewMatrix, float* projectionMatrix, int textureUnit, float* lightDirection, float* diffuseLightColor, float* ambientLight)
{
	unsigned int location;

	location = openGL->glGetUniformLocation(m_shaderProgram, "worldMatrix");
	if (location == -1) return false;
	openGL->glUniformMatrix4fv(location, 1, false, worldMatrix);

	location = openGL->glGetUniformLocation(m_shaderProgram, "viewMatrix");
	if (location == -1) return false;
	openGL->glUniformMatrix4fv(location, 1, false, viewMatrix);

	location = openGL->glGetUniformLocation(m_shaderProgram, "projectionMatrix"); // Set the projection matrix in the vertex shader.
	if (location == -1) return false;
	openGL->glUniformMatrix4fv(location, 1, false, projectionMatrix);

	location = openGL->glGetUniformLocation(m_shaderProgram, "shaderTexture"); // Set the texture in the pixel shader to use the data from the first texture unit.
	if (location == -1) return false;
	openGL->glUniform1i(location, textureUnit);

	location = openGL->glGetUniformLocation(m_shaderProgram, "lightDirection"); // Set the light direction in the pixel shader.
	if (location == -1) return false;
	openGL->glUniform3fv(location, 1, lightDirection);

	location = openGL->glGetUniformLocation(m_shaderProgram, "diffuseLightColor"); // Set the light direction in the pixel shader.
	if (location == -1) return false;
	openGL->glUniform4fv(location, 1, diffuseLightColor);

	location = openGL->glGetUniformLocation(m_shaderProgram, "ambientLight"); //The ambient value in the pixel shader is set here. 
	if (location == -1) return false;
	openGL->glUniform4fv(location, 1, ambientLight);

	return true;
}