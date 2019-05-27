#if !defined(LMMESH_H)
#define LMMESH_H

#include <string>
using std::string;

#include <d3d9.h>
#include <d3dx9.h>

#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../UI/LMGeometry.h"
#include "D3D9Vertex_UnlitTextured.h"

class LMMesh
{
private:
	string m_dirPath;
	string m_filePath;

	LPD3DXMESH m_Mesh;
	LMVector3 m_MeshInitialRotation;
	LMVector3 m_MeshInitialScale;
	float m_InitialHitTestRadius;
	
	LPDIRECT3DDEVICE9 m_D3D_Device;
	LPD3DXBUFFER m_MaterialBuffer;
	DWORD m_MaterialCount;
	D3DMATERIAL9 * m_MaterialList;
	LPDIRECT3DTEXTURE9 * m_TextureList;

	D3DMATERIAL9 * m_customMaterial;
	bool m_isMaterialRand;

	WORD * m_pIndices;
	D3D9Vertex_UnlitTextured * m_pVertices;


public:

	LMMesh();
	LMMesh(string path, string model, LPDIRECT3DDEVICE9 device);
	LMMesh(string path, string model, LPDIRECT3DDEVICE9 device, D3DMATERIAL9 * customMaterial, bool isRand);
	LMMesh(string path, string model, LPDIRECT3DDEVICE9 device, int i);

	void operator = (const LMMesh &m);

	void LoadIt(string path, string model, LPDIRECT3DDEVICE9 device);
	virtual ~LMMesh();

	void CustomMaterial(D3DMATERIAL9 * customMaterial, bool isRand);

	//accessors
	LPD3DXMESH GetMesh();

	//LMVector3 * GetMeshInitialRotation();
	//LMVector3 * GetMeshInitialScale();
	float GetInitialHitTestRadius();
	WORD * GetIndiceBuffer() { return m_pIndices; };
	D3D9Vertex_UnlitTextured * GetVertexBuffer() { return m_pVertices; };


	//LPD3DXBUFFER GetMaterialBuffer();
	DWORD GetMaterialCount();
	D3DMATERIAL9 * GetMaterial(int i);
	LPDIRECT3DTEXTURE9 GetTexture(int i);

	LPDIRECT3DDEVICE9 GetDevice();


};

#endif
