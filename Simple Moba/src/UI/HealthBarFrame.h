#if !defined(HEALTHBARFRAME_H)
#define HEALTHBARFRAME_H

#include <d3dx9.h>

#include "../../../EngineGameModel/src/Base/PhysicsObject.h"
#include "../../../EngineMoba/src/Actors/Actor.h"
#include "../../../EngineGameModuleDirectX9/src/ControlHeader.h"

class HealthBarFrame
{
private:
	float x, y, multFactor, m_interfaceScale;

	D3DXMATRIXA16 m_world;
	D3DXMATRIX m_scale;
	D3DXMATRIX m_rotation;
	D3DXMATRIX m_translation;

	PhysicsObject m_physicsObject;

	D3DMATERIAL9 m_Material;
	//LPDIRECT3DTEXTURE9 m_Texture = NULL;

	LPDIRECT3DTEXTURE9 m_HealthFrameTeam;
	LPDIRECT3DTEXTURE9 m_HealthFrameOpponent;

	LPDIRECT3DVERTEXBUFFER9 m_Vertex_Buffer;

	LMVector4 * m_Vertices;

	PhysicsObject m_physicsObjectHealth;

	D3DMATERIAL9 m_MaterialHealth;
	LPDIRECT3DTEXTURE9 m_TextureHealthTeam;
	LPDIRECT3DTEXTURE9 m_TextureHealthOpponent;
	LPDIRECT3DVERTEXBUFFER9 m_Vertex_BufferHealth;

	LMVector4 * m_VerticesHealth;

	LPD3DXMESH m_nameText;
	D3DMATERIAL9 m_nameMaterial;
	HDC deviceContext;
	HFONT my3dfont;

	Actor * m_owner;

public:
	HealthBarFrame();
	~HealthBarFrame();

	bool Init(Actor * owner);
	void Update(float deltaTime, float healthPercent);
	void Render(bool isFriendly);

	PhysicsObject * GetPhysicsObject() { return &m_physicsObject; }

	void SetScale(float scale) { m_interfaceScale = scale; }
};


#endif
