#include "NPCView.h"

NPCView::NPCView()
{

}

NPCView::NPCView(NPCController * npcController, CharacterView * characterView)
	: CharacterControllerView(characterView), m_npcController(npcController)
{
	//(actorView)

	vector<Ability*> * abilties = npcController->GetCharacter()->GetAbilities();
	//m_basicView = BasicAttackView(device, (BasicAttack*)abilties->at(0));//0 means basic attack getss stored first for npcs (might change)
	
}

NPCView::~NPCView()
{
}

void NPCView::Render()
{
	m_characterView->GetActorView()->Render();

	for (unsigned int i = 0; i < m_characterView->GetAbilityViews()->size(); i++)
	{
		if (m_characterView->GetAbilityViews()->at(i) != nullptr)
			m_characterView->GetAbilityViews()->at(i)->Render();
	}
	
	//m_basicView.Render();
}

NPCController * NPCView::GetNPCController() { return m_npcController; }


