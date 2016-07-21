#if !defined(UIGAMEMAP_H)
#define UIGAMEMAP_H

#include <vector>
using std::vector;

#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h" 
#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"

class UIGameMap : public UIArea
{
private:
protected:
	vector <UIElement> m_icons;
	UIElement m_background;

	LMVector3 m_mapOrigin;
	LMVector3 m_mapSize;

public:
	UIGameMap();
	~UIGameMap();
	bool Init();

	LMVector3 * GetMapOrigin();
	LMVector3 * GetMapSize();
};

#endif