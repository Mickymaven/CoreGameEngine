#include "UICharacterPanelMini.h"

UICharacterPanelMini::UICharacterPanelMini()
{
}

UICharacterPanelMini::~UICharacterPanelMini()
{
}

bool UICharacterPanelMini::Init(ViewProfile * viewProfile,
	ThemeResources * themeResources,
	MobaState * gameState,
	vector<InputModel*> * inputModels,
	PlayerCharacterController * initCharControl)
{
	m_gameState = gameState;
	m_viewProfile = viewProfile;
	m_theme = themeResources;
	m_viewProfile = viewProfile;
	

	if (!InitAvatarElement(&m_avatar, characterGrey)) return false;


		
		
		
	m_avatar.SetWidth(( 0.5f * 160/1920)*1600.0f);//4 5/7 * 1600
	m_avatar.SetHeight(( 0.5f * 160/1200)*900.0f);//4 6/8 * 900;

		
	//m_viewProfile->m_aspectProfile->GetWidthForElement(gameElementPlayerAvatar),
	//m_viewProfile->m_aspectProfile->GetHeightForElement(gameElementPlayerAvatar),

	m_avatar.GetPosition()->x = 0.0f * 1600.0f;// m_viewProfile->m_aspectProfile->GetXForElement(gameElementPlayerAvatar);
	m_avatar.GetPosition()->z = 0.859f * 900.0f;// m_viewProfile->m_aspectProfile->GetYForElement(gameElementPlayerAvatar);


	/*
gameElementPlayerAvatar
0.0
0.0
0.322
0.859
1.0
160
160
1920
1200
	*/
	


	if (!InitHealthBar()) return false;

	return true;
}

bool UICharacterPanelMini::InitHealthBar()
{
	float i, j;


	m_xorigin = 0.18f*  1600.0f///m_viewProfile->m_aspectProfile->GetAlignX(gameElementHealthBar)
		+ -0.095 * 1600.0f;//m_viewProfile->m_aspectProfile->GetXForElement(gameElementHealthBar);

	i= 1.0f * 900.0f;//m_viewProfile->m_aspectProfile->GetAlignY(gameElementHealthBar) +
	j= -0.084f * 900.f;//m_viewProfile->m_aspectProfile->GetYForElement(gameElementHealthBar);

	m_y = i + j;


	

			/*
gameElementHealthBar
0.5boundsHorizontalAlign,
1.0boundsVerticalAlign,
-0.095boundsPartPositionX,
-0.084boundsPartPositionY,
1.0	boundsScale,
480.0boundsImageWidth,
45.0boundsImageHeight,
1920boundsResWidth,7888
1200boundsResHeight,



	*/


	LPDIRECT3DTEXTURE9 tex;
	if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/misc/HealthBar_texture.png", &tex) != D3D_OK)
		return false;
	m_hpbar = UIResizableElement(
		( 0.5f * 480.0f / 1920.0f ) * 1280.0f,
		( 0.5f * 45.0f / 1200.0f ) * 720.0f,

		/*
		m_viewProfile->m_aspectProfile->GetWidthForElement(gameElementHealthBar), (4 * 5/7)* 1280
		m_viewProfile->m_aspectProfile->GetHeightForElement(gameElementHealthBar),(4*6/8)* 720//0.0313f * g_clientSizeRect->bottom,*/
		PhysicsObject(
			LMVector3(0.0f, 0.0f, m_y),		//Position
			LMVector3(0.0f, 0.0f, 0.0f),	//Rotation
			LMVector3(1.0f, 1.0f, 1.0f),	//Scale
			LMVector3(0.0f, 0.0f, 0.0f),	//Velocity
			LMVector3(0.0f, 0.0f, 0.0f),	//Spin
			LMVector3(0.0f, 0.0f, 0.0f),	//Resize
			0.0f),
		tex);


	m_hpbar.InitMaterial();
	if (!m_hpbar.InitVertexData()) return false;

	return true;
}

void UICharacterPanelMini::Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView)
{

	UICharacterPanel::UpdateHP(deltaTime, playerCharacterController, playerCharacterView);
}

void UICharacterPanelMini::Render()
{
	m_hpbar.Render();
	m_avatar.Render();
}
