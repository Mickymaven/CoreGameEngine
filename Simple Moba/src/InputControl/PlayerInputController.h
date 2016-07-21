#if !defined(PLAYERINPUTCONTROLLER_H)
#define PLAYERINPUTCONTROLLER_H

#include <vector>
using std::vector;

#include "../../../EngineGameModuleDirectX9/src/Input/GameInputController.h"
#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputSet.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

class PlayerInputController
{
protected:
	StandardMatch5v5State * gameState;
	GameInputController * m_gameInputController;

	vector<InputModel*> m_inputModels;
	vector<InputSet*> m_inputSets;

	//temp vars
	vector<int> * vec;
public:
	PlayerInputController();
	PlayerInputController(GameInputController * gameInputController, StandardMatch5v5State * gameStateIn);
	~PlayerInputController();

	void Update(float deltaTime);
	bool IsPressForAction(InputModel * inputSet, bool isSpamPass, int action);

	void AddInputSet(InputSet * inputSet);//be sure to add input sets in order
	void AddInputModel(InputModel * inputModel);

	string * ToString(int action);

};

#endif