#if !defined(CHARACTERCONTROLLERVIEW_H)
#define CHARACTERCONTROLLERVIEW_H

#include "../../../EngineGameModel/src/Maths/LMVector4.h"

#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"

#include "CharacterView.h"
#include "TradeInventoryView.h"

class CharacterControllerView
{
protected:
	CharacterView * m_characterView;
	TradeInventoryView m_tradeInventoryView;

public:
	CharacterControllerView();
	CharacterControllerView(CharacterView * characterView);
	~CharacterControllerView();

	bool InitTradeView(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds, vector<ShopInventoryView*> * shopViews);

	virtual void Render() = 0;

	CharacterView * GetCharacterView();

	TradeInventoryView * GetTradeInventoryView();
};

#endif