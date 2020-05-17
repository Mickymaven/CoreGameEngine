#if !defined(MODELCLASS_H)
# define MODELCLASS_H

#include <iostream>
using std::iostream;

#include <vector>
#include <fstream>
using namespace std;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineGameModel/src/Maths/LMVector2.h"

#include "../Device/OpenGL4Object.h"
#include "../Device/OpenGL4TextureShader.h"
#include "TextureClass.h"

/*

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
*/

class Mesh;

class ModelClass
{
private:
	/*
	struct VertexType
	{
		float x, y, z;
		float r, g, b;
	};
	*/
	struct VertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	int m_vertexCount;
	int m_indexCount;

	unsigned int m_vertexArrayId;
	unsigned int m_vertexBufferId;
	unsigned int m_indexBufferId;

	TextureClass * m_texture;
	ModelType* m_model;

	//GL_BUILD
	std::vector<Mesh> meshes;
	std::string directory;

public:
	ModelClass();
	ModelClass(const OpenGL4Object * object);
	~ModelClass();


	//bool Initialize(OpenGL4Object * object);
	bool Initialize(OpenGL4Object * object, char* modelFilename, char* textureFilename, unsigned int textureUnit, bool wrap);
	void Shutdown(OpenGL4Object * object);
	void Render(OpenGL4Object * object);

private:
	//bool InitializeBuffers4(OpenGL4Object * object);
	bool InitializeBuffers(OpenGL4Object * object);
	void ShutdownBuffers(OpenGL4Object * object);
	void RenderBuffers(OpenGL4Object * object);

	bool LoadTexture(OpenGL4Object * object , char * textureFilename, unsigned int textureUnit, bool wrap);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

	//GL_BUILD STUFF
	//void loadModelUsingAssimp(std::string path);
	//void processNode(aiNode* node, const aiScene* scene);
	//Mesh processMesh(aiMesh* mesh, const aiScene* scene);

};

struct VertexOGL {
	VertexOGL() {

	}

	VertexOGL(const VertexOGL & v)
	{
		Position = v.Position;
		Normal = v.Normal;
		TexCoords = v.TexCoords;
	}

	~VertexOGL() {

	}

	LMVector3 Position;
	LMVector3 Normal;
	LMVector2 TexCoords;
};

class Mesh
{
public:
	static OpenGL4Object * m_object;

	std::vector<VertexOGL> vertices;
	std::vector<GLuint> indices;

	Mesh(std::vector<VertexOGL>& vertices, std::vector<GLuint>& indices);
	~Mesh();
	void Draw();

private:
	GLuint VAO, VBO, EBO;

	void setupMesh();

	void SetObject(const OpenGL4Object & object);


};


#endif