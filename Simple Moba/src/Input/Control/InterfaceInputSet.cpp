#include "InterfaceInputSet.h"

InterfaceInputSet::InterfaceInputSet()
{}

InterfaceInputSet::InterfaceInputSet(StandardMatch5v5State * state, MobaViewState * view, PlayerWorldSelectionController * playerWorldSelectionController)
{
	gameState = state;
	gameView = view;
	m_playerWorldSelectionController = playerWorldSelectionController;
}

InterfaceInputSet::~InterfaceInputSet()
{

}

void InterfaceInputSet::Update(float deltaTime)
{
	if (gameView->GetHud()->GetInvPanel()->GetIsDraggingItem())
	{
		if (!sm_gameInputController->GetMousePress(LEFT_BUTTON, m_model->m_spamFlags[interfaceActionSelect], false))
			gameView->GetHud()->GetInvPanel()->SelectMouseUp(&g_mouseClientPosition);
	}
	else
	{
		//you are not dragging your item in the inv panel. The hud will provide mouse over oon that item below.
		gameView->GetHud()->MouseOver(&g_mouseClientPosition);
	}
}

void InterfaceInputSet::AttemptAction(int action, float deltaTime)
{
	switch (action)
	{
	case interfaceActionSelect:
	{
		//every following Mouse Handling calls should not happen if the hud is closed
		if (gameView->GetHud()->GetState() != uiHudClosed)
		{

			gameView->GetHud()->GetGameInfoPanel()->Select(&g_mouseClientPosition);
			sm_gameInputController->ExpendForBounds(LEFT_BUTTON, gameView->GetHud()->GetGameInfoPanel());

			gameView->GetHud()->GetInvPanel()->Select(&g_mouseClientPosition);
			sm_gameInputController->ExpendForBounds(LEFT_BUTTON, gameView->GetHud()->GetInvPanel());

			//expend
		}

		if (!sm_gameInputController->GetMousePressDownLast(LEFT_BUTTON))
			//gameView->GetInterfaceInputModel()->m_keybinds[interfaceActionSelect]))
			gameView->GetDialogScreenController()->ActionSelect(&g_mouseClientPosition);

		//Character Panel Button CLicks
		int abilityIndex = gameView->GetHud()->GetCharacterPanel()->SelectFromAbilities(&g_mouseClientPosition);

		PlayerAction theActions[] = 
		{
			actionCastAbility1,
			actionCastAbility2,
			actionCastAbility3,
			actionCastAbility4,
			actionCastAbility5,
			actionCastAbility6,
			actionCastRecall,
			actionCastSleep,
		};



		if (gameView->GetHud()->GetState() == uiHudClosed) break;

		if (abilityIndex > -1)
		{

			if (!sm_gameInputController->GetMousePressDownLast(LEFT_BUTTON))
			{

				if (abilityIndex == actionCastRecall)
				{
					((CoreCharacter*)gameState->GetControlledCharacter())->ActionCastRecall(*gameState->GetGameElapsedTime());
				}
				else if (abilityIndex == actionCastSleep)
				{
					((CoreCharacter*)gameState->GetControlledCharacter())->ActionCastSleep(*gameState->GetGameElapsedTime());
				}

				else 
				{
					gameState->GetControlledCharacter()->ActionCastAbility(//Todo (annoying me that so many parameters for no reason)
					theActions[abilityIndex],
					abilityIndex,
					*gameState->GetGameElapsedTime(),
					gameState->ActorsForSide(teamSideFriendly),
					gameState->ActorsForSide(teamSideOpponent),
					gameState->GetTargetableNPCs());
				 }
			}

			sm_gameInputController->ExpendMouseKey(LEFT_BUTTON);
		}
	
		break;
	}
	case interfaceActionAltSelect:

		//every following Mouse Handling calls should not happen if the hud is closed
		if (gameView->GetHud()->GetState() == uiHudClosed) break;

		if (gameView->GetHud()->GetMap()->ActionAltSelect(&g_mouseClientPosition, gameView->GetIndicatorController()->GetWalkIndicator()))
		{
			gameView->GetIndicatorController()->SetWalkIndicatorTimer(0.0f);
		}


		sm_gameInputController->ExpendForBounds(RIGHT_BUTTON, gameView->GetHud()->GetMap());

		break;

	}
}

void InterfaceInputSet::SpamAction(int action, float deltaTime)
{

}