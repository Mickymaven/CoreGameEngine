#if !defined(ACTORVIEWFACTORY_H)
#define ACTORVIEWFACTORY_H

#include <vector>
using std::vector;


#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"
#include "../GameplayView/ActorView.h"


class ActorViewFactory
{
private:
	
	LMMesh * m_actorMesh;

	vector<LMMesh*> m_characterMeshes;

public:
	ActorViewFactory();
	~ActorViewFactory();

	bool ConstructActorView(LPDIRECT3DDEVICE9 device, ActorView ** actorViewOut, Actor * actor, CharacterClassName name);
	bool GetActorMesh(CharacterClassName name, LMMesh ** actorMeshOut);
};

#endif