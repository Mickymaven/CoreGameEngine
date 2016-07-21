#if !defined (PLAYERCHARACTERVIEWFACTORY_H)
#define PLAYERCHARACTERVIEWFACTORY_H

#include <d3dx9.h>

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../../../CoreGame/src/Gameplay/Characters/AbilitySlotType.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterData.h"
#include "../../../CoreGame/src/Gameplay/Abilities/AbilityName.h"
#include "../GameplayView/PlayerCharacterView.h"
#include "AbilityViewFactory.h"
#include "CharacterViewFactory.h"

class PlayerCharacterViewFactory
{
private:
	CharacterViewFactory * m_characterViewFactory;

public:
	PlayerCharacterViewFactory();
	~PlayerCharacterViewFactory();

	bool Init(CharacterViewFactory * characterViewFactory);

	bool ConstructPlayerCharacterView(
		LPDIRECT3DDEVICE9 device,
		PlayerCharacterView ** playerCharacterViewOut,
		PlayerCharacterController * playerCharacterController,
		const CharacterClassName characterClass,
		vector<AbilityName> * customAbilities,
		ViewProfile * viewProfile,
		ThemeResources * theme,
		LMVector4 * bounds);
};

#endif