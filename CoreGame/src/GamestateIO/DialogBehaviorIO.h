#if !defined(DIALOGBEHAVIORIO_H)
#define DIALOGBEHAVIORIO_H

#include "../../../EngineMoba/src/Actor_Control/DialogBehavior.h"
#include "../../../Simple Moba/src/GamestateViewIO/ProfileIOBase.h" // forward dependency

class DialogBehaviorIO : public ProfileIOBase
{
protected:
	DialogBehavior * m_dialogBehavior;

public:
	DialogBehaviorIO();
	~DialogBehaviorIO();

	//bool WriteData(string path, vector<int> * binds);

	bool ReadData(string path, DialogBehavior * dialogBehavior);
};

#endif