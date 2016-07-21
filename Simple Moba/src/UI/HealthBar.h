#if !defined(HEALTHBAR_H)
#define HEALTHBAR_H

#include <d3dx9.h>


#include "../../../EngineGameModel/src/Base/PhysicsObject.h"
#include "../../../EngineGameModel/src/Maths/LMVector2.h"

#include "../../../EngineMoba/src/Actors/Actor.h"
#include "../../../EngineMoba/src/Actors/VitalEntity.h"

#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIResizableElement.h"
#include "../../../EngineGameModuleDirectX9/src/ControlHeader.h"

#include "../Graphics/GraphicsAlgorithms.h"

#include "../../../EngineGameModuleDirectX9/src/Application/Globals.h"

class HealthBar
{
private:
	char buffer[1000];
	VitalEntity * m_owner;

	LMVector2 m_position;
	bool m_tempIsFriendly;
	bool m_visibility;
	
	bool * m_healthMirrorOnPointer;
	LPD3DXFONT m_font;
	D3DCOLOR * m_fontColor;
	RECT m_fontPosition;

	UIElement m_frameFriendly;
	UIResizableElement m_healthFriendly;

	UIElement m_frameOpponent;
	UIResizableElement m_healthOpponent;



	//Every Update stuff
	D3DXVECTOR2 myVector;
	float subValue;
	float direction1;
	float direction2;
	UIResizableElement * healthbar;


	float crunchpc;
	float pcDownScreen;

	float scalex;
	UIElement * FrameForTeam;


	//font
	LPD3DXMESH m_nameText;
	D3DMATERIAL9 m_nameMaterial;
	HDC deviceContext;
	HFONT my3dfont;
	D3DXMATRIXA16 m_world;
	D3DXMATRIX m_scale;
	D3DXMATRIX m_rotation;
	D3DXMATRIX m_translation;
	D3DXMATRIX localtrans;
	
public:
	HealthBar();
	HealthBar(
		LPDIRECT3DTEXTURE9 friendlyFrameTexture,
		LPDIRECT3DTEXTURE9 friendlyHealthTexture,
		LPDIRECT3DTEXTURE9 opponentFrameTexture,
		LPDIRECT3DTEXTURE9 opponentHealthTexture,
		bool * isHealthMirrorOn,
		LPD3DXFONT font,
		D3DCOLOR * fontColor
		);
	~HealthBar();

	bool Init(VitalEntity * owner);
	bool Init3DNamesForActors(Actor * owner);
	void Update(float deltaTime, LMCamera * camera, float healthPercent, bool isFriendly, int ci);
	void Render();
	void RenderName(bool is3d);
	void RenderName3d();

};


#endif