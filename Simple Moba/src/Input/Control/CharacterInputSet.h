#if !defined(CHARACTERINPUTSET_H)
#define CHARACTERINPUTSET_H

#include "../../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../../EngineMoba/src/Actors/Actor.h"
#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"

#include "../../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../../../CoreGame/src/Gameplay/Characters/CoreCharacter.h"
#include "../../ViewControl/CameraDirector.h"
#include "../../GamestateView/MobaViewState.h"
#include "../../GameplayView/NPCView.h"
#include "../Model/CharacterInputModel.h"

#include "../../GameControl/PlayerWorldSelectionController.h"

class CharacterInputSet : public InputSet
{
private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;

	PlayerWorldSelectionController * m_playerWorldSelectionController;

	CameraDirector * m_cameraDirector;
	Character * playerCharacter;

	LMCamera * cam3p;
	char keyMoveAction;
	Actor * target;
	
	VitalEntity * basicAttackTarget;
	PlayerCharacterController * targetPlayerCharacterController;
	bool m_mouseUpDuringAMInitialClick;
	D3DXVECTOR4 * ResultPoint;
	D3DXVECTOR3 point1, point2;
	LMVector3 tempVec3;

	//select with mouse temp
	PlayerCharacterView * pcView;
	NPCView * npcView;
	LMVector3 pointHere;
	//bool selectWithMouse;
	
	//walk or basic temp
	VitalEntityView * veView;
	LMVector3 walkTarget;

public:
	CharacterInputSet();
	CharacterInputSet(StandardMatch5v5State * state, MobaViewState * view, PlayerWorldSelectionController * playerWorldSelectionController);
	~CharacterInputSet();

	void Update(float deltaTime);

	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);

};

#endif