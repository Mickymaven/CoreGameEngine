#if !defined(INPUTSET_H)
#define INPUTSET_H

#include <vector>
using std::vector;

#include "../Application/Globals.h"
#include "InputModel.h"

#include "GameInputController.h"

class InputSet
{
protected:
	static GameInputController * sm_gameInputController;
	InputModel * m_model;



public:
	InputSet();
	~InputSet();

	virtual void Update(float deltaTime);
	virtual void AttemptAction(int action, float deltaTime);
	virtual void SpamAction(int action, float deltaTime);
	virtual void Finally(float deltaTime);

	void SetModel(InputModel * model);

	static void SetInputController(GameInputController * m_gameInputController);
};

#endif