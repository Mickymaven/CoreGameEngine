#include "DamageController.h"

DamageController::DamageController()
{
	m_playerDeathDuration = 5.0f;
	m_npcDeathDuration = 5.0f;

	//temp stuff for eahc update
	m_gameModeDamageMultiplier = 1.0f;
	m_abilitySource = nullptr;
	m_appliedDamage = 0.0f;
	m_targetHealth = 0.0f;
	m_finalBlowOrigin = nullptr;
	m_deathEvent = nullptr;
	m_deleteatindex = false;
	m_damageVectorElement = nullptr;
	m_isDeathThisUpdate = false;
}

DamageController::~DamageController() {}

void DamageController::Init(MobaState * gameStateIn)
{
	VitalObjectController::gameState = gameStateIn;

	m_deathFlags.resize(gameState->GetPlayerCharacters()->size(), nullptr);
}

void DamageController::Update(float deltaTime)
{
	vector<Character *> * actorList = NULL;
	vector<Damage * > * vec = nullptr;
	Damage * damage = nullptr;

	for (unsigned int h = 0; h < gameState->GetCharacterLists()->size(); h++)
	{
		//todo damage objects should be unique for each target derived class (Vital or Actor)
		//
		//this could be done by Ability having a seperate Damage Vector for each class of target.
		//or
		//damage store enum of target like it does now but seperate derived class pointer for the target class
		//and accessor for each............
		//
		//dont really want to move damage from its casting ability bc they are there to be deactivated easily
		//by owner (on ability owner death or other state change)

		actorList = gameState->GetCharacterLists()->at(h);
	
		for (unsigned int i = 0; i < actorList->size(); i++)
		{
			//actorList->at(i)->TryThis();
			
			if (actorList->at(i) != NULL)
			{
				for (unsigned int j = 0; j < actorList->at(i)->GetAbilities()->size(); j++)//iterate abilities of each character
				{
					if (actorList->at(i)->GetAbilities()->at(j) == nullptr) continue;

					vec = actorList->at(i)->GetAbilities()->at(j)->GetDamageOnUpdate();

					for (int k = vec->size() - 1; k >= 0; k--)
					{
						damage = vec->at(k); //temp var to pass

						//later when we move damage to graveyard type functions, we need ref to original vec index
						//dont remove this
						m_damageVectorElement = &vec->at(k);

						//sprintf_s(buffer, "character %i damage # %i \n", i, k);
						//OutputDebugString(buffer);

						if (vec->at(k) != NULL)
						{
							vec->at(k)->GetTarget()->OnHit(vec->at(k)->GetOwner());

							switch (vec->at(k)->GetTarget()->GetVitalEntityType())
							{
								case vitalEntityTypeVitalEntity: DamageVitalEntity(deltaTime, damage); break;
								case vitalEntityTypeActor: DamageActor(deltaTime, damage); break;
								case vitalEntityTypeNPC: DamageNPC(deltaTime, damage); break;
								case vitalEntityTypeCount://intentional fall through
								default: break;
							}
						}
					}
					
					//house keep vec size each update
					if (vec->size() > 0)
					{
						while (vec->at(vec->size() - 1) == NULL)
						{
							vec->pop_back();

							if (vec->size() == 0) break;
						}
					}
				}
			}
		}
	}

	if (m_isDeathThisUpdate) CalculateAssists(deltaTime);
}

void DamageController::DamageVitalEntity(float deltaTime, Damage * damage)
{
	if (! RemoveDamageForInactiveTargets(deltaTime, damage) )
	{
		CalcDamageAndUpdateAbility(deltaTime, damage);

		if (m_targetHealth <= 0.0f) //process death
		{
			CommonOnDeath(damage);

			DamageEvent damageEvent;
			damageEvent.m_eventTypeId = damageEventTeamLootChestDestroyed;
			damageEvent.m_owner = damage->GetOwner();
			damageEvent.m_target = damage->GetTarget();
			m_damageEventCallback(damageEvent);
		}

		ApplyDamageChanges(deltaTime, damage);
	}
}


