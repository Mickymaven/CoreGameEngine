#if !defined(KEYDIALOGINPUTSET_H)
#define KEYDIALOGINPUTSET_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"
#include "../../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../GamestateView/MobaViewState.h"
#include "../../UI_Base/UIKeyDialog.h"
#include "../Model/KeyDialogInputModel.h"

class KeyDialogInputSet : public InputSet
{
private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;

	UIKeyDialog * m_keyDialog;

public:
	KeyDialogInputSet();
	KeyDialogInputSet(StandardMatch5v5State * state, MobaViewState * view);
	~KeyDialogInputSet();

	void Update(float deltaTime);
	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);
	void Finally(float deltaTime);

};

#endif