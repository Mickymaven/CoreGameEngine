#include "UIMobaHud.h"

TooltipController * UIMobaHud::m_tooltipController = NULL;

UIMobaHud::UIMobaHud() : UIHudBase()
{
	m_isLeftInv = true;
	m_playerCharacter = NULL;
	m_elapsedGameTime = NULL;
	cTime = 0.0f;
}

UIMobaHud::~UIMobaHud()
{

}

bool UIMobaHud::Init(
	CoreGameState * gameStateIn, //todo substitute for base class pointer ad every thing inited here is from Engine MOBA
	ViewProfile * viewProfile,
	ThemeResources * theme,
	CameraDirector * cameraDirector,
	GameConfiguration * gameConfiguration,
	bool invLeft,
	float * gameTime,
	vector<InputModel*> * inputModels,
	vector<BuffView> * buffViews,
	vector<ItemView> * itemViews,
	TooltipController * tooltipController,
	PlayerCharacterController * initCharControl)
{
	gameState = gameStateIn;
	m_tooltipController = tooltipController;
	m_viewProfile = viewProfile;
	m_theme = theme;
	m_cameraDirector = cameraDirector;


	m_state = uiHudClosed;

	if (!viewProfile->InitElement(gameElementHUD, &m_playergui)) return false;
	




	if (! m_map.Init(gameStateIn, gameConfiguration)) return false;
	if (! m_characterPanel.Init(viewProfile, theme, gameStateIn, tooltipController, inputModels, initCharControl)) return false;
	if (! m_gameInfoPanel.Init(viewProfile, theme, gameStateIn, tooltipController, initCharControl, inputModels, itemViews)) return false;
	if (! m_invPanel.Init(viewProfile, theme, gameStateIn, tooltipController, inputModels, itemViews, initCharControl)) return false;
	if (!m_chat.Init(viewProfile, theme, gameStateIn)) return false;

	//491; 0.3881422f ~= 0.5f-0.111857f
	//912;

	

	m_elapsedGameTime = gameTime;

	m_greyColorValue = D3DCOLOR_XRGB(255, 255, 255);
	m_darkGreyColorValue = D3DCOLOR_XRGB(9, 9, 9);
	m_tomatoColorValue = D3DCOLOR_XRGB(192, 128, 128);

	//m_avatar.GetPosition()->x = 377.0f;
	//m_avatar.GetPosition()->z = g_clientSizeRect->bottom - m_avatar.GetHeight();
	m_isLeftInv = invLeft;
	
	m_isDragging = false;
	m_dragTimer = LMTimer(0.5f, false);

	//buff display stuff
	m_origin = LMVector2(0.3f, 0.75f);
	m_origin.x *= g_clientSizeRect->right;
	m_origin.y *= g_clientSizeRect->bottom;
	m_xIndexCount = 0;

	m_playerBuffSize = 15;

	// buffs
	m_buffs.m_buffs.resize(m_playerBuffSize);
	if (!m_buffs.Init(buffViews)) return false;

	for (unsigned int i = 0; i < m_playerBuffSize; i++)
		m_buffs.m_buffs.at(i).SetMouseOverCallback(
		std::bind(&TooltipController::ActivateTooltipBuff, m_tooltipController, _1, _2));
	LMVector4 buffsBounds = LMVector4(440.0f, 750.0f, 840.0f, 790.0f);
	m_buffs.PositionItems(&buffsBounds, 43.0f, 43.0f, 45.0f, 0.0f);

	//debuffs
	m_debuffs.m_buffs.resize(m_playerBuffSize);
	if (!m_debuffs.Init(buffViews)) return false;
	
	for (unsigned int i = 0; i < m_playerBuffSize; i++)
		m_debuffs.m_buffs.at(i).SetMouseOverCallback(
		std::bind(&TooltipController::ActivateTooltipBuff, m_tooltipController, _1, _2));
	LMVector4 debuffsBounds = LMVector4(440.0f, 795.0f, 840.0f, 845.0f);
	m_debuffs.PositionItems(&debuffsBounds, 43.0f, 43.0f, 45.0f, 0.0f);

	//player inv
	
	/*
	m_maxInvSize = 10;

	m_playerInventory.SetItemViews(itemViews);
	m_playerInventory.m_items.resize(initCharControl->GetInventory()->size());
	
	for (unsigned int i = 0; i < m_maxInvSize; i++)
		m_playerInventory.m_items.at(i).SetMouseOverCallback(
		std::bind(&TooltipController::ActivateTooltipItem, m_tooltipController, _1, _2, _3));
	CalculateInvPositions(viewProfile);
	*/


	return true;
}

