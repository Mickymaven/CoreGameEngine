#include "CharacterViewFactory.h"

CharacterViewFactory::CharacterViewFactory()
{
}

CharacterViewFactory::~CharacterViewFactory()
{
}

bool CharacterViewFactory::Init(ActorViewFactory * actorViewFactory, AbilityViewFactory * abilityViewFactory)
{
	m_actorViewFactory = actorViewFactory;
	m_abilityViewFactory = abilityViewFactory;

	return true;
}

bool CharacterViewFactory::ConstructCharacterView(
	LPDIRECT3DDEVICE9 device,
	CharacterView ** characterViewOut,
	Character * character,
	const CharacterClassName characterClass,
	vector<AbilityName> * customAbilities )
{
	CharacterView * constructedCharacterView = nullptr;
	ActorView * actorView = nullptr;

	if (!m_actorViewFactory->ConstructActorView(device, &actorView, character->GetActor(), characterClass)) return false;

	constructedCharacterView = new CharacterView(character, actorView);

	if (!ConstructCharacterAbilityViews(
		device,
		character->GetAbilities(),
		constructedCharacterView->GetAbilityViews(),
		characterClass,
		customAbilities
	)) return false;

	*characterViewOut = constructedCharacterView;
	
	return true;
}

bool CharacterViewFactory::ConstructCharacterAbilityViews(
	LPDIRECT3DDEVICE9 device,
	vector<Ability*>* abilities,
	vector<AbilityView*>* abilityViews,
	CharacterClassName name,
	vector<AbilityName>* customAbilityList)
{
	abilityViews->resize(abilitySlotCount);

	if (!m_abilityViewFactory->ConstructAbilityView(
		device,
		&abilityViews->at(abilitySlotBasicAttack),
		abilityBasicAttack,
		abilities->at(abilitySlotBasicAttack)
	)) return false;


	if (!m_abilityViewFactory->ConstructAbilityView(
		device,
		&abilityViews->at(abilitySlotRecall),
		abilityRecall,
		abilities->at(abilitySlotRecall)
	)) return false;

	if (!m_abilityViewFactory->ConstructAbilityView(
		device,
		&abilityViews->at(abilitySlotSleep),
		abilitySleep,
		abilities->at(abilitySlotSleep)
	)) return false;



	for (unsigned int i = abilitySlot1; i <= abilitySlot4; i++)
	{
		if (!m_abilityViewFactory->ConstructAbilityView(
			device,
			&abilityViews->at(i),
			m_data.m_defaultAbilities.at(name).at(i - 1),
			abilities->at(i)
		)) return false;
	}

	for (unsigned int j = abilitySlot5; j <= abilitySlot6; j++)
	{
		if (!m_abilityViewFactory->ConstructAbilityView(
			device,
			&abilityViews->at(j),
			customAbilityList->at(j - 5),
			abilities->at(j)
		)) return false;
	}

	return true;
}
