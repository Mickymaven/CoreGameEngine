#include "UICharacterPanel.h"

const int UICharacterPanel::elementIDs[] =
{
	gameElementAbility1,
	gameElementAbility2,
	gameElementAbility3,
	gameElementAbility4,
	gameElementAbilityCustom1,
	gameElementAbilityCustom2,
	gameElementAbilityRecall,
	gameElementAbilitySleep
};

UICharacterPanel::UICharacterPanel()
{
}

UICharacterPanel::~UICharacterPanel()
{
}

bool UICharacterPanel::Init(
	ViewProfile * viewProfile,
	ThemeResources * themeResources,
	MobaState * gameState,
	TooltipController * tooltipController,
	vector<InputModel*> * inputModels,
	PlayerCharacterController * initCharControl)
{
	m_gameState = gameState;
	m_tooltipController = tooltipController;
	m_viewProfile = viewProfile;
	m_theme = themeResources;

	//init character abilities icons vector

	//player abilities
	



	


	if (!m_abilityIcon.Init(
		viewProfile->m_aspectProfile->GetWidthForElement(gameElementAbility1),
		viewProfile->m_aspectProfile->GetWidthForElement(gameElementAbility1),
		"Resources/UI/Buffs/MotoCrash.png"
		)) return false;
	



	m_characterAbilities.resize(initCharControl->GetCharacter()->GetAbilities()->size()-1);
	for (unsigned int i = 0; i < m_characterAbilities.size(); i++)
	{
		m_characterAbilities.at(i).SetMouseOverCallback(
			std::bind(&TooltipController::ActivateTooltipAbility, m_tooltipController, _1, _2, _3));

		m_characterAbilities[i].SetIcon(&m_abilityIcon);
	}
	SetAbilityPositions(viewProfile);

	//init ability hotkey labels

	m_bindLabels.resize(8);

	CharacterAction elementText[] =
	{
		characterActionCastAbility1,
		characterActionCastAbility2,
		characterActionCastAbility3,
		characterActionCastAbility4,
		characterActionCastAbility5,
		characterActionCastAbility6,
		characterActionCastRecall,
		characterActionCastSleep,
	};

	
	for (unsigned int i = 0; i < 8; i++)
	{
		if (!viewProfile->InitRelativeLabel(elementIDs[i], &m_bindLabels[i], &themeResources->m_smallText, 20.0f, 13, 1.0f, 1.0f)) return false;
		m_bindLabels[i].SetText(
			GetInputDefineString(
				inputModels->at(7)->m_keybinds[elementText[i]]
				).c_str()
			
			);
	}


	//init cooldown text labels
	m_cooldownLabels.resize(8);
	for (unsigned int i = 0; i < 8; i++)
	{
		if (!viewProfile->InitRelativeLabel(
			elementIDs[i],//int elementID,
			&m_cooldownLabels[i],//UILabelCstr * label,
			&themeResources->m_abilityCooldownText,//FontGroup * fontGroup,
			75.0f, 50.0f,//float w, float h,
			0.25f, 0.5f//float top, float left

			)) return false;
		
		m_cooldownLabels[i].Init(*m_cooldownLabels[i].GetBounds(), &themeResources->m_abilityCooldownText, &themeResources->m_abilityCooldownBelowText, 1.0f);

		//m_cooldownLabels[i].SetFloatFormat(3, 0);
	}


	//init avatar
	if (!InitAvatarElement(&m_avatar, characterGrey)) return false;



	//init hpbar
	//if (!viewProfile->InitElement(gameElementHUD, &m_playergui)) return false;



	//hppc = 0.284585f;
	//hpwidth = hppc * g_clientSizeRect->right;

	m_xorigin = m_viewProfile->m_aspectProfile->GetAlignX(gameElementHealthBar) 
		+ m_viewProfile->m_aspectProfile->GetXForElement(gameElementHealthBar);
													//g_clientSizeRect->right*(0.3881422f + 0.5f*hppc) - 0.5f*hpwidth;
	m_y = m_viewProfile->m_aspectProfile->GetAlignY(gameElementHealthBar) +
		+ m_viewProfile->m_aspectProfile->GetYForElement(gameElementHealthBar);

	LPDIRECT3DTEXTURE9 tex;
	if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/misc/HealthBar_texture.png", &tex) != D3D_OK)
		return false;
	m_hpbar = UIResizableElement(
		m_viewProfile->m_aspectProfile->GetWidthForElement(gameElementHealthBar),
		m_viewProfile->m_aspectProfile->GetHeightForElement(gameElementHealthBar),//0.0313f * g_clientSizeRect->bottom,
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

	//init stats labels
	if (!m_stats.Init(viewProfile, themeResources, gameState, tooltipController, initCharControl)) return false;
	return true;
}

bool UICharacterPanel::InitAvatarElement(UIElement * uiElement, CharacterClassName characterClass)
{
	*uiElement = UIElement(
		m_viewProfile->m_aspectProfile->GetWidthForElement(gameElementPlayerAvatar),
		m_viewProfile->m_aspectProfile->GetHeightForElement(gameElementPlayerAvatar),
		m_viewProfile->m_themeResourceProfile->GetAvatarPaths()->at(characterClass));

	if (!uiElement->Init()) return false;

	uiElement->GetPosition()->x = m_viewProfile->m_aspectProfile->GetXForElement(gameElementPlayerAvatar);
	uiElement->GetPosition()->z = m_viewProfile->m_aspectProfile->GetYForElement(gameElementPlayerAvatar);

	return true;
}

void UICharacterPanel::Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView)
{
	SetAbilities(playerCharacterView);

	m_stats.Update(deltaTime, playerCharacterController->GetCharacter()->GetActor()->GetStats());

	//update hp bar
	float scale = 0.0f;
	if (playerCharacterController->GetCharacter()->GetActor()->GetStats()->m_maxHealth > 0)
	{
		scale = playerCharacterController->GetCharacter()->GetActor()->GetStats()->m_health
			/ playerCharacterController->GetCharacter()->GetActor()->GetStats()->m_maxHealth;
	}//maybe if you get 100 to 0'd bc you're a scrub your hp bar might show 100?
	 //TODO health bar goes down with a velocity (even though most damage is damage over time).
	 //this way less things can be damage over time and i get the smooth hp bar thing.

	m_hpbar.GetPhysicsObject()->GetScale()->x = scale;
	m_hpbar.GetPhysicsObject()->GetPosition()->x = m_xorigin - 0.5f*(1.0f - scale);


	float cdValue = 0.0f;
	//update cooldown text
	for (unsigned int i = 0; i < 8; i++)
	{

		if (i == 6)//pos of recall ability in vector
		{
			if (m_gameState->GetControlledActor()->GetState() == actorRecall)
			{
				cdValue = ((Recall*)m_gameState->GetControlledCharacter()->GetAbilities()->at(actionCastRecall))->GetRecallTimer()->GetRemainder();
			}

			//make sure recall cd label goes away
			else
			{
				cdValue = 0.0f;//not on recall t
				m_cooldownLabels[i].UILabelCstr::SetText("");
			}
		}

		//all non cooldown Cooldowns
		else cdValue = m_gameState->GetControlledCharacter()->GetAbilities()->at(i+1)->GetCooldownRemaining(*m_gameState->GetGameElapsedTime());

		if (cdValue > 0.0f)
		{
			m_cooldownLabels[i].SetText(cdValue);
		}
		else m_cooldownLabels[i].UILabelCstr::SetText("");
	}
}

