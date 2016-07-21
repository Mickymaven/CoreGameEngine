#if !defined (NPCVIEWFACTORY_H)
#define NPCVIEWFACTORY_H

#include <d3dx9.h>

#include "../../../EngineMoba/src/Actors/NPCController.h"
#include "../../../CoreGame/src/Gameplay/Characters/AbilitySlotType.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterData.h"
#include "../../../CoreGame/src/Gameplay/Abilities/AbilityName.h"
#include "../GameplayView/NPCView.h"
#include "AbilityViewFactory.h"
#include "CharacterViewFactory.h"

class NPCViewFactory
{
private:
	CharacterViewFactory * m_characterViewFactory;

public:
	NPCViewFactory();
	~NPCViewFactory();

	bool Init(CharacterViewFactory * characterViewFactory);

	bool ConstructNPCView(
		LPDIRECT3DDEVICE9 device,
		NPCView ** npcViewOut,
		NPCController * npcController,
		const CharacterClassName characterClass,
		vector<AbilityName> * customAbilities,
		ViewProfile * viewProfile,
		ThemeResources * theme,
		LMVector4 * bounds);
};

#endif