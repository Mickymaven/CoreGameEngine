#include "HealingController.h"

HealingController::HealingController()
{
	m_gameModeHealingMultiplier = 1.0f;
}

HealingController::~HealingController()
{
}

void HealingController::Init(MobaState * gameStateIn)
{
	gameState = gameStateIn;
}

void HealingController::Update(float deltaTime)
{
	vector<Character *> * actorList = NULL;
	vector<Healing * > * vec = nullptr;
	Healing * healing = nullptr;

	for (unsigned int h = 0; h < gameState->GetCharacterLists()->size(); h++)
	{
		actorList = gameState->GetCharacterLists()->at(h);

		for (unsigned int i = 0; i < actorList->size(); i++)
		{
			//actorList->at(i)->TryThis();

			if (actorList->at(i) != NULL)
			{
				for (unsigned int j = 0; j < actorList->at(i)->GetAbilities()->size(); j++)//iterate abilities of each character
				{
					if (actorList->at(i)->GetAbilities()->at(j) == nullptr) continue;

					vec = actorList->at(i)->GetAbilities()->at(j)->GetHealingOnUpdate();

					for (int k = vec->size() - 1; k >= 0; k--)
					{
						healing = vec->at(k); //temp var to pass

						//later when we move damage to graveyard type functions, we need ref to original vec index
						//dont remove this
						m_healingVectorElement = &vec->at(k);

						if (vec->at(k) != NULL)
						{
							vec->at(k)->GetTarget()->OnHit(vec->at(k)->GetOwner());

							switch (vec->at(k)->GetTarget()->GetVitalEntityType())
							{
							case vitalEntityTypeVitalEntity: HealVitalEntity(deltaTime, healing); break;
							case vitalEntityTypeActor: HealActor(deltaTime, healing); break;
							case vitalEntityTypeNPC: HealNPC(deltaTime, healing); break;
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
}

void HealingController::HealVitalEntity(float deltaTime, Healing * healing)
{
	if (!RemoveHealingForInactiveTargets(deltaTime, healing))
	{
		CalcHealingAndUpdateAbility(deltaTime, healing);
		ApplyHealingChanges(deltaTime, healing);
	}
}

void HealingController::HealNPC(float deltaTime, Healing * healing)
{
	if (!RemoveHealingForInactiveTargets(deltaTime, healing))
	{
		CalcHealingAndUpdateAbility(deltaTime, healing);
		ApplyHealingChanges(deltaTime, healing);
	}
}

void HealingController::HealActor(float deltaTime, Healing * healing)
{
	if (!RemoveHealingForInactiveTargets(deltaTime, healing))
	{
		CalcHealingAndUpdateAbility(deltaTime, healing);
		ApplyHealingChanges(deltaTime, healing);
	}
}

bool HealingController::RemoveHealingForInactiveTargets(float deltaTime, Healing * healing)
{
	if (healing->GetTarget()->GetVitalEntityState() == vitalEntityStateInactive)
	{
		StoreHealing(healing);
		return true;
	}

	return false;
}

void HealingController::CalcHealingAndUpdateAbility(float deltaTime, Healing * healing)
{
	m_abilitySource = (Ability *)healing->GetAbilitySource();

	m_targetHealth = healing->GetTarget()->GetStats()->m_health;

	m_healthPortionValue = 0.0f;
	m_appliedHealing = 0.0f;

	m_healthPortionValue = healing->UpdateReturningHealthPortion(deltaTime) * m_gameModeHealingMultiplier;

	//if (m_abilitySource->GetHealthEffectApplicationType() == heaSingle) m_abilitySource->OnEnterInactive();

	//heal up to max
	if (m_healthPortionValue > (healing->GetTarget()->GetStats()->m_maxHealth - m_targetHealth))
		m_appliedHealing = (healing->GetTarget()->GetStats()->m_maxHealth - m_targetHealth);
	//else can use full heal as it wont be upto max
	else m_appliedHealing = m_healthPortionValue;

	m_targetHealth += m_appliedHealing;

	//m_abilitySource->SetDamageApplied(m_appliedDamage, damage->GetDamageType());
		
}

void HealingController::ApplyHealingChanges(float deltaTime, Healing * healing)
{
	healing->GetTarget()->GetStats()->SetHealth(m_targetHealth);

	if (healing->GetState() == heInactive)
	{
		StoreHealing(healing);
	}

	/*topo death event stuff does damage healing cleanup
	if (m_targetHealth <= 0)
	{
		m_abilitySource->TargetEliminated();
		StoreHealing(healing);
	}*/
}
void HealingController::StoreHealing(Healing * healing)
{
	healing->MakeInactive(*gameState->GetGameElapsedTime());

	if (healing->GetTarget()->GetVitalEntityType() == vitalEntityTypeActor)
	{
		vector<Healing*> * vec = ((VitalEntityController*)healing->GetTarget()->GetVoidToController())->GetHealingRecieved();
		if (vec != NULL)
		{
			vec->push_back(healing);

		}
	}
	else delete healing;

	//remove ref to damage object from source vector in ability
	//relies on *m_damageVectorElement being set during source vector iteration
	*m_healingVectorElement = nullptr;//ie ability::vector<damage*>->at(k)=nullptr

}