void UICharacterPanel::Render()
{
	m_hpbar.Render();
	m_avatar.Render();
	m_stats.Render();
	
	for (unsigned int i = 0; i < m_characterAbilities.size(); i++)
	{
		m_characterAbilities[i].Render();
		m_cooldownLabels[i].Render();
	}

	for (unsigned int i = 0; i < m_bindLabels.size(); i++)
	{
		m_bindLabels[i].Render();
	}

}

void UICharacterPanel::SetAbilityPositions(ViewProfile * viewProfile)
{
	RECT * eleBounds = nullptr;
	LMVector3 * pos=nullptr;
	int elementID = 0;


	for (unsigned int i = 0; i < m_characterAbilities.size(); i++)
	{
		elementID = elementIDs[i];

		eleBounds = m_characterAbilities[i].GetBounds();
		pos = m_characterAbilities[i].GetPosition();


		eleBounds->left = viewProfile->m_aspectProfile->GetAlignX(elementID) + viewProfile->m_aspectProfile->GetXForElement(elementID);
		eleBounds->top = viewProfile->m_aspectProfile->GetAlignY(elementID) + viewProfile->m_aspectProfile->GetYForElement(elementID);
		eleBounds->right = viewProfile->m_aspectProfile->GetAlignX(elementID) + viewProfile->m_aspectProfile->GetXForElement(elementID) + viewProfile->m_aspectProfile->GetWidthForElement(elementID);
		eleBounds->bottom = viewProfile->m_aspectProfile->GetAlignY(elementID) + viewProfile->m_aspectProfile->GetYForElement(elementID) + viewProfile->m_aspectProfile->GetHeightForElement(elementID);



		pos->x = eleBounds->left;
		pos->z = eleBounds->top;


	}

	/*



	//if (!viewProfile->InitElement(gameElementHUD, &m_playergui)) return false;

	float rowTop = 0.0f;
	float elementLeft = 0.0f;
	LMVector3 * pos = NULL;
	RECT * eleBounds = NULL;
	float eleWidth = 0.0f;
	float eleHeight = 0.0f;



	int initLeft = 0.377*g_clientSizeRect->right;
	int squareWidth = 0.04296875f * g_clientSizeRect->right;
	m_afLeft = { initLeft, (LONG)(g_clientSizeRect->bottom - 121.0f), initLeft + squareWidth, g_clientSizeRect->bottom };//(0.881f*g_clientSizeRect->bottom

	rowTop = (LONG)(g_clientSizeRect->bottom - 121.0f);//902 = (0.881f*g_clientSizeRect->bottom
	elementLeft = initLeft;



	for (unsigned int i = 0; i < m_characterAbilities.size(); i++)
	{
		if (i == abilitySlotRecall - 1)
		{
			rowTop = (LONG)(0.96f*g_clientSizeRect->bottom);
			elementLeft = 0.3f*g_clientSizeRect->right;

		}


		m_characterAbilities.at(i).SetWidth(squareWidth);
		m_characterAbilities.at(i).SetHeight(squareWidth);

		eleWidth = m_characterAbilities.at(i).GetWidth();
		eleHeight = m_characterAbilities.at(i).GetHeight();
		pos = m_characterAbilities.at(i).GetPosition();
		eleBounds = m_characterAbilities.at(i).GetBounds();

		eleBounds->left = elementLeft;
		eleBounds->top = rowTop;
		eleBounds->bottom = rowTop + eleHeight;
		eleBounds->right = elementLeft + eleWidth;

		pos->x = elementLeft;
		pos->z = rowTop;

		elementLeft += squareWidth;


	}
	*/

}

