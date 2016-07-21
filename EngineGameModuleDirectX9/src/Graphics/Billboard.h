#if !defined(BILLBOARD_H)
#define BILLBOARD_H

#include <string>
using std::string;

#include <d3dx9.h>

#include "../../../EngineGameModel/src/Base/PhysicsObject.h"
#include "../../../EngineGameModel/src/Maths/LMVector4.h"
#include "D3DFVF_D3DVertex.h"
#include "Vertex.h"

enum BillboardAlignment
{
	billboardAlignBottomCentre,
	billboardAlignMiddleCentre,
	billboardAlignmentCount
};

class Billboard
{
protected:
	static LPDIRECT3DDEVICE9 m_device;

	PhysicsObject m_physicsObject;

	D3DXMATRIXA16 m_world;
	D3DXMATRIX m_scale;
	D3DXMATRIX m_rotation;
	D3DXMATRIX m_translation;

	LMVector3 * pos;
	LMVector3 * rot;
	LMVector3 * sca;

	D3DMATERIAL9 m_material;
	LPDIRECT3DTEXTURE9 m_texture = NULL;
	LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer = NULL;

	LMVector4 * m_vertices;

	float m_width, m_height;

public:
	Billboard();
	~Billboard();

	bool Init(LPDIRECT3DDEVICE9 device, string path, BillboardAlignment alignment, float width, float height);

	void Update(float deltaTime);
	void Render();

	PhysicsObject * GetPhysicsObject();

	void SetRadius(float radius);
};

#endif