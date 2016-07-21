#include "InputModel.h"

InputModel::InputModel()
{
	m_state = 0;
}

bool InputModel::Init(string path)
{


	return true;
}

InputModel::~InputModel()
{

}

vector<int> * InputModel::GetVectorForCurrentState()
{
	return &m_actionsforState.at(m_state);
}

void InputModel::SetState(int state)
{
	m_state = state;
}