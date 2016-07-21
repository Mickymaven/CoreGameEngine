#if !defined (CHATTEXTAREAINPUTSET_H)
#define CHATTEXTAREAINPUTSET_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"

#include "../../../../CoreGame/src/Gamestate/CoreGameState.h"
#include "../../GamestateView/MobaViewState.h"

#include "../../UI/UIChat.h"
#include "../Model/ChatTextAreaInputModel.h"

class ChatTextAreaInputSet : public InputSet
{
private:
	CoreGameState * gameState;
	MobaViewState * gameView;

	UIChat * m_uiChat;

public:
	ChatTextAreaInputSet();
	ChatTextAreaInputSet(CoreGameState * state, MobaViewState * view);
	~ChatTextAreaInputSet();

	void Update(float deltaTime);
	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);
	void Finally(float deltaTime);

};

#endif