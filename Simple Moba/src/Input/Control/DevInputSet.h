#if !defined(DEVINPUTSET_H)
#define DEVINPUTSET_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"
#include "../../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../GamestateView/MobaViewState.h"
#include "../Model/DevInputModel.h"

class DevInputSet: public InputSet
{

private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;

	D3DXVECTOR4 ResultPoint;
	D3DXVECTOR3 point1, point2;

public:
	DevInputSet();
	DevInputSet(StandardMatch5v5State * state, MobaViewState * view);
	~DevInputSet();

	void Update(float deltaTime);
	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);
};

#endif