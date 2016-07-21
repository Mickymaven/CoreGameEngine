#if !defined(INTERFACEINPUTSET_H)
#define INTERFACEINPUTSET_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"
#include "../../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../GamestateView/MobaViewState.h"
#include "../Model/InterfaceInputModel.h"

#include "../../GameControl/PlayerWorldSelectionController.h"

class InterfaceInputSet : public InputSet
{
private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;

	PlayerWorldSelectionController * m_playerWorldSelectionController;

public:
	InterfaceInputSet();
	InterfaceInputSet(StandardMatch5v5State * state, MobaViewState * view, PlayerWorldSelectionController * playerWorldSelectionController);
	~InterfaceInputSet();

	void Update(float deltaTime);
	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);
};

#endif