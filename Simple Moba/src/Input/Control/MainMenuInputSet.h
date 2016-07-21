#if !defined(MAINMENUINPUTSET_H)
#define MAINMENUINPUTSET_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"
#include "../../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../GamestateView/MobaViewState.h"
#include "../Model/MainMenuInputModel.h"
#include "../../UI/GameMainMenu.h"

class MainMenuInputSet : public InputSet
{

private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;
	GameMainMenu * m_mainMenu;

public:
	MainMenuInputSet();
	MainMenuInputSet(StandardMatch5v5State * state, MobaViewState * view);
	~MainMenuInputSet();

	void Update(float deltaTime);
	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);
	void Finally(float deltaTime);
};

#endif