void UIMobaHud::CalculateInvPositions(ViewProfile * viewProfile)
{
	/*
	LMVector4 bounds = LMVector4(0.0f,0.0f,g_clientSizeRect->right, g_clientSizeRect->bottom);

	x_start = 10.0f;
	z_start = g_clientSizeRect->bottom - 100.0f;
	x_dist = 44.0f;
	z_dist = 44.0f;


	float rowTop = 0.0f;
	float elementLeft = 0.0f;
	LMVector3 * pos = NULL;
	RECT * eleBounds = NULL;
	float eleWidth = 0.0f;
	float eleHeight = 0.0f;

	rowTop = z_start;
	elementLeft = x_start;

	for (unsigned int index = 0; index < m_maxInvSize; index++)
	{

		m_playerInventory.m_items.at(index).SetWidth(43.0f);
		m_playerInventory.m_items.at(index).SetHeight(43.0f);

		eleWidth = m_playerInventory.m_items.at(index).GetWidth();
		eleHeight = m_playerInventory.m_items.at(index).GetHeight();
		pos = m_playerInventory.m_items.at(index).GetPosition();
		eleBounds = m_playerInventory.m_items.at(index).GetBounds();

		pos->x = elementLeft;
		pos->z = rowTop;

		eleBounds->left = elementLeft;
		eleBounds->top = rowTop;
		eleBounds->bottom = rowTop + eleHeight;
		eleBounds->right = elementLeft + eleWidth;

		if (index == 4)
		{
			rowTop += z_dist;
			elementLeft = x_start;
		}
		else elementLeft += x_dist;


		m_inventoryPositons[index] = LMVector3(
			x_start + index*x_dist,
			0.0f,
			z_start);

		if (index > 4)
		{
			m_inventoryPositons[index].z += z_dist;
			m_inventoryPositons[index].x -= 5 * x_dist;
		}
	}*/
}

void UIMobaHud::SetInvItems(PlayerCharacterController * playerCharacterController)
{
	//TODO find place to update selected Player Controller;

	//m_playerInventory.SetItems(playerCharacterController->GetInventory());

	//for (unsigned int i = 0; i < playerCharacterController->GetInventory()->size(); i++)
	//{
	//	m_playerInventory.m_items.at(i).SetItem(playerCharacterController->GetInventory()->at(i));
	//}
}

void UIMobaHud::SetBuffs(PlayerCharacterController * playerCharacterController)
{
	m_buffs.SetBuffs(playerCharacterController->GetCharacter()->GetActor()->GetBuffs());
	m_debuffs.SetBuffs(playerCharacterController->GetCharacter()->GetActor()->GetDebuffs());
}


void UIMobaHud::Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView)
{
	//TODO only perform this on Item change?
	//SetInvItems(playerCharacterController);
	m_invPanel.Update(deltaTime, playerCharacterController, playerCharacterView);

	SetBuffs(playerCharacterController);

	m_characterPanel.Update(deltaTime, playerCharacterController, playerCharacterView);
	m_map.Update(deltaTime);

	m_playerCharacter = playerCharacterController;
	//m_dragTimer.Update(deltaTime);

}

void UIMobaHud::Render()
{
	if (m_state != uiHudClosed)
	{
		m_playergui.Render();
		m_map.Render();
		m_characterPanel.Render();
		m_gameInfoPanel.Render();

		m_invPanel.Render();

		if (m_playerCharacter != NULL)
		{

			//render buffs

			m_buffs.Render();
			m_debuffs.Render();
		}
	}

	m_chat.Render();
}

