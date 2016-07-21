#if !defined(KEYDIALOGINPUTMODEL_H)
#define KEYDIALOGINPUTMODEL_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

enum KeyDialogAction
{
	keyDialogActionSelect,
	keyDialogActionClose,
	keyDialogActionFinally,
	keyDialogActionCount
};

class KeyDialogInputModel : public InputModel
{
public:
	KeyDialogInputModel();
	bool Init(string path);
	~KeyDialogInputModel();
};

#endif