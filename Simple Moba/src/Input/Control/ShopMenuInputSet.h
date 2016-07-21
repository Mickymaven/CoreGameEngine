#if !defined(SHOPMENUINPUTSET_H)
#define SHOPMENUINPUTSET_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"
#include "../../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../GamestateView/MobaViewState.h"
#include "../Model/ShopMenuInputModel.h"

class ShopMenuInputSet : public InputSet
{
private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;
	GameShopMenu * m_shopMenu;
	TradeInventoryView * m_shopView;

public:
	ShopMenuInputSet();
	ShopMenuInputSet(StandardMatch5v5State * state, MobaViewState * view);
	~ShopMenuInputSet();

	void Update(float deltaTime);
	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);
	void Finally(float deltaTime);
};

#endif