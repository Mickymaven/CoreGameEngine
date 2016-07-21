#include "CoreNPCControllerFactory.h"

CoreNPCControllerFactory::CoreNPCControllerFactory()
{
}

CoreNPCControllerFactory::~CoreNPCControllerFactory()
{
}

bool CoreNPCControllerFactory::Init(CoreCharacterFactory * coreCharacterFactory)
{
	m_coreCharacterFactory = coreCharacterFactory;

	return true;
}

bool CoreNPCControllerFactory::ConstructNPCController(
	CoreNPCController ** npcOut,
	LMVector3 * position,
	StandardMatch5v5GameUniqueNPC id,
	Pathfinder * pathfinder,
	vector<Actor*>* teamActors,
	vector<Actor*>* opponentActors,
	vector<Actor*>* neutralActors,
	CharacterClassName characterClass,
	vector<ItemName> * itemSet,
	bool targetable,
	TeamName team,
	string * uniqueName,
	vector<AbilityName> * customAbilities)
{
	Actor * actor;
	m_NPC = NULL;

	if (m_coreCharacterFactory->ConstructCharacter(
		&m_constructedCoreCharacter,
		characterClass,
		pathfinder,
		itemSet,
		teamActors,
		opponentActors,
		neutralActors,
		team,
		uniqueName,
		customAbilities))
	{
		//m_NPC = new CoreNPCController(m_constructedCoreCharacter);
		actor = m_constructedCoreCharacter->GetActor();
		actor->GetPhysicsObject()->SetPosition(*position);
	}
	else return false;

	switch (id)
	{
	case standardMatch5v5GameUniqueNPCBaseYellow:
	{
		actor->SetName("Shop Keeper");
		//actor->SetUniqueName("Yellow Shop");
		actor->GetStats()->SetHealth(5000.0f);
		actor->GetStats()->SetMaxHealth(5000.0f);

		m_NPC = new AngryCat(m_constructedCoreCharacter, teamActors, opponentActors, neutralActors);
		actor->SetIntargetable();
		break;
	}
	case standardMatch5v5GameUniqueNPCBasePurple:
	{
		actor->SetName("Shop Keeper");
		//actor->SetUniqueName("Purple Shop");
		actor->GetStats()->SetHealth(5000.0f);
		actor->GetStats()->SetMaxHealth(5000.0f);

		m_NPC = new AngryCat(m_constructedCoreCharacter, teamActors, opponentActors, neutralActors);
		actor->SetIntargetable();

		break;
	}
	case standardMatch5v5GameUniqueNPCNeutralShop1:
	{
		actor->SetName("Neutral Human");
		//actor->SetUniqueName("Neutral Shopkeep");
		actor->GetStats()->SetHealth(5000.0f);
		actor->GetStats()->SetMaxHealth(5000.0f);

		m_NPC = new AngryCat(m_constructedCoreCharacter, teamActors, opponentActors, neutralActors);
		actor->SetIntargetable();

		break;
	}
	case standardMatch5v5GameUniqueNPCAngryCat:
	{
		actor->GetStats()->SetHealth(900.0f);
		actor->GetStats()->SetMaxHealth(900.0f);
		actor->SetName("Angry Cat");
		//actor->SetUniqueName("Angry Cat ^@_@^ ");

		m_NPC = new AngryCat(m_constructedCoreCharacter, teamActors, opponentActors, neutralActors);

		break;

	}
	case standardMatch5v5GameUniqueNPCVisionOwl:
	{
		actor->GetStats()->SetHealth(4000.0f);
		actor->GetStats()->SetMaxHealth(4000.0f);
		actor->SetName("Vision Owl");
		//actor->SetUniqueName("South Vision Owl");

		m_NPC = new VisionOwl(m_constructedCoreCharacter, teamActors, opponentActors, neutralActors);
		//m_NPC->GetCharacter()->GetTradeInventory()->GetPrivateTradeInventory()->push_back(m_itemFactory->GetItem(NULL,itemNomBar));
		//todo not push items onto private trade inventory set here


		break;
	}
	default:
	case standardMatch5v5GameUniqueNPCCount:
		{
			MessageBox(NULL, "Bad UniqueNPC id sent to Game Asset Factory", "Simple Moba Debug", MB_OK);
			return false;
		}

		break;
	}


	

	*npcOut = m_NPC;

	return true;
}
