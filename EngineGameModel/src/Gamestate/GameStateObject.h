#if !defined(GAMESTATEOBJECT_H)
#define GAMESTATEOBJECT_H

#include <string>
using std::string;

#include <windows.h>

enum InitMessage
{
	initMessageAbort,
	initMessageContinue,
	initMessageComplete,
	initMessageCount
};

class GameStateObject
{
protected:


	int m_loadProgress;
	int m_loadSize;

	LARGE_INTEGER m_initStart;
	LARGE_INTEGER m_initCurrent;
	char m_initBuffer[9000];
	LARGE_INTEGER m_init_tFrequency;

public:
	GameStateObject();
	~GameStateObject();


	InitMessage UpdateLoadProgress();
	virtual bool InitSelectedPhase(int initPhase);
	virtual string GetInitPhaseString(int initPhase);

	void InitDebugPrint(string s);

	int * GetLoadProgress();
	int * GetLoadSize();

	void SetLoadProgress(int loadProgress);
	void SetLoadSize(int loadSize);

};

#endif