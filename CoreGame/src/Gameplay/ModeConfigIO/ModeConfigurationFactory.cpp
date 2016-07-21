#include "ModeConfigurationFactory.h"

ModeConfigurationFactory::ModeConfigurationFactory()
{
	constructedConfig = nullptr;
}

ModeConfigurationFactory::~ModeConfigurationFactory()
{
}

CreateModeCode ModeConfigurationFactory::CreateModeConfiguration(BaseMapConfigForMode ** modeOut, GameConfiguration * gameConfiguration)
{

	int map = gameConfiguration->GetMapId();

	switch (gameConfiguration->GetGameMode())
	{
	case modeStandard:
		switch (map) {
		case gameMapTabulaRasa:{*modeOut = new TabulaRasaConfigForStandard(); break; }
		case gameMapBarebones:{*modeOut = new BarebonesConfigForStandard(); break; }
		default:return createModeCodeFail; }
	break;

	case modeOpenWorld:
		switch (map) {
		//case gameMapTabulaRasa: {*modeOut = new TabulaRasaConfigForOpenWorld(); break; }
		case gameMapBarebones: {*modeOut = new BarebonesConfigForOpenWorld(); break; }
		default:return createModeCodeFail;
		}
	break;

	default: return createModeCodeFail;
	}
	
	return createModeCodeOK;
}