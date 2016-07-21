#include "MenuScene.h"

D3DXMATRIXA16 MenuScene::m_world;
D3DXMATRIX MenuScene::m_scale;
D3DXMATRIX MenuScene::m_rotation;
D3DXMATRIX MenuScene::m_translation;

LMCamera * MenuScene::m_uicamera = NULL;

UIElement * MenuScene::m_sharedBackground = NULL;

MenuScene::MenuScene(MenuSceneSelection selfSceneEnum, string name, LMCamera * cam)
{
	if (m_sharedBackground == NULL)
	{
		m_sharedBackground = new UIElement((float)g_clientSizeRect->right, (float)g_clientSizeRect->bottom, "Resources/Client/Intro/intro-back-dev.png");

		if (!m_sharedBackground->Init()) MessageBox(NULL, "Cant Load Texture", "Error", MB_OK);
		m_sharedBackground->GetPosition()->x = 0.0f;
		m_sharedBackground->GetPosition()->x = 0.0f;
	}

	if (m_uicamera == NULL) m_uicamera = cam;

	m_nextScene = selfSceneEnum;
}

MenuScene::~MenuScene()
{

}

void MenuScene::Update(float fDeltaTime)
{
	MessageBox(NULL, "MenuScene::Update base class virtual called instead of derived class..", "Error", MB_OK);

}

void MenuScene::Render()
{
	MessageBox(NULL, "MenuScene::Render base class virtual called instead of derived class..", "Error", MB_OK);

}

void MenuScene::OnEnterScene()
{
	MessageBox(NULL, "MenuScene::OnEnterScene base class virtual called instead of derived class..", "Error", MB_OK);
}

GameConfiguration * MenuScene::GetTestGameConfig(int i)
{
	m_gameConfig = GameConfiguration(gameMapBarebones, "Forest", modeStandard);

	m_gameConfig.AddPlayer("Butter", characterNenian, yellowTeamName, 1, abilityHiddenPower, abilityElixirBurst);
	m_gameConfig.AddPlayer("Lemon", characterSurku, yellowTeamName, 2, abilityHiddenPower, abilityElixirBurst);
	m_gameConfig.AddPlayer("Gold", characterGrey, yellowTeamName, 3, abilityHiddenPower, abilityElixirBurst);
	m_gameConfig.AddPlayer("Amber 2", characterGrey, yellowTeamName, 4, abilityHiddenPower, abilityElixirBurst);
	m_gameConfig.AddPlayer("Cheese", characterGrey, yellowTeamName, 5, abilityHiddenPower, abilityElixirBurst);

	m_gameConfig.AddPlayer("Lavender", characterSurku, purpleTeamName, 6, abilityEternalLight, abilityElixirBurst);
	m_gameConfig.AddPlayer("Violet", characterSurku, purpleTeamName, 7, abilityEternalLight, abilityElixirBurst);
	m_gameConfig.AddPlayer("Lilac", characterShork, purpleTeamName, 8, abilityEternalLight, abilityElixirBurst);
	m_gameConfig.AddPlayer("Mauve", characterShork, purpleTeamName, 9, abilityEternalLight, abilityElixirBurst);
	m_gameConfig.AddPlayer("Grape", characterShork, purpleTeamName, 10, abilityEternalLight, abilityElixirBurst);

	return &m_gameConfig;
}
