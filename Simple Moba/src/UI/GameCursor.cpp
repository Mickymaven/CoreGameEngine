#include "GameCursor.h"

GameCursor::GameCursor() :UIElement()
{
}

GameCursor::~GameCursor()
{
}

bool GameCursor::Init(float width, float height)
{
	m_width = width;
	m_height = height;

	m_state = gameCursorTypeCursor;
	m_paths.push_back(""); //gameCursorTypeNone (we want paths to match enums but dont make a texture for gameCursorTypeNone 
	m_paths.push_back("Resources/UI/Cursor/Cursor.png"); //gameCursorTypeCursor,
	m_paths.push_back("Resources/UI/Cursor/CursorTypeCameraPan.png"); //gameCursorTypeCameraPan,
	m_paths.push_back("Resources/UI/Cursor/Cursor.png"); //gameCursorTypeTradeInfo,
	m_paths.push_back("Resources/UI/Cursor/CursorTypeInfo.png"); //gameCursorTypeInfo,
	m_paths.push_back("Resources/UI/Cursor/CursorTypeInfoAttack.png"); //gameCursorTypeInfoAttack,

	m_paths.push_back("Resources/UI/Cursor/CursorTypeCastDirectional.png");//gameCursorDirectional,
	m_paths.push_back("Resources/UI/Cursor/CursorTypeCastDirectionalAttack.png");//gameCursorDirectionalAttack,

	m_paths.push_back("Resources/UI/Cursor/CursorTypeCast.png"); //gameCursorTypeCast
	m_paths.push_back("Resources/UI/Cursor/CursorTypeCastAttack.png"); //gameCursorTypeCastAttack,
	m_paths.push_back("Resources/UI/Cursor/CursorTypePoint.png"); //gameCursorTypePoint,
	m_paths.push_back("Resources/UI/Cursor/CursorTypePointAttack.png"); //gameCursorTypePointAttack,

	m_paths.push_back("Resources/UI/Cursor/CursorTypeCooldownCastAttack.png"); //gameCursorTypeCooldownCastAttack,
	m_paths.push_back("Resources/UI/Cursor/CursorTypeCooldownAttack.png"); //gameCursorTypeCooldownAttack,
	m_paths.push_back("Resources/UI/Cursor/CursorTypeCooldownCast.png"); //gameCursorTypeCooldownCast,

	m_paths.push_back("Resources/UI/Cursor/CursorTypeRangeAttack.png");//gameCursorTypeRangeAttack,
	m_paths.push_back("Resources/UI/Cursor/CursorTypeRange.png");//gameCursorTypeRange,

	m_paths.push_back("Resources/UI/Cursor/CursorTypeCastAttackMove.png");//gameCursorTypeAttackMove

	m_paths.push_back("Resources/UI/Cursor/CursorTypeHeal.png"); //gameCursorTypeHeal,
	m_paths.push_back("Resources/UI/Cursor/CursorTypeHealCast.png"); //gameCursorTypeHealCast,
	m_textures.resize(gameCursorTypeCount);

	//we are starting this texture init for loop from one because we dont call render when index is 0
	m_textures.at(0) = nullptr;

	for (int index = 1; index < gameCursorTypeCount; index++)
	{
		m_textures.at(index) = LPDIRECT3DTEXTURE9();

		if (D3DXCreateTextureFromFile(g_D3D_Device, m_paths.at(index).c_str(), &m_textures.at(index) ) != D3D_OK)
		{
			//MessageBox(NULL, "Bad texture; ", "Error", MB_OK);	return false
			OutputDebugString("Bad texture (GameCursor.cpp)\n");
		}
	}
	
	InitMaterial();

	return InitVertexData();

	return true;
}

void GameCursor::Update(float delaTime)
{
	//GameCursorTypes WhichCursorShouldIShow(MobaState * gameState);


	UxTexture = m_textures.at(m_state);

}

void GameCursor::Render()
{
	if (m_state == gameCursorTypeNone) return;
	else if (m_state == gameCursorTypeCameraPan)
	{
		UIElement::Render((float)g_mouseClientPosition.x - m_width / 2.0f, 0.0f, (float)g_mouseClientPosition.y - m_height / 2.0f);
	}
	else UIElement::Render((float)g_mouseClientPosition.x, 0.0f, (float)g_mouseClientPosition.y);
}

GameCursorTypes GameCursor::GetState() { return m_state; }

void GameCursor::SetState(GameCursorTypes cursorType)
{
	m_state = cursorType;
}