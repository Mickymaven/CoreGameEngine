#if !defined(MODECONFIGURATIONFACTORY_H)
#define MODECONFIGURATIONFACTORY_H


#include "../ModeConfig/BarebonesConfigForStandard.h"
#include "../ModeConfig/TabulaRasaConfigForStandard.h"
#include "../ModeConfig/BarebonesConfigForOpenWorld.h"

#include "../../GameConfiguration.h"

enum CreateModeCode
{
	createModeCodeOK,
	createModeCodeFail,
	createModeCodeCount
};

class ModeConfigurationFactory
{
protected:
	BaseMapConfigForMode * constructedConfig;

public:

	ModeConfigurationFactory();
	~ModeConfigurationFactory();

	CreateModeCode CreateModeConfiguration(BaseMapConfigForMode** modeOut, GameConfiguration * gameConfiguration);

};

#endif