#if !defined(CAMERAINPUTSET_H)
#define CAMERAINPUTSET_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"
#include "../../../../EngineMoba/src/Actors/Actor.h"
#include "../../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../ViewControl/CameraDirector.h"
#include "../../GamestateView/MobaViewState.h"
#include "../Model/CameraInputModel.h"

class CameraInputSet : public InputSet
{
private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;

	CameraDirector * m_cameraDirector;

public:
	CameraInputSet();
	CameraInputSet(StandardMatch5v5State * state, MobaViewState * view);
	~CameraInputSet();

	void Update(float deltaTime);
	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);
	void ActionCameraFocusPlayer(unsigned int i);
	void SetCameraDirector(CameraDirector * cameraDirector);

};

#endif