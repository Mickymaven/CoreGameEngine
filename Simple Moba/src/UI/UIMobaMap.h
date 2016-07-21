#if !defined (UIMOBAMAP_H)
#define UIMOBAMAP_H

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../../../CoreGame/src/GameConfiguration.h"
#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../UI_Base/UIGameMap.h"
#include "../../../EngineGameModuleDirectX9/src/Graphics/Billboard.h"

//#include "../GameControl/PlayerWorldSelectionController.h"


class UIMobaMap : public UIGameMap
{
private:
protected:
	GameConfiguration * gameConfiguration;
	StandardMatch5v5State * gameState;

	vector< vector <PlayerCharacterController *> *> m_playerTeams;
	vector< vector <UIElement >> m_playerIcons;

	LMVector2 m_positionMax;
	LMVector3 m_targetPosition;

public:
	UIMobaMap();
	~UIMobaMap();
	bool Init(StandardMatch5v5State * gameStateIn, GameConfiguration * gameConfigurationIn);

	void Update(float deltaTime);
	void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	bool ActionAltSelect(POINT * p, Billboard * walkIndicator);
};

#endif