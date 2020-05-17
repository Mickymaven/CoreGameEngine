#if !defined(PATHFINDER_H)
#define PATHFINDER_H

#include <Windows.h>

#include <unordered_map>
using std::unordered_map;

//#include <unordered_set>

#include <deque>
using std::deque;

#include <vector>
using std::vector;

#include <functional>
using namespace std::placeholders;

#include <queue>
using std::priority_queue;


#include "../../../EngineGameModel/src/Maths/LMVector3.h"


#include "../../../EngineGameModel/src/Maths/LMNode.h"
#include "../../../EngineGameModel/src/Maths/LMNodeGraph.h"
#include "../../../EngineGameModel/src/Maths/LMNodeMap.h"


/*


struct SimpleGraph {
	std::unordered_map<char, std::vector<char> > edges;

	std::vector<char> neighbors(char id) {
		return edges[id];
	}
};

std::priority_queue

struct MyGraph
{
	typedef L Node;
	typedef typename vector<Node>::iterator iterator;
	unordered_map<Node, vector<Node>> edges;

	inline const vector<Node> neighbours(Node id)
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

//template<typename T, typename priority_t>
class Pathfinder
{
private:


	std::function<void(vector<LMVector3*>* pathOut, LMVector3 * position, LMVector3 * target)> m_optimiseFunction;


	vector<LMVector3*> m_bestNodes;
	vector<float> m_bestNodeDistances;

	char node_buffer[500];

	vector<LMVector3>nodes;

	vector<vector<LMVector3*>> m_graph;

	deque<vector<LMVector3*>*> m_openList;
	deque<vector<LMVector3*>*> m_closedList;

	vector<vector<LMVector3*>*> m_tempGraph;// (closed list)


	vector<vector<LMVector3*>> m_neighbours;

	LMNodeMap<LMVector3*> m_nodeMap;

	//std::unordered_map<LMVector3 &, LMVector3 &> came_from;
	//std::unordered_map<LMVector3 &, float> cost_so_far; //storage of g (for f=g+h)

	
	//typedef std::pair<priority_t, T> PQElement;
	/*
	std::priority_queue<
		
		PQElement,
		std::vector<PQElement>,
		std::greater<PQElement>					
		> m_open1;
	
	std::priority_queue<

		PQElement,
		std::vector<PQElement>,
		std::greater<PQElement>
	> m_closed1;
	*/


public:
	Pathfinder();
	void InitGraph();

	~Pathfinder();

	void GeneratePath(vector<LMVector3 *> * pathOut, LMVector3 * position, LMVector3 * target);

	void Search(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target);
	
	void SearchMarch19(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target);
	void Search1(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target);
	void Search2(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target);

	void SearchMaze19(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target);


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