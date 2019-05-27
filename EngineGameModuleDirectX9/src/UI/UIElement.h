#if !defined(UIELEMENT_H)
#define UIELEMENT_H

#include <string>
using std::string;


#include "../Application/GlobalsDX9.h"//dont sstatic in device anymore
#include "../../../EngineGameModel/src/Maths/LMVector4.h"
#include "LMGeometry.h"
#include "UIBase.h"

class UIElement : public UIBase
{
protected:
	string m_texturePath;
	
	D3DXMATRIXA16 m_world;
	D3DXMATRIX m_scale;
	D3DXMATRIX m_rotation;
	D3DXMATRIX m_translation;
	
	D3DXMATRIX m_World, m_Scale, m_Rotation, m_Translation;

	D3DMATERIAL9 DefaultMaterial;
	LPDIRECT3DTEXTURE9 UxTexture = NULL;
	LPDIRECT3DVERTEXBUFFER9 MyUX_Buffer = NULL;

	LMVector4 * MyUXVertices;

public:
	UIElement();

	UIElement(float width, float height, string path);//try to depreciate
	UIElement(float width, float height);//Specifically used for derived class GameCursor
	UIElement(float width, float height, LPDIRECT3DTEXTURE9 texture);

	~UIElement();
	
	bool Init(float width, float height, string path);
	bool Init();
	
	void InitMaterial();
	bool InitVertexData();
	bool InitVertexData(float x, float y);

	void Update(float deltaTime);
	void Render();
	void Render(float x, float y, float z);

	//void UseViewAndProjection();
};

#endif