#if !defined(INPUTMODEL_H)
#define INPUTMODEL_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "InputKeyDefines.h"

class InputModel
{ 
public:
	string m_path;
	vector<string> * m_name;
	//const string m_name[characterActionCount];
	vector<int> m_keybinds;
	vector<int> m_spamFlags;

	int m_state;
	vector<vector<int>> m_actionsforState;

	InputModel();
	virtual bool Init(string path);
	~InputModel();

	

	vector<int> * GetVectorForCurrentState();
	void SetState(int state);

	string GetPath();
};

#endif