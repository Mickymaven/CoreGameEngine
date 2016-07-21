#if !defined(CHARACTERACTIONS_H)
#define CHARACTERACTIONS_H
#include <string>
using std::string;

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

class CharacterActionStrings
{
public:
	static const string m_name[characterActionCount];
};
#endif