#include "NPCViewFactory.h"
#include "PlayerCharacterViewFactory.h"

NPCViewFactory::NPCViewFactory()
{
	//*m_characterView = nullptr;
}

NPCViewFactory::~NPCViewFactory()
{

}

bool NPCViewFactory::Init(CharacterViewFactory * characterViewFactory)
{
	m_characterViewFactory = characterViewFactory;
	return true;
}

bool NPCViewFactory::ConstructNPCView(
	LPDIRECT3DDEVICE9 device,
	NPCView ** npcViewOut,
	NPCController * npcController,
	const CharacterClassName characterClass,
	vector<AbilityName> * customAbilities,
	ViewProfile * viewProfile,
	ThemeResources * theme,
	LMVector4 * bounds
)
{
	NPCView * npcView = nullptr;
	CharacterView * characterView = nullptr;

	if (!m_characterViewFactory->ConstructCharacterView(
		device, &characterView, npcController->GetCharacter(),
		characterClass, customAbilities)) return false;

	npcView = new NPCView(npcController, characterView);

	*npcViewOut = npcView;
	return true;
}