void UIMobaHud::RenderTextStuff()
{
	//hud is closed. dont render
	
	// # player interface text //////////////////////////////////////////////////


	//names and cds below
	tempCDvalue = -123.0f;//invalid to test
	m_tempColorValue = m_greyColorValue;

	//yellow cooldowns

	vector <PlayerCharacterController *> * switchTeamUX = NULL;
	
	//float xbump = (70.0f / g_clientSizeRect->right)* g_clientSizeRect->right;
	float xbump = 70.0f;
	//float team2 = (580.0f / g_clientSizeRect->right)* g_clientSizeRect->right;

	float team2 = ((0.5935 - 0.17578125) * g_clientSizeRect->right);

	if (m_state != uiHudClosed)
	{


		for (int h = 0; h <= 1; h++)
		{
			if (h == 0) switchTeamUX = gameState->GetPlayerCharactersByTeam(yellowTeamName);
			else if (h == 1) switchTeamUX = gameState->GetPlayerCharactersByTeam(purpleTeamName);

			for (int i = 0; i < 5; i++)
			{
				//player name at top

				m_fontPos = { 180, -1, 230, g_clientSizeRect->bottom };
				m_fontPos.left = 0.17578125 * g_clientSizeRect->right;
				m_fontPos.right = m_fontPos.left + 50;

				m_fontPos.left += (int)((xbump  * i) + (h * team2));
				m_fontPos.right += (int)((xbump * i) + (h * team2));

				sprintf_s(m_buffer9001, switchTeamUX->at(i)->GetCharacter()->GetActor()->GetUniqueName().c_str());

				m_fontPos.top += 1;
				m_fontPos.left += 1;
				m_fontPos.right += 1;


			
				m_theme->m_nameText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_CENTER, D3DCOLOR_XRGB(48, 47, 45));
				m_fontPos.top -= 1;
				m_fontPos.left -= 1;
				m_fontPos.right -= 1;
				m_theme->m_nameText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));

				m_fontPos = { 180, 35, 230, g_clientSizeRect->bottom };
				m_fontPos.left = 0.17578125 * g_clientSizeRect->right;
				m_fontPos.right = m_fontPos.left + 50;

				m_fontPos.left += (int)((xbump  * i) + (h * team2));
				m_fontPos.right += (int)((xbump * i) + (h * team2));


				tempCDvalue = 0.0f;

				if (switchTeamUX->at(i)->GetCharacter()->GetActor()->GetState() == actorDead)
				{
					tempCDvalue = switchTeamUX->at(i)->GetCharacter()->GetActor()->GetTimer()->GetRemainder();
				}

				if (tempCDvalue > 0.0f)
				{
					if (tempCDvalue < 1.0f) sprintf_s(m_buffer9001, "%0.1f", tempCDvalue);
					else sprintf_s(m_buffer9001, "%.0f", tempCDvalue);

					m_theme->m_largeText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_CENTER, D3DCOLOR_XRGB(48, 47, 45));
				}

				tempCDvalue = 0.0f;
				if (switchTeamUX->at(i)->GetCharacter()->GetActor()->GetState() == actorRecall)
				{
					tempCDvalue = ((Recall*)switchTeamUX->at(i)->GetCharacter()->GetAbilities()->at(actionCastRecall))->GetRecallTimer()->GetRemainder();
				}

				if (tempCDvalue > 0.0f)
				{
					if (tempCDvalue < 1.0f) sprintf_s(m_buffer9001, "%0.1f", tempCDvalue);
					else sprintf_s(m_buffer9001, "%.0f", tempCDvalue);

					m_theme->m_nameText.m_font->DrawText(NULL, m_buffer9001, -1,&m_fontPos, DT_CENTER, D3DCOLOR_XRGB(0, 0, 0));
				}


				/*
				//damage vec size
				for (int j = 1; j <= 4; j++)
				{
				m_fontPos.top += 30;
				sprintf_s(m_buffer9001, "%i", switchTeamUX->at(i)->GetSlotAbility(j)->GetDamageOnUpdate()->size());
				m_theme->m_largeText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_CENTER, D3DCOLOR_XRGB(222, 255, 222));
				}
				*/
			}
		}

		int yEnd = g_clientSizeRect->bottom;
		int xEnd = g_clientSizeRect->right;

		//YellowTeamScore
		sprintf_s(m_buffer9001, "%i", *gameState->GetTeamScore(yellowTeamName));
		m_fontPos = { 0, 15, (g_clientSizeRect->right / 2 - 60), yEnd };
		m_theme->m_largeText.m_font->DrawText(NULL, m_buffer9001, -1,&m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 192));

		//PurpleTeamScore
		sprintf_s(m_buffer9001, "%i", *gameState->GetTeamScore(purpleTeamName));
		m_fontPos = { (g_clientSizeRect->right / 2 + 60), 15, g_clientSizeRect->right, yEnd };
		m_theme->m_largeText.m_font->DrawText(NULL, m_buffer9001, -1,&m_fontPos, DT_LEFT, D3DCOLOR_XRGB(255, 192, 255));

		//Kills
		sprintf_s(m_buffer9001, "%i  /", gameState->GetControlledCharacter()->GetActor()->GetKDA().kills);
		m_fontPos = { 0, (LONG)(0.01f*g_clientSizeRect->bottom), 50, g_clientSizeRect->bottom };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1,&m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));

		//Deaths
		sprintf_s(m_buffer9001, "%i  /", gameState->GetControlledCharacter()->GetActor()->GetKDA().deaths);
		m_fontPos = { 0, (LONG)(0.01f*g_clientSizeRect->bottom), 88, g_clientSizeRect->bottom };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1,&m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));

		//Assists
		sprintf_s(m_buffer9001, "%i", gameState->GetControlledCharacter()->GetActor()->GetKDA().assists);
		m_fontPos = { 0, (LONG)(0.01f*g_clientSizeRect->bottom), 112, g_clientSizeRect->bottom };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1,&m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));




		//INV Value
		sprintf_s(m_buffer9001, "Inventory value: %i", *gameState->GetControlledCharacter()->GetInventoryValue());
		m_fontPos = { 10, (LONG)(0.855f * g_clientSizeRect->bottom), 150, g_clientSizeRect->bottom };//795
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(163, 175, 160));

		int sStart = 0.419f*g_clientSizeRect->right;
		int sSpread = 39.68f;//0.031f * g_clientSizeRect->right;*1280
		int yStart = g_clientSizeRect->bottom - 0.025f*g_clientSizeRect->bottom;

	 }//end not mobaHUDClosed check

	//// GAME DEBUG STUFF /////
	if (gameState->m_isDebugTextOn)
	{
		// active camera
		switch (m_cameraDirector->m_gameCameraThisUpdate)
		{
		case usingThirdPersonCamera: sprintf_s(m_buffer9001, "Third Person Camera"); break;
		case usingFlyCamera: sprintf_s(m_buffer9001, "Fly Camera"); break;
		case usingLockCamera: sprintf_s(m_buffer9001, "Lock Camera"); break;
		case usingInterfaceCamera: sprintf_s(m_buffer9001, "Interface Camera"); break;
		default: sprintf_s(m_buffer9001, "Other");
		}
		m_fontPos = { 0, 580, g_clientSizeRect->right - 10, g_clientSizeRect->bottom };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));

		//lock status
		if (m_cameraDirector->GetIsCameraLocked()) sprintf_s(m_buffer9001, "Lock On");
		else sprintf_s(m_buffer9001, "Lock Off");
		m_fontPos = { 0, 600, g_clientSizeRect->right - 10, 2222 };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));


		// Actor Attack Move State Feedback
		switch (gameState->GetControlledCharacter()->GetAttackMoveController()->GetState())
		{
		case attackMoveStateStandby: sprintf_s(m_buffer9001, "attackMoveStateStandby"); break;
		case attackMoveRegularWalk: sprintf_s(m_buffer9001, "attackMoveRegularWalk"); break;
		case attackMoveStateDBAttacking: sprintf_s(m_buffer9001, "attackMoveStateDBAttacking"); break;
		case attackMoveStateDBMoving: sprintf_s(m_buffer9001, "attackMoveStateDBMoving"); break;
		case attackMoveStateAMAttacking: sprintf_s(m_buffer9001, "attackMoveStateAMAttacking"); break;
		case attackMoveStateAMMoving: sprintf_s(m_buffer9001, "attackMoveStateAMMoving"); break;
		default:
			sprintf_s(m_buffer9001, "bad state");
			break;
		}

		m_fontPos = { 0, 640, g_clientSizeRect->right - 10, g_clientSizeRect->bottom };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));


		//battle state feedback
		switch (gameState->GetControlledCharacter()->GetBattleStateController()->GetBattleState())
		{
		case actorBattleStateDefendPosition: sprintf_s(m_buffer9001, "actorBattleStateDefendPosition"); break;
		case actorBattleStateDefendArea: sprintf_s(m_buffer9001, "actorBattleStateDefendArea"); break;
		case actorBattleStateChase: sprintf_s(m_buffer9001, "actorBattleStateChase"); break;
		case actorBattleStateStopped: sprintf_s(m_buffer9001, "actorBattleStateStopped"); break;
		}
		m_fontPos = { 0, 660, g_clientSizeRect->right - 10, 2222 };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));

		//Path Controller State
		switch (gameState->GetControlledCharacter()->GetPathController()->GetState())
		{
		case pathStateStandby:sprintf_s(m_buffer9001, "pathStateStationary"); break;
		case pathStateRequestPath:sprintf_s(m_buffer9001, "pathStateRequestPath"); break;
		case pathStateNavigate:sprintf_s(m_buffer9001, "pathStateNavigate"); break;
		case pathStateAlternativePath:sprintf_s(m_buffer9001, "pathStateAlternativePath"); break;
		}
		m_fontPos = { 0, 680, g_clientSizeRect->right - 10, 2222 };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));


		//battle state feedback
		switch (gameState->GetControlledCharacter()->GetWalkState()->GetState())
		{
		case walkStateStopped: sprintf_s(m_buffer9001, "walkStateStopped"); break;
		case walkStatePaused: sprintf_s(m_buffer9001, "walkStatePaused"); break;
		case walkStateWalking: sprintf_s(m_buffer9001, "walkStateWalking"); break;
		case walkStateCount: sprintf_s(m_buffer9001, "walkStateCount"); break;
		}
		m_fontPos = { 0, 700, g_clientSizeRect->right - 10, 2222 };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));

		//player Character's actor feedback.
		switch (gameState->GetControlledCharacter()->GetActor()->GetState()) {
		case actorUnspawned: sprintf_s(m_buffer9001, "actorUnspawned"); break;
		case actorDead: sprintf_s(m_buffer9001, "actorDead"); break;
		case actorRecall: sprintf_s(m_buffer9001, "actorRecall"); break;
		case actorCasting: sprintf_s(m_buffer9001, "actorCasting"); break;
		case actorBasicAttack: sprintf_s(m_buffer9001, "actorBasicAttack"); break;
		case actorStationary: sprintf_s(m_buffer9001, "actorStationary"); break;
		case actorWalking: sprintf_s(m_buffer9001, "actorWalking"); break;
		case actorWalkToBasicTarget: sprintf_s(m_buffer9001, "actorWalkToBasicTarget"); break;
		case actorDirectionalCast: sprintf_s(m_buffer9001, "actorDirectionalCast"); break;
		case actorInstantCast: sprintf_s(m_buffer9001, "actorInstantCast"); break;
		case actorPointCast: sprintf_s(m_buffer9001, "actorPointCast"); break;
		case actorSingleTargetCast: sprintf_s(m_buffer9001, "actorSingleTargetCast"); break;
		case actorAttackMoveCast: sprintf_s(m_buffer9001, "actorAttackMoveCast"); break;
		case actorStateCount:default: break;
		}
		m_fontPos = { 0, 720, g_clientSizeRect->right - 10, g_clientSizeRect->bottom };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));

		//player position
		sprintf_s(m_buffer9001, "( %000.2f, %000.2f, %000.2f )",
			gameState->GetControlledCharacter()->GetActor()->GetPhysicsObject()->GetPosition()->x,
			gameState->GetControlledCharacter()->GetActor()->GetPhysicsObject()->GetPosition()->y,
			gameState->GetControlledCharacter()->GetActor()->GetPhysicsObject()->GetPosition()->z);
		m_fontPos = { 10, 740, g_clientSizeRect->right - 10, g_clientSizeRect->bottom };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));


		//( Debug only stat leveling)
		sprintf_s(m_buffer9001, "%i L", gameState->GetControlledCharacter()->GetActor()->GetStats()->GetLevel());
		m_fontPos = { 0, 760, g_clientSizeRect->right - 10, 2222 };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));

		//current camera pos
		D3DXVECTOR3 * cPos = m_cameraDirector->GetUsingCamera(m_cameraDirector->m_gameCameraThisUpdate)->GetPosition();
		sprintf_s(m_buffer9001, "( %000.2f, %000.2f, %000.2f )", cPos->x, cPos->y, cPos->z);
		m_fontPos = { 10, 780, g_clientSizeRect->right - 10, g_clientSizeRect->bottom };
		m_theme->m_mediumText.m_font->DrawText(NULL, m_buffer9001, -1, &m_fontPos, DT_RIGHT, D3DCOLOR_XRGB(255, 128, 255));


	}
}

