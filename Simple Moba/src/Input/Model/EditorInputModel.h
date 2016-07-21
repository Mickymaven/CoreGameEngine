#if !defined(EDITORINPUTMODEL_H)
#define EDITORINPUTMODEL_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

enum EditorAction
{
	editorActionNodeToolClick,
	editorActionToogleOn,
	editorActionGenerateNeighbours,
	editorActionGenerateFile,
	editorActionCount
};

class EditorInputModel : public InputModel
{
public:
	EditorInputModel();
	bool Init(string path);
	~EditorInputModel();
};

#endif;