void DamageController::DamageNPC(float deltaTime, Damage * damage)
{
	if (!RemoveDamageForInactiveTargets(deltaTime, damage))
	{
		CalcDamageAndUpdateAbility(deltaTime, damage);

		if (m_targetHealth <= 0) //process death
		{
			CommonActorDeath(damage);

			DamageEvent d;
			d.m_eventTypeId = damageEventImportantNPC;
			d.m_owner = damage->GetOwner();
			d.m_target = damage->GetTarget();

			m_damageEventCallback(d);
		}

		ApplyDamageChanges(deltaTime, damage);
	}
}

void DamageController::DamageActor(float deltaTime, Damage * damage)
{
	((Actor*)damage->GetTarget())->GetState();

	if ( ((Actor*)damage->GetTarget())->GetState() == actorRecall )
	{
		((Actor *)damage->GetTarget())->ExitCurrentState();
		((Actor *)damage->GetTarget())->OnEnterStationary();
	}

	if (!RemoveDamageForInactiveTargets(deltaTime, damage))
	{
		CalcDamageAndUpdateAbility(deltaTime, damage);

		//process death for vital Like this:

		if (m_targetHealth <= 0)
		{
			CommonActorDeath(damage);

			//process kill information
			
			//determine result based on damage source group (which index in actorControlList).

			
			//change scores inline
			switch (((Actor*)damage->GetOwner())->GetTeam())
			{
			case yellowTeamName: (*gameState->GetTeamScore(yellowTeamName)) += 1; break;
			case purpleTeamName: (*gameState->GetTeamScore(purpleTeamName)) += 1; break;
			default: OutputDebugString("Invalid team UpdateDamageStructure()");
			}
	

			//killer kda
			m_ownerKDA = ((Actor*)damage->GetOwner())->GetKDA();
			m_ownerKDA.kills++;
			((Actor*)damage->GetOwner())->SetKDA(m_ownerKDA);

			//victim kda

			m_targetKDA = ((Actor*)damage->GetTarget())->GetKDA();
			m_targetKDA.deaths++;
			((Actor*)damage->GetTarget())->SetKDA(m_targetKDA);


			//assist kda flag to help us with our call to DamageController::CalculateAssists()
			//which occurs at the end of DamageController::UpdateDamage()
			m_isDeathThisUpdate = true;
			//OutputDebugString("DEATH FOUND --VVVVV\n");

			for (unsigned int actorCount = 0; actorCount < gameState->GetPlayerCharacters()->size(); actorCount++)
			{
				//string st1 = ((Actor*)m_targetToDamage)->GetUniqueName();
				//string st2 = gameState->GetPlayerCharacters()->at(actorCount)->GetActor()->GetUniqueName();
				//sprintf_s(bufferb, "Address targ: %s, actor address: %s, index: %i \n", st1.c_str(), st2.c_str(), actorCount);
				//OutputDebugString(bufferb);

				if (damage->GetTarget() == gameState->GetPlayerCharacters()->at(actorCount)->GetActor())
				{
					m_deathFlags.at(actorCount) = m_deathEvent;
					//OutputDebugString("DEATH FLAG CONDITION MET\n");
					break;
				}
			}
		}

		ApplyDamageChanges(deltaTime, damage);
	}
}


bool DamageController::RemoveDamageForInactiveTargets(float deltaTime, Damage * damage)
{
	if (damage->GetTarget()->GetVitalEntityState() == vitalEntityStateInactive)
	{
		//remove damage object at vector index
		StoreDamage(damage);
		return true;
	}

	return false;
}

void DamageController::CalcDamageAndUpdateAbility(float deltaTime, Damage * damage)
{
	m_abilitySource = (Ability *)damage->GetAbilitySource();

	m_targetHealth = damage->GetTarget()->GetStats()->m_health;

	if (m_targetHealth > 0)
	{
		m_reductionValue = 0.0f;
		m_totalDamageValue = 0.0f;
		m_damagePortionValue = 0.0f;
		m_reductionPortion = 0.0f;

		switch (damage->GetDamageType())
		{
		case damageTypeDamage:
			m_reductionValue = damage->GetTarget()->GetStats()->m_armor;
			break;
		case damageTypeCatVoodoo:
			m_reductionValue = damage->GetTarget()->GetStats()->m_catVoodooResist;

			break;
		default:
			break;
		}

		m_damagePortionValue = damage->UpdateReturningHealthPortion(deltaTime) * m_gameModeDamageMultiplier;

		if (m_abilitySource->GetHealthEffectApplicationType() == heaSingle)
		{
			m_abilitySource->OnEnterInactive();
			//if abilities have behavior that 
			//is intended to happen after this damage has
			//occured, then it wont happen because we are 
			//setting the ability inactive here. The alternative
			//is to make each facet of the ability have a state
			//which could be set as inactive. eg the spagetti ball.
			//OutputDebugString("Made inactive \n");
		}

		m_totalDamageValue = damage->GetValue();
		m_reductionPortion = (m_reductionValue * (m_damagePortionValue / m_totalDamageValue));

		if (m_reductionPortion < m_damagePortionValue)
		{

			m_appliedDamage = m_damagePortionValue - m_reductionPortion;
			m_targetHealth -= m_appliedDamage;

			m_abilitySource->SetDamageApplied(m_appliedDamage, damage->GetDamageType());
			//abilitySource->SetTargetHealth();
		}

		else {/* zero damage */ }
	}
}

