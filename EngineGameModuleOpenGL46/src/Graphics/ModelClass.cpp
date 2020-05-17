/*
#include <assimp/Importer.hpp>
#include <../code/Importer.cpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
*/

#include "ModelClass.h"


ModelClass::ModelClass()
{
	m_texture = 0;
	m_model = 0;
	m_indexBufferId = 0;
	m_indexCount = 0;
	m_vertexArrayId = 0;
	m_vertexBufferId = 0;
	m_vertexCount = 0;
}

ModelClass::ModelClass(const OpenGL4Object * object)
{
	m_texture = 0;
	m_model = 0;
	m_indexBufferId = 0;
	m_indexCount = 0;
	m_vertexArrayId = 0;
	m_vertexBufferId = 0;
	m_vertexCount = 0;
}

ModelClass::~ModelClass()
{

}

/*
bool ModelClass::Initialize(OpenGL4Object * object)
{
	bool result = InitializeBuffers4(object);

	if (!result) return false;

	return true;
}
*/
bool ModelClass::Initialize(OpenGL4Object * object, char* modelFilename, char* textureFilename, unsigned int textureUnit, bool wrap)
{
	bool result;

	result = LoadModel(modelFilename);
	if (!result) return false;
	
	InitializeBuffers(object);
	if (!result) return false;

	result = LoadTexture(object, textureFilename, textureUnit, wrap);
	if (!result) return false;

	return true;
}

void ModelClass::Shutdown(OpenGL4Object * object)
{
	ReleaseTexture();

	ShutdownBuffers(object);

	ReleaseModel();

	return;
}

void ModelClass::Render(OpenGL4Object * object)
{
	RenderBuffers(object);

	return;
}
/*
bool ModelClass::InitializeBuffers4(OpenGL4Object * object)
{
	VertexType * vertices;
	unsigned int * indices;

	m_vertexCount = 3;

	m_indexCount = 3;

	vertices = new VertexType[m_vertexCount];
	if (! vertices) return false;

	indices = new unsigned int[m_indexCount];
	if (! indices) return false;

	// Bottom left.
	vertices[0].x = -1.0f;  // Position.
	vertices[0].y = -1.0f;
	vertices[0].z = 0.0f;

	vertices[0].r = 1.0f;  // Color.
	vertices[0].g = 1.0f;
	vertices[0].b = 0.0f;

	// Top middle.
	vertices[1].x = 0.0f;  // Position.
	vertices[1].y = 1.0f;
	vertices[1].z = 0.0f;

	vertices[1].r = 0.0f;  // Color.
	vertices[1].g = 1.0f;
	vertices[1].b = 0.0f;

	// Bottom right.
	vertices[2].x = 1.0f;  // Position.
	vertices[2].y = -1.0f;
	vertices[2].z = 0.0f;

	vertices[2].r = 0.0f;  // Color.
	vertices[2].g = 1.0f;
	vertices[2].b = 1.0f;

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	object->glGenVertexArrays(1, &m_vertexArrayId);

	object->glBindVertexArray(m_vertexArrayId);
	object->glGenBuffers(1, &m_vertexBufferId);

	object->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	object->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType), vertices, GL_STATIC_DRAW);

	object->glEnableVertexAttribArray(0);
	object->glEnableVertexAttribArray(1);

	object->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	object->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);


	object->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	object->glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(VertexType), (unsigned char*)NULL + (3 * sizeof(float)));


	object->glGenBuffers(1, &m_indexBufferId);

	object->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	object->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}
*/
bool ModelClass::InitializeBuffers(OpenGL4Object* object)
{
	VertexType* vertices;
	unsigned int* indices;
	int i;

	vertices = new VertexType[m_vertexCount];// Create the vertex array.
	if(!vertices) return false;
	
	indices = new unsigned int[m_indexCount];// Create the index array.
	if(!indices) return false;

	for(i=0; i<m_vertexCount; i++)// Load the vertex array and index array with data.
	{
		vertices[i].x  = m_model[i].x;
		vertices[i].y  = m_model[i].y;
		vertices[i].z  = m_model[i].z;
		vertices[i].tu = m_model[i].tu;
		vertices[i].tv = 1.0f - m_model[i].tv;
		vertices[i].nx = m_model[i].nx;
		vertices[i].ny = m_model[i].ny;
		vertices[i].nz = m_model[i].nz;

		indices[i] = i;
	}

	object->glGenVertexArrays(1, &m_vertexArrayId);// Allocate an object vertex array object.

	object->glBindVertexArray(m_vertexArrayId);	// Bind the vertex array object to store all the buffers and vertex attributes we create here.

	object->glGenBuffers(1, &m_vertexBufferId);// Generate an ID for the vertex buffer.

	object->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);// Bind the vertex buffer and load the vertex (position, texture, and normal) data into the vertex buffer.
	object->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType), vertices, GL_STATIC_DRAW);

	object->glEnableVertexAttribArray(0);  // Vertex position.// Enable the three vertex array attributes.
	object->glEnableVertexAttribArray(1);  // Texture coordinates.
	object->glEnableVertexAttribArray(2);  // Normals.

	object->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);// Specify the location and format of the position portion of the vertex buffer.
	object->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);

	object->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);// Specify the location and format of the texture coordinate portion of the vertex buffer.
	object->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char*)NULL + (3 * sizeof(float)));

	object->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);// Specify the location and format of the normal vector portion of the vertex buffer.
	object->glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexType), (unsigned char*)NULL + (5 * sizeof(float)));

	object->glGenBuffers(1, &m_indexBufferId);// Generate an ID for the index buffer.

	object->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);// Bind the index buffer and load the index data into it.
	object->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount* sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	
	delete [] vertices;// Now that the buffers have been loaded we can release the array data.
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers(OpenGL4Object * object)
{
	object->glDisableVertexAttribArray(0);
	object->glDisableVertexAttribArray(1);

	object->glBindBuffer(GL_ARRAY_BUFFER, 0);
	object->glDeleteBuffers(1, &m_vertexBufferId);

	object->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	object->glDeleteBuffers(1, &m_indexBufferId);

	object->glBindVertexArray(0);
	object->glDeleteVertexArrays(1, &m_vertexArrayId);
}

