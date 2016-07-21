#include "DevInputSet.h"

DevInputSet::DevInputSet()
{}

DevInputSet::DevInputSet(StandardMatch5v5State * state, MobaViewState * view)
{
	gameState = state;
	gameView = view;
}

DevInputSet::~DevInputSet()
{

}

void DevInputSet::Update(float deltaTime)
{

}

void DevInputSet::AttemptAction(int action, float deltaTime)
{
	switch (action)
	{
	case devActionLevelCharacter:
		gameState->GetControlledActor()->GetStats()->LevelUp();
		break;
	case devActionTeleportChar:
		GetRayFromLMCamera(
			gameView->GetCameraDirector()->GetPointerToCurrentCamera(),
			g_mouseClientPosition.x,
			g_mouseClientPosition.y,
			point1,
			point2);

		TransformRayByMeshWorldMatrix(&point1, &point2, gameView->GetGameMapView()->GetGroundView()->GetWorldMatrix());
		
		if (PickFromSprite(&ResultPoint, gameView->GetGameMapView()->GetGroundView()->GetLMMesh(), point1, point2))//when you click of the map result point=null
			gameState->GetControlledCharacter()->DebugTeleport(ResultPoint.x, ResultPoint.y, ResultPoint.z);
		break;
	case devActionHalfHealth:

		if (gameState->m_isDebugTextOn)
		{
			for (unsigned int i = 0; i < gameState->GetPlayerCharacters()->size(); i++)
			{
				Actor * a = gameState->GetPlayerCharacters()->at(i)->GetActor();

				a->GetStats()->m_health = a->GetStats()->m_maxHealth / 2.0f;
			}
		}
		break;

	case devTogglePathEnabled:
		
		gameState->GetControlledCharacter()->GetPathController()->SetEnabled(
			!gameState->GetControlledCharacter()->GetPathController()->GetIsEnabled());

		if (gameState->GetControlledCharacter()->GetPathController()->GetIsEnabled())
			gameView->GetGameMessage()->SetMessage("Pathfollowing On");

		else gameView->GetGameMessage()->SetMessage("Pathfollowing Off");

		break;

	case devActionToggleDebugText:
		gameState->m_isDebugTextOn = !gameState->m_isDebugTextOn;
		break;
	}
}

void DevInputSet::SpamAction(int action, float deltaTime)
{

}