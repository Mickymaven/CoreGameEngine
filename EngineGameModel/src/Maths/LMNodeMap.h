#if !defined(LMNODEMAP_H)
#define LMNODEMAP_H

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include <utility> 
using namespace std;


template<typename L>

class LMNodeMap

{
protected:
	typedef L Node;
	typedef typename vector<Node>::iterator iterator;
	unordered_map<Node, vector<Node>> edges;

public:
	LMNodeMap();
	~LMNodeMap();

	const vector<L> LMNodeMap<L>::neighbours(L id);

	unordered_map<L, vector<L>> * LMNodeMap<L>::GetEdges();

};

template<typename L>
const vector<L> LMNodeMap<L>::neighbours(L id)
{
	return edges[id];
}

template<typename L>
unordered_map<L, vector<L>> * LMNodeMap<L>::GetEdges()
{
	return &edges;
}

template<typename L>
LMNodeMap<L>::LMNodeMap()
{
}

template<typename L>
LMNodeMap<L>::~LMNodeMap()
{
}

#endif

