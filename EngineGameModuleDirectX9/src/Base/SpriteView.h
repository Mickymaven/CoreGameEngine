#if !defined(SPRITEVIEW_H)
#define SPRITEVIEW_H

#include <vector>
using std::vector;

#include <d3dx9.h>

#include "../../../Simple Moba/src/Graphics/GraphicsAlgorithms.h"
#include "../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"

class SpriteView
{
protected:
	static LPDIRECT3DDEVICE9 m_D3D_Device;

	Sprite * m_sprite;
	LMMesh * m_mesh;

	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_rotationMatrix;
	D3DXMATRIX m_translationMatrix;
	D3DXMATRIX m_scaleMatrix;

	LMVector3 * m_pPosition;
	LMVector3 * m_pRotation;
	LMVector3 * m_pScale;

public:
	SpriteView();
	SpriteView(LPDIRECT3DDEVICE9 device, Sprite * sprite, LMMesh * mesh);
	~SpriteView();

	void WorldTransform();
	void virtual Render();

	bool IntersectPoints(vector<LMVector3> * pPointsOut, LMVector3 * point1, LMVector3 * point2);
	bool IsIntersectSprite(vector<LMVector3> * hitPoints, D3DXVECTOR3 point1, D3DXVECTOR3 point2);

	Sprite * GetSprite();
	LMMesh * GetLMMesh();
	D3DXMATRIX * GetWorldMatrix();
};

#endif