#if !defined (PATHOPTIMISER_H)
#define PATHOPTIMISER_H

#include <deque>
using std::deque;

#include <vector>
using std::vector;

#include <windows.h>

#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineMoba/src/Pathfinding/Pathfinder.h"

#include "../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

#include "PathRendering.h"

class PathOptimiser
{
	static PathRendering * m_pathRendering;
	
	Pathfinder * m_pathFinder;
	SpriteView * m_groundView;

	deque<vector<LMVector3*>*> * m_closedList;

	vector<vector<LMVector3*>*> m_tempGraph;// (closed list)
	vector<vector<LMVector3*>*> m_tempGraphOptimised;// (closed list)

	LMVector3 m_origin;
	LMVector3 m_target;

	D3DXVECTOR3 point1;
	D3DXVECTOR3 point2;
	vector<LMVector3> m_hitPoints;

public:
	PathOptimiser();
	~PathOptimiser();

	void Init(Pathfinder * pathfinder, SpriteView * groundView);

	void Render();

	void OptimisePath(
		vector<LMVector3*> * pathOut,
		LMVector3 * position,
		LMVector3 * target
		);

	bool IsVisualRangeNeighbour(LMVector3 * parentNode, LMVector3 * targetNode);




};

#endif