void UIMobaHud::ImplementBehavior(int index, int enumIndex)
{
	OutputDebugString("Found Click. Is item in Slot? ");

	//stuff that is only intended to happen as soon as we release drag
	if (enumIndex == 1)//1 means drag to position
	{
		if (m_isDragging == true)
		{
			//we can swap
			if (m_playerCharacter->GetCharacter()->GetInventory()->at(index) == NULL)
			{
				//swap method a
				m_playerCharacter->GetCharacter()->GetInventory()->at(index) = m_playerCharacter->GetCharacter()->GetInventory()->at(m_dragIndex);
				m_playerCharacter->GetCharacter()->GetInventory()->at(m_dragIndex) = NULL;
			}
			else
			{
				//swap method b
				Item * tempItemPointer = NULL;
				tempItemPointer = m_playerCharacter->GetCharacter()->GetInventory()->at(index);
				m_playerCharacter->GetCharacter()->GetInventory()->at(index) = m_playerCharacter->GetCharacter()->GetInventory()->at(m_dragIndex);
				m_playerCharacter->GetCharacter()->GetInventory()->at(m_dragIndex) = tempItemPointer;

			}
			m_isDragging = false;
		}

		return;
	}

	// stuff that only happens when we are first clicking
	if (m_playerCharacter->GetCharacter()->GetInventory()->at(index) != NULL)
	{
		OutputDebugString("Yes\n");
		
		
		if (m_isDragging == false)
		{
			m_dragTimer.RestartWithDuration(0.5f, true);
			m_isDragging = true;
			m_dragIndex = index;
		}
	}
	else OutputDebugString("No\n");
}

