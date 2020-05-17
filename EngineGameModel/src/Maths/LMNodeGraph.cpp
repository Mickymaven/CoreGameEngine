#include "LMNodeGraph.h"

LMNodeGraph::LMNodeGraph()
{
}

LMNodeGraph::~LMNodeGraph()
{
}

void LMNodeGraph::push_back(LMNode & value)
{
	m_children.push_back(&value);
}

vector<LMNode*>& LMNodeGraph::Children()
{
	return m_children;
	// TODO: insert return statement here
}

LMNode & LMNodeGraph::Parent()
{

	return m_parent;
	// TODO: insert return statement here
}
