#include "LMMesh.h"
#include <iostream>
#include <string>
#include <d3dx9.h>

LMMesh::LMMesh ()
{

}

LMMesh::LMMesh (string path, string model, LPDIRECT3DDEVICE9 device)
{
	m_customMaterial = NULL;
	m_isMaterialRand = false;
	LoadIt(path, model, device);
}

LMMesh::LMMesh(string path, string model, LPDIRECT3DDEVICE9 device, D3DMATERIAL9 * customMaterial, bool isRand)
{
	m_customMaterial = NULL;
	m_isMaterialRand = false;

	CustomMaterial(customMaterial, isRand);
	LoadIt(path, model, device);
}

void LMMesh::LoadIt(string path, string model, LPDIRECT3DDEVICE9 device)
{
	m_filePath = model;
	m_dirPath = path;

	//string pinky = "pinky.x";
	//if (!model.compare(pinky)) OutputDebugString("pinky init");

	m_MeshInitialRotation = LMVector3(0.0f, 0.0f, 0.0f);
	m_MeshInitialScale =  LMVector3(1.0f, 1.0f, 1.0f);

	/*
	LPD3DXMESH = m_Mesh;

	float * m_HitTestRadius; // units ?

	LPDIRECT3DDEVICE9 m_D3D_Device;
	LPD3DXBUFFER m_MaterialBuffer;
	D3DMaterial9 * m_MaterialList;
	LPDIRECT3DTEXTURE9 m_TextureList;

	*/
	m_D3D_Device = device;

	m_MaterialBuffer = NULL;//to init
	m_MaterialList = NULL;//to init
	m_MaterialCount = NULL;//to init
	m_TextureList = NULL;//to init
	m_Mesh = NULL;//to init

	m_InitialHitTestRadius = 1.0f;//at least any sized model can collide a bit (doing this stuff later)


	// .X file loading

	const char * temp_C = (path+model).c_str();

	//test load
	if (FAILED(
		D3DXLoadMeshFromX(temp_C, D3DXMESH_SYSTEMMEM, m_D3D_Device, NULL, &m_MaterialBuffer, NULL, &m_MaterialCount, &m_Mesh)
		)
		)
	{
		//Error
		//MessageBox(NULL, "Couldnt load .x LMMesh.cpp", "Opps!", MB_OK);
		OutputDebugString("Couldnt load .x LMMesh.cpp");
		return;
	}
	//m_mesh initialised from .x file


	//GET FVF of model!

	DWORD fvf = m_Mesh->GetFVF();


	ID3DXMesh * myMesh;
	if (FAILED(
		m_Mesh->CloneMeshFVF(0, fvf, m_D3D_Device, &myMesh)
		)
		)
	{
		//Are you fucking kidding me
		MessageBox(NULL, "Couldnt load fvf of model LMMesh.ccp", "Opps!", MB_OK);
	}
	else
	{
		m_Mesh = myMesh;

		//code to make raycast work

		LPDIRECT3DVERTEXBUFFER9 pVB;
		LPDIRECT3DINDEXBUFFER9 pIB;


		m_Mesh->GetIndexBuffer(&pIB);
		m_Mesh->GetVertexBuffer(&pVB);

		pIB->Lock(0, 0, (void**)&m_pIndices, 0);
		pVB->Lock(0, 0, (void**)&m_pVertices, 0);
	}

	//do stuff with fvf model

	if (FAILED(
		D3DXComputeNormals(m_Mesh, NULL)
		)
		)
	{
		//hope this doesnt happen ever
		MessageBox(NULL, "Couldnt compute model normals LMMesh.ccp", "Opps!", MB_OK);
	}

	//Materials stuff
	m_MaterialList = new D3DMATERIAL9[m_MaterialCount];
	m_TextureList = new LPDIRECT3DTEXTURE9[m_MaterialCount];

	D3DXMATERIAL* matMaterials = (D3DXMATERIAL*)m_MaterialBuffer->GetBufferPointer();

	char materialTexturePath[500];
	LPSTR lpMaterialTexturePath = materialTexturePath;

	for (DWORD i = 0; i < m_MaterialCount; i++)
	{
		if (matMaterials[i].pTextureFilename == NULL)
		{
			materialTexturePath[0] = '\0';
		}
		else if (matMaterials[i].pTextureFilename == "")
		{
			materialTexturePath[0] = '\0';
		}
		else
		{
			strcpy_s(materialTexturePath, m_dirPath.c_str());
			strcat_s(materialTexturePath, matMaterials[i].pTextureFilename);
		}

		m_MaterialList[i] = matMaterials[i].MatD3D;
		m_MaterialList[i].Ambient = m_MaterialList[i].Diffuse;

		//m_MaterialList[i].Ambient;
		//m_MaterialList[i].Diffuse;
		//m_MaterialList[i].Emissive;
		//m_MaterialList[i].Power;
		//m_MaterialList[i].Specular;

		//DDS Texture loading (or whatever is in the dot x file) into TextureList
		
		if (FAILED(
			D3DXCreateTextureFromFile(m_D3D_Device, lpMaterialTexturePath, &m_TextureList[i])
			))
		{
			// so we can stuff have models without files
			m_TextureList[i] = NULL;

			ZeroMemory(&m_MaterialList[i], sizeof(D3DMATERIAL9));

			m_MaterialList[i].Diffuse.r = m_MaterialList[i].Ambient.r = 0.3f;
			m_MaterialList[i].Diffuse.g = m_MaterialList[i].Ambient.g = 0.3f;
			m_MaterialList[i].Diffuse.b = m_MaterialList[i].Ambient.b = 0.3f;
			m_MaterialList[i].Specular.r = 0.30f;
			m_MaterialList[i].Specular.g = 0.30f;
			m_MaterialList[i].Specular.b = 0.30f;
			m_MaterialList[i].Power = 4.0f;
			
		}
		else
		{
			if (m_isMaterialRand)
			{
				OutputDebugString("Rand materials.\n");
				m_MaterialList[i].Diffuse.r = m_MaterialList[i].Ambient.r = (rand() % 100)*1.0f;
				m_MaterialList[i].Diffuse.g = m_MaterialList[i].Ambient.g = (rand() % 100)*1.0f;
				m_MaterialList[i].Diffuse.b = m_MaterialList[i].Ambient.b = (rand() % 100)*1.0f;
				m_MaterialList[i].Specular.r = (rand() % 100)*1.0f;
				m_MaterialList[i].Specular.g = (rand() % 100)*1.0f;
				m_MaterialList[i].Specular.b = (rand() % 100)*1.0f;
				m_MaterialList[i].Power = (rand() % 100)*1.0f;
				m_MaterialList[i];
			}

			else if (m_customMaterial != NULL)
			{
				//OutputDebugString("WE ARE IN MATERIALS FOR GROUND");
				m_MaterialList[i].Diffuse.r = m_MaterialList[i].Ambient.r = m_customMaterial->Ambient.r;
				m_MaterialList[i].Diffuse.g = m_MaterialList[i].Ambient.g = m_customMaterial->Ambient.g;
				m_MaterialList[i].Diffuse.b = m_MaterialList[i].Ambient.b = m_customMaterial->Ambient.b;
				m_MaterialList[i].Specular.r = m_customMaterial->Specular.r;
				m_MaterialList[i].Specular.g = m_customMaterial->Specular.g;
				m_MaterialList[i].Specular.b = m_customMaterial->Specular.b;
				m_MaterialList[i].Power = m_customMaterial->Power;
			}
			else
			{
				//OutputDebugString("\nWE got a  texture from .x material i\n");
				m_MaterialList[i].Diffuse.r = m_MaterialList[i].Ambient.r = 0.5f;
				m_MaterialList[i].Diffuse.g = m_MaterialList[i].Ambient.g = 0.5f;
				m_MaterialList[i].Diffuse.b = m_MaterialList[i].Ambient.b = 0.5f;
				m_MaterialList[i].Specular.r = 0.35f;
				m_MaterialList[i].Specular.g = 0.35f;
				m_MaterialList[i].Specular.b = 0.35f;
				m_MaterialList[i].Power = 5.0f;
			}
		}
	}
}

