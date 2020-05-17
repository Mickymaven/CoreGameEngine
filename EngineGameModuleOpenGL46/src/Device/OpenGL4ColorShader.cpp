#include "OpenGL4ColorShader.h"

OpenGL4ColorShader::OpenGL4ColorShader()
{
}

OpenGL4ColorShader::~OpenGL4ColorShader()
{
}

bool OpenGL4ColorShader::Initialize(OpenGL4Object * object, HWND hwnd)
{
	bool result = InitializeShader((char*)"Resources/Shaders/colorVS.glsl", (char*)"Resources/Shaders/colorPS.glsl", object, hwnd);
	
	
	if (!result)
	{
		return false;
	}
	
	return true;
}

void OpenGL4ColorShader::Shutdown(OpenGL4Object * object, HWND hwnd)
{
	ShutdownShader(object);
}

void OpenGL4ColorShader::SetShader(OpenGL4Object * object)
{
	object->glUseProgram(m_shaderProgram);
}

bool OpenGL4ColorShader::SetShaderParameters(OpenGL4Object * object, float * worldMatrix, float * viewMatrix, float * projectionMatrix)
{
	unsigned int location;

	location = object->glGetUniformLocation(m_shaderProgram, "worldMatrix");
	if (location == -1) return false;

	object->glUniformMatrix4fv(location, 1, false, worldMatrix);

	location = object->glGetUniformLocation(m_shaderProgram, "viewMatrix");
	if (location == -1) return false;

	object->glUniformMatrix4fv(location, 1, false, viewMatrix);

	location = object->glGetUniformLocation(m_shaderProgram, "projectionMatrix");
	if (location == -1) return false;

	object->glUniformMatrix4fv(location, 1, false, projectionMatrix);

	return true;
}

bool OpenGL4ColorShader::InitializeShader(char * vsFilename, char * fsFilename, OpenGL4Object * object, HWND hwnd)
{
	const char * vertexShaderBuffer = nullptr;
	const char * fragmentShaderBuffer = nullptr;
	int status;

	vertexShaderBuffer = LoadShaderSourceFile(vsFilename);
	if (vertexShaderBuffer == nullptr)
	{
		return false;
	}

	fragmentShaderBuffer = LoadShaderSourceFile(fsFilename);
	if (fragmentShaderBuffer == nullptr)
	{
		return false;
	}

	m_vertexShader = object->glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = object->glCreateShader(GL_FRAGMENT_SHADER);

	object->glShaderSource(m_vertexShader, 1, &vertexShaderBuffer, NULL);
	object->glShaderSource(m_fragmentShader, 1, &fragmentShaderBuffer, NULL);

	delete[] vertexShaderBuffer;
	vertexShaderBuffer = 0;

	delete[] fragmentShaderBuffer;
	fragmentShaderBuffer = 0;

	object->glCompileShader(m_vertexShader);
	object->glCompileShader(m_fragmentShader);


	// Check to see if the vertex shader compiled successfully.
	object->glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		OutputShaderErrorMessage(object, hwnd, m_vertexShader, vsFilename);
		return false;
	}

	object->glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		OutputShaderErrorMessage(object, hwnd, m_fragmentShader, vsFilename);
		return false;
	}

	m_shaderProgram = object->glCreateProgram();

	object->glAttachShader(m_shaderProgram, m_vertexShader);
	object->glAttachShader(m_shaderProgram, m_fragmentShader);

	object->glBindAttribLocation(m_shaderProgram, 0, "inputPosition");
	object->glBindAttribLocation(m_shaderProgram, 1, "inputColor");

	object->glLinkProgram(m_shaderProgram);

	object->glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
	if (status != 1)
	{
		OutputLinkerErrorMessage(object, hwnd, m_shaderProgram);
		return false;
	}
	
	return true;
}

char * OpenGL4ColorShader::LoadShaderSourceFile(char * path)
{
	ifstream fileIn;
	int fileSize;
	char input;
	char* buffer;

	//test and info

	fileIn.open(path);

	if (fileIn.fail()) return 0;

	fileSize = 0;

	fileIn.get(input);

	while (!fileIn.eof())
	{
		fileSize++;
		fileIn.get(input);
	}

	fileIn.close();


	//read

	buffer = new char[fileSize + 1];
	if (! buffer) return 0;

	fileIn.open(path);
	fileIn.read(buffer, fileSize);
	fileIn.close();

	buffer[fileSize] = '\0';

	return buffer;
}

void OpenGL4ColorShader::OutputShaderErrorMessage(OpenGL4Object * object, HWND hwnd, unsigned int id, char * path)
{
	int logSize;
	int i;
	char * infoLog;
	ofstream fileOut;
	wchar_t newString[128];
	unsigned int error;
	size_t convertedChars;

	object->glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);

	logSize++;

	infoLog = new char[logSize];
	if (! infoLog) return;

	object->glGetShaderInfoLog(id, logSize, NULL, infoLog);

	fileOut.open("shader-error.txt");

	for (i = 0; i < logSize; i++)
	{
		fileOut << infoLog[i];
	}

	fileOut.close();

	error = mbstowcs_s(&convertedChars, newString, 128, path, 128);
	if (! error) return;

	MessageBoxW(hwnd, L"Error compiling shader. Check shader-error.txt for messages.", newString, MB_OK);
}

void OpenGL4ColorShader::OutputLinkerErrorMessage(OpenGL4Object * object, HWND hwnd, unsigned int id)
{
	int logSize;
	int i;
	char * infoLog;
	ofstream fileOut;

	object->glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logSize);

	logSize++;

	infoLog = new char[logSize];
	if (!infoLog) return;

	object->glGetProgramInfoLog(id, logSize, NULL, infoLog);

	fileOut.open("linker-error.txt");

	for (i = 0; i < logSize; i++)
	{
		fileOut << infoLog[i];
	}

	fileOut.close();

	MessageBoxW(hwnd, L"Error compiling shader. Check shader-error.txt for messages.", L"LinkerError", MB_OK);
}

void OpenGL4ColorShader::ShutdownShader(OpenGL4Object * object)
{
	object->glDetachShader(m_shaderProgram, m_vertexShader);
	object->glDetachShader(m_shaderProgram, m_fragmentShader);

	object->glDeleteShader(m_vertexShader);
	object->glDeleteShader(m_fragmentShader);

	object->glDeleteProgram(m_shaderProgram);
}
