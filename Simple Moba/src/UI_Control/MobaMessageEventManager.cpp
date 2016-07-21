#include "MobaMessageEventManager.h"

MobaMessageEventManager::MobaMessageEventManager()
{
}

MobaMessageEventManager::~MobaMessageEventManager()
{
}

bool MobaMessageEventManager::Init(StandardMatch5v5State * gameState, GameMessage * gameMessage, CameraDirector * cameraDirector, DamageController * damageController)
{
	m_damageController = damageController;
	m_gameState = gameState;
	m_cameraDirector = cameraDirector;
	m_gameMessage = gameMessage;

	m_damageController->SetDamageEventCallback(std::bind(&MobaMessageEventManager::Event, this, _1));
	
	return true;
}

void MobaMessageEventManager::Event(DamageEvent damageEvent)//todo add lang stuff
{
	char message[2000];
	
	switch (damageEvent.m_eventTypeId)
	{
	case damageEventTeamLootChestDestroyed:
		{
			if (damageEvent.m_target == m_gameState->GetPurpleTeamChest())
			{
				m_gameState->SetGameOverState(gameOverStateGameOver);
				m_gameState->SetWinner(yellowTeamName);

				sprintf_s(message, "Yellow Team Win.\nThanks ");
			}

			else if (damageEvent.m_target == m_gameState->GetYellowTeamChest())
			{
				m_gameState->SetGameOverState(gameOverStateGameOver);
				m_gameState->SetWinner(purpleTeamName);

				sprintf_s(message, "Purple Team Win.\nThanks ");
			}
			else
			{
				sprintf_s(message, "A loot chest was destroyed by ");

			}

			strcat_s(message, damageEvent.m_owner->GetUniqueName().c_str());
			strcat_s(message, ".");
		
			m_cameraDirector->SetUsingCamera(usingFlyCamera);
		}
		break;
	case damageEventObjectDestroyed:
		{
			sprintf_s(message, damageEvent.m_owner->GetUniqueName().c_str());
			strcat_s(message, " has destroyed a ");
			strcat_s(message, damageEvent.m_target->GetStats()->GetName().c_str());
			strcat_s(message, ".");

		} break;
	case damageEventImportantNPC:
		{
			sprintf_s(message, damageEvent.m_owner->GetUniqueName().c_str());
			strcat_s(message, " has killed ");
			strcat_s(message, damageEvent.m_target->GetStats()->GetName().c_str());
			strcat_s(message, ".");
			
		} break;
	case damageEventPlayerDied:
		{

			//Who killed Who
			sprintf_s(message, damageEvent.m_owner->GetUniqueName().c_str());
			strcat_s(message, " has killed ");
			strcat_s(message, damageEvent.m_target->GetUniqueName().c_str());
			strcat_s(message, ".");

			if (damageEvent.m_deathEvent == nullptr) break;

			//Names for assists
			vector<VitalEntity*> * assists = damageEvent.m_deathEvent->GetAssists();
			int commaCount = 0;
			for (unsigned int i = 0; i < assists->size(); i++)
			{
				if (commaCount == 0) strcat_s(message, "\n Assists: ");
				if (commaCount >= 1) strcat_s(message, ", ");
				strcat_s(message, assists->at(i)->GetUniqueName().c_str());
				commaCount++;
			}
			strcat_s(message, ".");

		} break;
	}

	m_gameMessage->SetMessage(message);
}
