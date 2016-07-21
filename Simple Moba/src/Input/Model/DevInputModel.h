#if !defined(DEVINPUTMODEL_H)
#define DEVINPUTMODEL_H

enum DevAction
{
	devActionLevelCharacter,
	devActionTeleportChar,
	devActionHalfHealth,
	devTogglePathEnabled,
	devActionToggleDebugText,
	devActionCount
};

#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"


class DevInputModel : public InputModel
{
public:
	DevInputModel();
	bool Init(string path);
	~DevInputModel();
};

#endif;