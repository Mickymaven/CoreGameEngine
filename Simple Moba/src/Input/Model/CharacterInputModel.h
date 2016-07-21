#if !defined(CHARACTERINPUTMODEL_H)
#define CHARACTERINPUTMODEL_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

#include "../../../../EngineMoba/src/Actors/Actor.h"//for actor state

enum CharacterAction
{
	//third person view
	characterActionKeyMoveLeft,
	characterActionKeyMoveRight,
	characterActionKeyMoveUp,
	characterActionKeyMoveDown,

	//regular actions
	characterActionSelectWithMouse,//usually left click
	characterActionWalkOrBasicAttack, //usually right click

	characterActionStop,
	characterActionAttackMove,
	characterActionDriveByMove,

	characterActionCastRecall,
	characterActionCastSleep,

	characterActionCastAbility1,
	characterActionCastAbility2,
	characterActionCastAbility3,
	characterActionCastAbility4,
	characterActionCastAbility5,
	characterActionCastAbility6,

	characterActionInventory1,
	characterActionInventory2,
	characterActionInventory3,
	characterActionInventory4,
	characterActionInventory5,
	characterActionInventory6,
	characterActionInventory7,
	characterActionInventory8,
	characterActionInventory9,
	characterActionInventory0,

	characterActionCount
};

class CharacterInputModel : public InputModel
{
public:
	CharacterInputModel();
	bool Init(string path);
	~CharacterInputModel();
};

#endif