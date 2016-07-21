#if !defined(CURSORCONTROLLER_H)
#define CURSORCONTROLLER_H

#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputKeyDefines.h"
#include "../GamestateView/MobaViewState.h"
#include "../UI/GameCursor.h"
#include "../ViewControl/CameraDirector.h"
#include "../GameControl/PlayerWorldSelectionController.h"


class CursorController
{
public:
	static GameInputController * m_gameInputController;


private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;

	PlayerWorldSelectionController * m_playerWorldSelectionController;
	PlayerCharacterView * m_pcView;
	NPCView * m_npcView;
	VitalEntityView * m_tempVE;


	CastTestResult m_castTestResultOpponent;
	CastTestResult m_castTestResultNeutral;
	CastTestResult m_castTestResultTeam;
	CastTestResult m_castTestResultGround;


	CameraDirector * cameraDirector;
	GameCursor * m_cursor;

	D3DXVECTOR4 * ResultPoint;
	D3DXVECTOR3 point1, point2;

	

public:
	CursorController();
	~CursorController();


	void Init(MobaViewState * gameViewIn, StandardMatch5v5State * gameStateIn, PlayerWorldSelectionController * playerWorldSelectionController);

	void Update(float deltaTime);
	GameCursorTypes WhichCursorShouldIShow();

	CastTestResult TestOpponentReturningCastTest();
	CastTestResult TestNPCsReturningCastTest();
	CastTestResult TestTeamReturningCastTest();
	CastTestResult TestGroundReturningCastTest();
	CastTestResult TestEntitiesReturningCastTest();

	bool TestOpponentReturningBool();
	bool TestTeamReturningBool();
	bool TestEntitiesReturningBool();

};



#endif
