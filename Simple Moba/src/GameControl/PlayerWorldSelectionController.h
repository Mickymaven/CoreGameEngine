#if !defined(PLAYERWORLDSELECTIONCONTROLLER_H)
#define PLAYERWORLDSELECTIONCONTROLLER_H


#include <vector>
using std::vector;

#include <d3dx9math.h>


#include "../../../EngineGameModel/src/Maths/LMVector3.h"

#include "../../../EngineMoba/src/GameControl/QuestItemController.h"

//#include "../../../CoreGame/src/Gamestate/CoreGameState.h"
#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"

#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"



#include "../../../EngineGamePlatform/src/Application/Globals.h"

#include "../GamestateView/MobaViewState.h"
#include "../Graphics/GraphicsAlgorithms.h"
#include "../GameplayView/PlayerCharacterView.h"
#include "../GameplayView/NPCView.h"
#include "../GameplayView/VitalEntityView.h"
#include "../GameplayView/ItemEntityView.h"


enum SelectActions
{
	selectActionNothing,

	selectActionQuerySelectTeam,
	selectActionQuerySelectOpponent,
	selectActionQuerySelectNeutral,
	selectActionQuerySelectNeutralObjects,
	selectActionQuerySelectQuestItems,
	selectActionQuerySelectGround,


	selectActionControlledSelectTeam,
	selectActionControlledSelectOpponent,
	selectActionControlledSelectNeutral,
	selectActionControlledSelectNeutralObjects,
	selectActionControlledSelectQuestItems,
	selectActionControlledSelectGround,

	selectActionControlledAltSelectTeam,
	selectActionControlledAltSelectOpponent,
	selectActionControlledAltSelectNeutral,
	selectActionControlledAltSelectNeutralObjects,
	selectActionControlledAltSelectQuestItems,
	selectActionControlledAltSelectGround,

	selectActionsCount
};

enum CheckFlags
{
	checkFlagCameraRayMade,
	checkFlagOpponentChecked,
	checkFlagTeamChecked,
	checkFlagNeutralsChecked,
	checkFlagNeutralObjectsChecked,
	checkFlagGroundChecked,
	checkFlagCount
};

//Players World Selection that we are kind of managing the stuff for.

//do not access data until after CameraInputSet Update happens.

class PlayerWorldSelectionController
{
protected:
	StandardMatch5v5State * gameModel;
	MobaViewState * gameView;

	QuestItemController m_questItemController;
	
	bool m_cameraRayMade;
	bool m_opponentChecked;
	bool m_teamChecked;
	bool m_neutralsChecked;
	bool m_questItemsChecked;
	bool m_neutralObjectsChecked;
	bool m_groundChecked;
	

	PlayerCharacterView * m_opponent;
	PlayerCharacterView * m_team;
	NPCView * m_neutral;
	
	ItemEntityView * m_questItem;
	int m_questViewItemIndex;
	QuestView * m_questView;

	VitalEntityView * m_neutralObject;
	bool m_validgroundPoint;
	LMVector3 m_groundPos;

	D3DXVECTOR4 ResultPoint;
	D3DXVECTOR3 point1;
	D3DXVECTOR3 point2;
	D3DXVECTOR3 point1TempLocal;
	D3DXVECTOR3 point2TempLocal;
	Actor * tempActorTarget;
	VitalEntity * tempVitalEntityTarget;
	int m_tempOutIndex;

	CastTestResult m_lastCastTestResult;

public:
	PlayerWorldSelectionController();
	~PlayerWorldSelectionController();

	bool Init(
		StandardMatch5v5State * coreGameStateIn,
		MobaViewState * mobaViewStateIn );

	void Update(float deltaTime);

	void SelectAction(SelectActions selectAction);
	void GenerateCameraRay();
	void CopyCameraRayToTempLocal();
	
	bool Pick(D3DXMATRIX * world, LMMesh * mesh, int index);
	bool TestActorControllerViews(vector <CharacterControllerView * > * views);
	bool TestVitalEntityViews(vector <VitalEntityView* > * views);
	bool TestItemEntityViews(vector <ItemEntityView> * views);
	bool TestSpriteViewForPosition(SpriteView * spriteView);
	

	bool OpponentTarget(PlayerCharacterView ** targetView, SelectActions action);
	bool TeamTarget(PlayerCharacterView ** targetView, SelectActions action);
	bool NPCTarget(NPCView ** targetView, SelectActions action);
	bool NeutralObjectTarget(VitalEntityView ** targetView, SelectActions action);
	bool QuestItemTarget(ItemEntityView ** targetView, SelectActions action);


	bool GroundPointWithScreen(LMVector3*targetPosition, SelectActions action);//for screen clicks to world
	//bool GroundPoint(LMVector3*targetPosition, SelectActions action); //used once you have a world position (check height okay)

	CastTestResult GetCastTestResult();
};


#endif