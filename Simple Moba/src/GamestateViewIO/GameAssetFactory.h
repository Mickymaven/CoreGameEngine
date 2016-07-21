#if !defined(GAMEASSETFACTORY_H)
#define GAMEASSETFACTORY_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"
#include "../../../CoreGame/src/Gamestate/AssetMeshNameEnum.h"

class GameAssetFactory
{
private:
	LPDIRECT3DDEVICE9 m_device;
	vector<LMMesh *> m_assetMeshes; //Lightweight Assets
	vector<LMMesh *> m_characterMeshes; //Lightweight Assets

public:
	GameAssetFactory();
	~GameAssetFactory();

	void Init(LPDIRECT3DDEVICE9 device);

	UIElement * GetCharacterIcon(CharacterClassName nameEnum);
	LMMesh * GetActorMesh(CharacterClassName nameEnum);
	LMMesh * GetAssetMesh(AssetMeshName nameEnum); //Lightweight Assets
};

#endif