void DamageController::ApplyDamageChanges(float deltaTime, Damage * damage)
{
	damage->GetTarget()->GetStats()->SetHealth(m_targetHealth);

	if (damage->GetState() == heInactive)
	{
		StoreDamage(damage);
	}

	if (m_targetHealth <= 0)
	{
		m_abilitySource->TargetEliminated();
		StoreDamage(damage);
	}

	/*
	house keeping
	if (vec->size() > 0)
	{

		if (vec->at(vec->size() - 1) == NULL)
		{
			vec->pop_back();
		}

		else if (vec->at(vec->size() - 1)->GetState() == heInactive)
		{
			StoreDamage(vec->at(vec->size() - 1));
			vec->at(vec->size() - 1) = NULL;
			vec->pop_back();
		}
	}*/
}

void DamageController::CommonOnDeath(Damage * damage)
{
	m_targetHealth = 0;

	m_abilitySource->SetDamageApplied(0.0f, damage->GetDamageType());
	m_abilitySource->OnEnterInactive();

	damage->GetTarget()->ExitCurrentState();
	damage->GetTarget()->OnEnterVitalEntityStateInactive();
}

void DamageController::CommonActorDeath(Damage * damage)
{
	CommonOnDeath(damage);

	RemoveBuffsFromActor(((Actor*)damage->GetTarget()));

	((Actor*)damage->GetTarget())->Death(10.0f);

	m_finalBlowType = damageOriginOpponent;
	m_finalBlowOrigin = damage->GetOwner();
	m_deathEvent = new DeathEvent(damage->GetTarget(), m_finalBlowType, m_finalBlowOrigin);

	gameState->GetDeathEvents()->push_back(m_deathEvent);
}


void DamageController::RemoveBuffsFromActor(Actor * actor)
{
	vector<Buff*> * buffs = actor->GetBuffs();
	if (buffs->size() > 0)
	{
		for (unsigned int i = buffs->size() -1; i > 0; i--)
		{
			if (buffs->at(i) != NULL) delete buffs->at(i);
			buffs->at(i) = NULL;
			buffs->pop_back();
		}
	}

	buffs = actor->GetDebuffs();
	//copy paste
	if (buffs->size() > 0)
	{
		for (unsigned int i = buffs->size() - 1; i > 0; i--)
		{
			if (buffs->at(i) != NULL) delete buffs->at(i);
			buffs->at(i) = NULL;
			buffs->pop_back();
		}
	}
}

void DamageController::StoreDamage(Damage * damage)
{
	damage->MakeInactive(*gameState->GetGameElapsedTime());

	if (damage->GetTarget()->GetVitalEntityType() == vitalEntityTypeActor)
	{
		vector<Damage*> * vec = ((VitalEntityController*)damage->GetTarget()->GetVoidToController())->GetDamageRecieved();
		if (vec != NULL)
		{
			vec->push_back(damage);

			//sprintf_s(bufferb, "Damage added to graveyard. Size now: %i \n", vec->size());
			//OutputDebugString(bufferb);
		}
	}
	else delete damage;

	//remove ref to damage object from source vector in ability
	//relies on *m_damageVectorElement being set during source vector iteration
	*m_damageVectorElement = nullptr;//ie ability::vector<damage*>->at(k)=nullptr

}

