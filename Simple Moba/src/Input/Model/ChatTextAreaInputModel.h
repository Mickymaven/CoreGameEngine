#if !defined(CHATTEXTAREAINPUTMODEL_H)
#define CHATTEXTAREAINPUTMODEL_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

enum ChatTextAreaAction
{
	chatTextAreaActionOpen,
	chatTextAreaActionSelect,
	chatTextAreaActionClose,
	chatTextAreaActionSend,
	chatTextAreaActionLeft,
	chatTextAreaActionRight,
	chatTextAreaActionBackspace,
	chatTextAreaActionCount
};

class ChatTextAreaInputModel : public InputModel
{
public:
	ChatTextAreaInputModel();
	bool Init(string path);
	~ChatTextAreaInputModel();
};

#endif