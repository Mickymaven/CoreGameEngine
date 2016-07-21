#if !defined(INPUTMODELLIST_H)
#define INPUTMODELLIST_H

#include <vector>
using std::vector;

#include "InputModel.h"

class InputModelList
{
protected:
	vector<InputModel*> m_list;


public:
	InputModelList();
	~InputModelList();
	
	bool push_back(InputModel & p);

	vector<InputModel*> * GetList();



};

#endif