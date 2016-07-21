#include "CharacterView.h"

CharacterView::CharacterView() {}

CharacterView::CharacterView(Character * character, ActorView * actorView)
	: m_actorView(actorView) , m_character(character)
{}

CharacterView::~CharacterView()
{
	//we take responsibility for use of new Keyword in a factory here.

	delete m_actorView;
	m_actorView = nullptr;

	for (unsigned int i = 0; i < m_abilityViews.size();  i++)
	{
		delete m_abilityViews.at(i);
		m_abilityViews.at(i) = nullptr;
	}
}

ActorView * CharacterView::GetActorView() { return m_actorView; }
vector<AbilityView*> * CharacterView::GetAbilityViews() { return &m_abilityViews; }
Character * CharacterView::GetCharacter() { return m_character; }

