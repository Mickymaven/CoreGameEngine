#if !defined(SHOPMENUINPUTMODEL_H)
#define SHOPMENUINPUTMODEL_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

enum ShopMenuAction
{
	shopActionClose,
	shopActionConfirmPreOrder,
	shopActionCancelPreOrder,
	shopActionConfirmTrade,
	shopActionCancelTrade,
	shopActionLeftMouse,
	shopActionRightMouse,
	shopActionCount
};

class ShopMenuInputModel : public InputModel
{
public:
	ShopMenuInputModel();
	bool Init(string path);
	~ShopMenuInputModel();
};

#endif;