LMMesh::LMMesh(string path, string model, LPDIRECT3DDEVICE9 device, int i)
{
	m_D3D_Device = device;

	m_InitialHitTestRadius = 3.141592654f;

	const char * temp_C = model.c_str();

	if (strcmp(temp_C, "SPHERE"))
	{
		if (FAILED(D3DXCreateSphere(m_D3D_Device, 1.0f, NULL, NULL, &m_Mesh, NULL)))
			MessageBox(NULL, "Couldnt generate a sphere mesh", "Opps!", MB_OK);
	}

	m_MaterialCount = 1;

	m_MaterialList = new D3DMATERIAL9[m_MaterialCount];
	m_TextureList = new LPDIRECT3DTEXTURE9[m_MaterialCount];

	m_TextureList[0] = NULL;

	ZeroMemory(&m_MaterialList[0], sizeof(D3DMATERIAL9));
	m_MaterialList[0].Diffuse.r = m_MaterialList[0].Ambient.r = 0.5f;
	m_MaterialList[0].Diffuse.g = m_MaterialList[0].Ambient.g = 0.5f;
	m_MaterialList[0].Diffuse.b = m_MaterialList[0].Ambient.b = 0.5f;
	m_MaterialList[0].Specular.r = 0.4f;
	m_MaterialList[0].Specular.g = 0.4f;
	m_MaterialList[0].Specular.b = 0.4f;
	m_MaterialList[0].Power = 7.0f;
}

void LMMesh::operator=(const LMMesh & m)
{
	m_customMaterial = m.m_customMaterial;
	m_isMaterialRand = m.m_isMaterialRand;

	CustomMaterial(m_customMaterial, m_isMaterialRand);
	LoadIt(m.m_dirPath, m.m_filePath, m.m_D3D_Device);
}

LMMesh::~LMMesh()
{
	delete[] m_MaterialList;
	delete[] m_TextureList;
}

void LMMesh::CustomMaterial(D3DMATERIAL9 * material, bool isRand)
{
	if (material == NULL)OutputDebugString("material was null");
	m_customMaterial = material;
	m_isMaterialRand = isRand;
}

LPD3DXMESH LMMesh::GetMesh()
{
	if (m_Mesh != NULL)
	{
		return m_Mesh;
	}

	return NULL;
}

/*
D3DXVECTOR3 LMMesh::GetMeshInitialRotation()
{
		return * m_MeshInitialRotation;
}

D3DXVECTOR3 LMMesh::GetMeshInitialScale()
{
	return * m_MeshInitialScale;
}
*/

float LMMesh::GetInitialHitTestRadius()
{
	return m_InitialHitTestRadius;
}

DWORD LMMesh::GetMaterialCount()
{
	return m_MaterialCount;
}

D3DMATERIAL9 * LMMesh::GetMaterial(int i)
{
	return & m_MaterialList[i];
}

LPDIRECT3DTEXTURE9 LMMesh::GetTexture(int i)
{
	return m_TextureList[i];
}

LPDIRECT3DDEVICE9 LMMesh::GetDevice()
{
	return m_D3D_Device;
}