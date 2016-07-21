#if !defined (BASICGAMEEDITOR_H)
#define BASICGAMEEDITOR_H

#include "NodeEditor.h"

class BasicGameEditor
{

private:
	NodeEditor m_nodeEditor;
public:
	BasicGameEditor();
	~BasicGameEditor();

	NodeEditor * GetNodeEditor();
};


#endif