void ModelClass::RenderBuffers(OpenGL4Object * object)
{
	object->glBindVertexArray(m_vertexArrayId);

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}

bool ModelClass::LoadTexture(OpenGL4Object * object, char * textureFilename, unsigned int textureUnit, bool wrap)
{
	bool result;

	m_texture = new TextureClass();
	if (!m_texture) return false;

	result = m_texture->Initialize(object, textureFilename, textureUnit, wrap);
	if (!result) return false;

	return true;
}

void ModelClass::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = 0;
	}

	return;
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}


void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}
/*
void ModelClass::loadModelUsingAssimp(std::string path)
{
	
	Assimp::Importer importer;
	/*
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of('/'));
	this->processNode(scene->mRootNode, scene);
}

void ModelClass::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}


Mesh ModelClass::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<VertexOGL> vertices;
	std::vector<GLuint> indices;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		VertexOGL vertex = VertexOGL();
		LMVector3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0])
		{
			LMVector2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = LMVector2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh(vertices, indices);
}
*/

Mesh::Mesh(std::vector<VertexOGL>& vertices, std::vector<GLuint>& indices)
{
    this->vertices = vertices;
    this->indices = indices;

    this->setupMesh();
}

Mesh::~Mesh()
{

}

OpenGL4Object * Mesh::m_object = nullptr;


void Mesh::Draw()
{
	m_object->glActiveTexture(GL_TEXTURE0);
	m_object->glBindVertexArray(this->VAO);
	m_object->glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	m_object->glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    m_object->glGenVertexArrays(1, &this->VAO);
    m_object->glGenBuffers(1, &this->VBO);
    m_object->glGenBuffers(1, &this->EBO);
	
    m_object->glBindVertexArray(this->VAO);
    m_object->glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    m_object->glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexOGL), &this->vertices[0], GL_STATIC_DRAW);
	
    m_object->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    m_object->glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	
    m_object->glEnableVertexAttribArray(0);
    m_object->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexOGL), (GLvoid*)0);
    m_object->glEnableVertexAttribArray(1);
    m_object->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexOGL), (GLvoid*)offsetof(VertexOGL, Normal));
    m_object->glEnableVertexAttribArray(2);
    m_object->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexOGL), (GLvoid*)offsetof(VertexOGL, TexCoords));
	
	m_object->glBindVertexArray(0);
}

void Mesh::SetObject(const OpenGL4Object & object)
{
	*m_object = object;
}