void UICharacterPanel::SetAbilities(PlayerCharacterView * playerCharacterView)
{
	//TODO find place to update selected Player Controller;*************

	//playerCharacterView->GetAbilityViews()->

	for (unsigned int i = 1; i < playerCharacterView->GetCharacterView()->GetAbilityViews()->size(); i++)
	{
		m_characterAbilities.at(i - 1).SetAbility(playerCharacterView->GetPlayerCharacterController()->GetCharacter()->GetAbilities()->at(i));
		m_characterAbilities.at(i - 1).SetAbilityView(playerCharacterView->GetCharacterView()->GetAbilityViews()->at(i));
	}
}


int UICharacterPanel::SelectFromAbilities(POINT * p)
{
	for (int i = 0; i < m_characterAbilities.size(); i++)
	{
		if (m_characterAbilities.at(i).GetAbility() != NULL)
		{
			if (m_characterAbilities.at(i).IsPointInBounds(p)) return i+1;
		}
	}

	return -1;
}

void UICharacterPanel::Select(POINT * p)
{

	

}

void UICharacterPanel::AltSelect(POINT * p)
{
}

bool UICharacterPanel::MouseOver(POINT * p)
{
	for (unsigned int i = 0; i < m_characterAbilities.size(); i++)
	{
		if (m_characterAbilities.at(i).GetAbility() != NULL)
		{
			if (m_characterAbilities.at(i).MouseOver(p)) return true;
		}
	}

	return false;
}