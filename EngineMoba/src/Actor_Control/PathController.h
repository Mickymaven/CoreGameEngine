#if !defined(PATHCONTROLLER_H)
#define PATHCONTROLLER_H

#include <vector>
using std::vector;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineMoba/src/Pathfinding/Pathfinder.h"
#include "WalkState.h"

enum PathState
{
	pathStateStandby,
	pathStateRequestPath,
	pathStateNavigate,
	pathStateAlternativePath,
	pathStateCount

};

class PathController
{
private:
	PathState m_state;
	Actor *  m_owner;

	bool m_isEnabled;

	static Pathfinder * sm_pathfinder;
	WalkState * m_walkState;

	vector<LMVector3 *> m_currentPath;
	LMVector3 * m_nextNode;

	int m_nextNodeIndex;

	LMVector3 m_endpoint;

public:
	PathController();
	PathController(Pathfinder * pathfinder, WalkState * walkState, Actor *  owner);
	~PathController();

	void Update(float deltaTime);
	void Render();

private:
	void OnEnterStandby();
	void Standby(float deltaTime);
	void OnExitStandby();

	void OnEnterRequestPath();
	void RequestPath(float deltaTime);
	void OnExitRequestPath();

	void OnEnterNavigate();
	void Navigate(float deltaTime);
	void OnExitNavigate();

	void OnEnterAlternativePath();
	void AlternativePath(float deltaTime);
	void OnExitAlternativePath();

	void ExitCurrentState();

public:

	void SetToStandby();
	bool WalkToPosition(bool ignoreRateLowering, LMVector3 * target, LMVector3 * origin);

	PathState GetState();

	bool GetIsEnabled();
	void SetEnabled(bool newEnabledState);
};

#endif