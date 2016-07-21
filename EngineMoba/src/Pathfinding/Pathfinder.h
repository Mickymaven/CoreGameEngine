#if !defined(PATHFINDER_H)
#define PATHFINDER_H

#include <Windows.h>
//#include <unordered_map>
//#include <unordered_set>

#include <deque>
using std::deque;

#include <vector>
using std::vector;

#include <functional>
using namespace std::placeholders;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"


/*
template<typename L>

struct MyGraph
{
	typedef L Location;
	typedef typename vector<Location>::iterator iterator;
	unordered_map<Location, vector<Location>> edges;

	inline const vector<Location> neighbours(Location id)
	{
		return edges[id];
	}
};

struct PathNode
{
	PathNode::PathNode(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	
	LMVector3 position;
	bool checked;
};
*/

class Pathfinder
{
private:


	std::function<void(vector<LMVector3*>* pathOut, LMVector3 * position, LMVector3 * target)> m_optimiseFunction;

	//static PathRendering * m_pathRendering;

	char node_buffer[500];

	//SpriteView * m_groundView;

	//vector<PathNode*> n;

	vector<LMVector3>nodes;

	//MyGraph<PathNode*> path_graph;

	vector<vector<LMVector3*>> m_graph;

	deque<vector<LMVector3*>*> m_openList;
	deque<vector<LMVector3*>*> m_closedList;

	//vector<LMVector3 *> * m_tempPathOut;
	vector<vector<LMVector3*>*> m_tempGraph;// (closed list)

	//
	//D3DXVECTOR3 point1;
	//D3DXVECTOR3 point2;
	//vector<LMVector3> m_hitPoints;

public:
	Pathfinder();
	void InitGraph();

	~Pathfinder();

	void GeneratePath(vector<LMVector3 *> * pathOut, LMVector3 * position, LMVector3 * target);

	void Search(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * targetNode, LMVector3 * position, LMVector3 * target);
	vector<LMVector3*> * VectorForNode(LMVector3 * node);
	void StoreClosedListInPath(vector<LMVector3 *> * pathOut, LMVector3 * position, LMVector3 * target);
	
	//
	bool IsVisualRangeNeighbour(LMVector3 * parentNode, LMVector3 * targetNode);

	template <typename MyGraph>
	void Search2(MyGraph graph, typename MyGraph::Location start);
	
	//access
	deque<vector<LMVector3*>*> * GetClosedList();

	//mutators
	void SetOptimiseFunction(std::function<void(vector<LMVector3*>* pathOut, LMVector3 * position, LMVector3 * target)> f);

};

#endif