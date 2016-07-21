#include "PlayerCharacterView.h"

PlayerCharacterView::PlayerCharacterView()
{
}

PlayerCharacterView::PlayerCharacterView(
	PlayerCharacterController * playerCharacterController,
	CharacterView * characterView)

	: CharacterControllerView(characterView),
	m_playerCharacterController(playerCharacterController)
{
}

PlayerCharacterView::~PlayerCharacterView()
{


}

void PlayerCharacterView::Render()
{
	m_characterView->GetActorView()->Render();


	

	for (unsigned int i = 0; i < m_characterView->GetAbilityViews()->size(); i++)
	{
		m_characterView->GetAbilityViews()->at(i)->Render();
	}
	//m_abilityViews.at(abilitySlotBasicAttack)->Render();
	//m_abilityViews.at(abilitySlot1)->Render();
	//m_abilityViews.at(abilitySlot2)->Render();
	//m_abilityViews.at(abilitySlot3)->Render();
	//m_abilityViews.at(abilitySlot4)->Render();
	//m_abilityViews.at(abilitySlot5)->Render();
	//m_abilityViews.at(abilitySlot6)->Render();
	//m_abilityViews.at(abilitySlotRecall)->Render();
	//m_abilityViews.at(abilitySlotSleep)->Render();
	//m_abilityViews.at(abilitySlot1)->Render();

}

PlayerCharacterController * PlayerCharacterView::GetPlayerCharacterController(){ return m_playerCharacterController; }
