#if !defined(LMNODEGRAPH_H)
#define LMNODEGRAPH_H

#include <vector>
using std::vector;

#include "LMNode.h"

class LMNodeGraph
{
protected:
	LMNode m_parent;
	vector<LMNode*> m_children;

public:
	LMNodeGraph();
	~LMNodeGraph();

	void push_back(LMNode & value);

	vector<LMNode*> & Children();
	LMNode & Parent();


};

#endif