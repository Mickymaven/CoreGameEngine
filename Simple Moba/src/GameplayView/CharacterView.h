#if!defined(CHARACTERVIEW_H)
#define CHARACTERVIEW_H

#include "ActorView.h"
#include "AbilityView.h"
#include "TradeInventoryView.h"

#include "../../../EngineMoba/src/Actors/Character.h"

class CharacterView
{
protected:
	Character * m_character;
	ActorView * m_actorView;
	vector<AbilityView*> m_abilityViews;

public:
	CharacterView();
	CharacterView(Character * character, ActorView * actorView);
	~CharacterView();

	ActorView * GetActorView();
	vector<AbilityView*> * GetAbilityViews();
	Character * GetCharacter();
};

#endif