void DamageController::RecheckAllDamageToRemove(float deltaTime)
{
	for (unsigned int i = 0; i < gameState->GetPlayerCharacters()->size(); i++)
	{
		if (gameState->GetPlayerCharacters()->at(i) != NULL)
		{
			vector <Ability *> * abilities = gameState->GetPlayerCharacters()->at(i)->GetAbilities();

			for (int j = 0; j < abilities->size(); j++)//iterate abilities of each character
			{
				vector<Damage * > * vec = abilities->at(j)->GetDamageOnUpdate();

				for (int k = vec->size() - 1; k >= 0; k--)
				{
					if (vec->at(k)!=NULL) RemoveDamageForInactiveTargets(deltaTime, vec->at(k));
				}
			}
		}
	}
}

void DamageController::CalculateAssists(float deltaTime)
{
	RecheckAllDamageToRemove(deltaTime);

	float assistTimeOut = 30.0f;
	/*
	for (unsigned int x = 0; x < m_deathFlags->size(); x++)
	{
		if (m_deathFlags->at(x) == false) OutputDebugString("death flag = False. \n");
		else if (m_deathFlags->at(x) == true) OutputDebugString("death flag = True. \n");
		else OutputDebugString("??????????????????????????????????\n");
	}*/

	for (unsigned int i = 0; i < gameState->GetPlayerCharacters()->size(); i++)
	{
		if (m_deathFlags.at(i) != NULL)
		{
			vector<Damage*> * graveyard = gameState->GetPlayerCharacters()->at(i)->GetDamageRecieved();

			vector<bool> assistflag(gameState->GetPlayerCharacters()->size(), false);

			//sprintf_s(bufferb, "Iterate through GRAVEYARD;  SIZE: %i \n", graveyard->size());
			//OutputDebugString(bufferb);

			for (unsigned int dCount = graveyard->size() - 1; dCount > 0; dCount--)
			{
				//OutputDebugString("Check damage: ");
				if (graveyard->at(dCount)->GetInactiveTime() > *gameState->GetGameElapsedTime() - assistTimeOut
					&& graveyard->at(dCount)->GetState() != heCountedTowardsScores)
				{
					for (unsigned int cCount = 0; cCount < gameState->GetPlayerCharacters()->size(); cCount++)
					{
						if (graveyard->at(dCount)->GetOwner() == gameState->GetPlayerCharacters()->at(cCount)->GetActor())
						{

							if (m_deathFlags.at(i)->GetFinalBlowOrigin() != graveyard->at(dCount)->GetOwner())
							{
								m_deathFlags.at(i)->AddDamage(graveyard->at(dCount));

								assistflag.at(cCount) = true;
							}

							graveyard->at(dCount)->CountedTowardsScores();
						}
					}
				}
				else
				{
					//OutputDebugString("30 second limit hit on graveyard vector\n");
					break;
				}
			}

			for (unsigned int flagCount = 0; flagCount < assistflag.size(); flagCount++)
			{
				if (assistflag.at(flagCount))
				{
					m_deathFlags.at(i)->AddAssist(gameState->GetPlayerCharacters()->at(flagCount)->GetActor());

					m_ownerKDA = gameState->GetPlayerCharacters()->at(flagCount)->GetActor()->GetKDA();
					m_ownerKDA.assists++;
					gameState->GetPlayerCharacters()->at(flagCount)->GetActor()->SetKDA(m_ownerKDA);
					//OutputDebugString("Assist Addded!\n");
				}
			}

			GameMessageForPlayerCharacterDeathEvent(m_deathFlags.at(i));
		}
	}
	//OutputDebugString("End Assist Calc\n");


	//RESET VARS
	m_isDeathThisUpdate = false;

	for (unsigned int i = 0; i < m_deathFlags.size(); i++)
	{
		m_deathFlags.at(i) = NULL;
	}
}

void DamageController::SetDamageEventCallback(function<void(DamageEvent e)> f)
{
	m_damageEventCallback = f;
}

void DamageController::GameMessageForPlayerCharacterDeathEvent(DeathEvent * deathEvent)
{
	DamageEvent damageEvent;

	damageEvent.m_eventTypeId = damageEventPlayerDied;
	damageEvent.m_owner = (Actor*)deathEvent->GetFinalBlowOrigin();
	damageEvent.m_target = deathEvent->GetVictim();
	damageEvent.m_deathEvent = deathEvent;

	m_damageEventCallback(damageEvent);
}