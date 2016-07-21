#include "ShopMenuInputModel.h"

ShopMenuInputModel::ShopMenuInputModel()
{

}

bool ShopMenuInputModel::Init(string path)
{

	m_path = "Resources/Settings/ShopMenuInput.keys";

	m_keybinds.resize(shopActionCount);
	m_keybinds[shopActionClose] = DIK_I;
	m_keybinds[shopActionConfirmPreOrder] = DIK_P;
	m_keybinds[shopActionCancelPreOrder] = DIK_R;
	m_keybinds[shopActionConfirmTrade] = DIK_B;
	m_keybinds[shopActionCancelTrade] = DIK_N;
	m_keybinds[shopActionLeftMouse] = MO_LEFT_BUTTON;
	m_keybinds[shopActionRightMouse] = MO_RIGHT_BUTTON;

	m_spamFlags.resize(shopActionCount, 0);

	vector<int> full
	{
		shopActionClose,
		shopActionConfirmPreOrder,
		shopActionCancelPreOrder,
		shopActionConfirmTrade,
		shopActionCancelTrade,
		shopActionLeftMouse,
		shopActionRightMouse
	};

	m_actionsforState.resize(1);

	m_actionsforState.at(0) = full;

	return true;
}

ShopMenuInputModel::~ShopMenuInputModel()
{

}