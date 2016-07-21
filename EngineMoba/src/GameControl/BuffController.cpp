#include "BuffController.h"

BuffController::BuffController()
{
	tempBuff = nullptr;
	buffVector = nullptr;
}

BuffController::~BuffController()
{
}

void BuffController::Init(MobaState * gameStateIn)
{
	gameState = gameStateIn;
}

void BuffController::Update(float deltaTime)
{
}


void BuffController::UpdateBuffs(float deltaTime)
{
	UpdateBuffStructure(deltaTime, true);
}

void BuffController::UpdateDebuffs(float deltaTime)
{
	UpdateBuffStructure(deltaTime, false);
}

void BuffController::UpdateBuffStructure(float deltaTime, bool buffs)
{
	buffVector = NULL;
	tempBuff = NULL;

	for (unsigned int i = 0; i < gameState->GetPlayerCharacters()->size(); i++)
	{
		if (gameState->GetPlayerCharacters()->at(i) != NULL)
		{
			if (buffs) buffVector = gameState->GetPlayerCharacters()->at(i)->GetActor()->GetBuffs();
			else buffVector = gameState->GetPlayerCharacters()->at(i)->GetActor()->GetDebuffs();

			for (unsigned int buffCount = 0; buffCount <buffVector->size(); buffCount++)
			{
				tempBuff = buffVector->at(buffCount);

				if (tempBuff != NULL)
				{

					if (gameState->GetPlayerCharacters()->at(i)->GetActor()->GetVitalEntityState() != vitalEntityStateInactive)
						ApplyBuffToVitalEntity(buffCount, gameState->GetPlayerCharacters()->at(i)->GetActor());

					//remove this check if you want buffs to apply to inactive players
					//might want a new state that distinguishes between dead and inactive. (or two seperate ones)...
				}
			}

			gameState->GetPlayerCharacters()->at(i)->GetActor()->StatChangeUpdate(deltaTime);
		}
	}
}

void BuffController::ApplyBuffToVitalEntity(int index, Actor * owner)
{
	//we want to delete/null a buff with expired timer

	if (tempBuff->GetTimer()->GetState() == timerFinished)
	{
		delete buffVector->at(index);
		buffVector->at(index) = NULL;
		return;
	}

	else if (tempBuff->GetTimer()->GetState() == timerStarted)
	{
		*owner->GetStatChangeObject() += *(StatChangeObject*)buffVector->at(index)->GetStatChangeObject();
	}
}