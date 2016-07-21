#include "PlayerCharacterViewFactory.h"

PlayerCharacterViewFactory::PlayerCharacterViewFactory()
{
	//*m_characterView = nullptr;
}

PlayerCharacterViewFactory::~PlayerCharacterViewFactory()
{

}

bool PlayerCharacterViewFactory::Init(CharacterViewFactory * characterViewFactory)
{
	m_characterViewFactory = characterViewFactory;
	return true;
}

bool PlayerCharacterViewFactory::ConstructPlayerCharacterView(
	LPDIRECT3DDEVICE9 device,
	PlayerCharacterView ** playerCharacterViewOut,
	PlayerCharacterController * playerCharacterController,
	const CharacterClassName characterClass,
	vector<AbilityName> * customAbilities,
	ViewProfile * viewProfile,
	ThemeResources * theme,
	LMVector4 * bounds
	)
{
	PlayerCharacterView * playerCharacterView = nullptr;
	CharacterView * characterView = nullptr;

	if (!m_characterViewFactory->ConstructCharacterView(
		device, &characterView, playerCharacterController->GetCharacter(),
		characterClass, customAbilities)) return false;

	playerCharacterView = new PlayerCharacterView(playerCharacterController, characterView);

	*playerCharacterViewOut = playerCharacterView;
	return true;
}