void UIMobaHud::ActionSelect()
{
	if (m_isDragging == false)
	{
		BehaviorOnFirstHit(43.0f, 43.0f, m_inventoryPositons, 10, 0);

	}

	//are we dragging or just clicking?
	//timers for how long our click has been held down
	//in update
	//how far has our mouse moved since we have started our drag
	//is that far enough?


}

void UIMobaHud::ActionUnselect()
{
	/*
	if (m_isDragging == true)
	{
		//do swap if swappable
		BehaviorOnFirstHit(43.0f, 43.0f, m_inventoryPositons, 10, 1);

		m_isDragging = false;
		m_dragTimer.Stop();
	}
	*/
}

void UIMobaHud::Select(POINT * p)
{
	if (m_state != uiHudClosed)
	{
		m_map.Select(p);
		//m_gameInfoPanel.Select(p);
		m_invPanel.Select(p);
	}
}

void UIMobaHud::AltSelect(POINT * p)
{
	if (m_state != uiHudClosed)
	{
		//m_map.AltSelect(p); do this in InputSet > map needs bool return
	}
}

bool UIMobaHud::MouseOver(POINT * p)
{
	/*
	for (unsigned int i = 0; i < m_maxInvSize; i++)
	{
		if (m_playerInventory.m_items.at(i).MouseOver(p)) return true;
	}
	*/
	if (m_state != uiHudClosed)
	{
		//abilities
		if (m_invPanel.MouseOver(p)) return true;
		if (m_buffs.MouseOver(p)) return true;
		if (m_debuffs.MouseOver(p)) return true;
		if (m_characterPanel.MouseOver(p)) return true;

	}
	return false;
}

bool UIMobaHud::IsDragging()
{
	return m_isDragging;
}

bool UIMobaHud::InitAvatarElement(UIElement * uiElement, CharacterClassName characterClass)
{
	return true;
}

void UIMobaHud::SetStateRequest(UIHudState state)
{
	if (state < uiHudStateCount && state >=0) m_state = state;
}

UIChat * UIMobaHud::GetChat() { return &m_chat; }

UIMobaMap * UIMobaHud::GetMap()
{
	return &m_map;
}

UIGameInfoPanel * UIMobaHud::GetGameInfoPanel()
{
	return &m_gameInfoPanel;
}

UICharacterPanel * UIMobaHud::GetCharacterPanel()
{
	return &m_characterPanel;
}

UIInvPanel * UIMobaHud::GetInvPanel()
{
	return &m_invPanel;
}
