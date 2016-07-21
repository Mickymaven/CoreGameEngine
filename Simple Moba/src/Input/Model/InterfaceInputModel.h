#if !defined(INTERFACEINPUTMODEL_H)
#define INTERFACEINPUTMODEL_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

enum InterfaceAction
{
	interfaceActionSelect,
	interfaceActionAltSelect,
	interfaceActionCount
};

class InterfaceInputModel : public InputModel
{
public:
	InterfaceInputModel();
	bool Init(string path);
	~InterfaceInputModel();
};

#endif;