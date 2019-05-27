#if !defined(BUFFVIEWFACTORY_H)
#define BUFFVIEWFACTORY_H

#include <vector>
using std::vector;

#include "../../../CoreGame/src/Gameplay/Buffs/BuffName.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../GamestateView/ViewProfile.h"
#include "../GameplayView/BuffView.h"

#include "../../../EngineGamePlatform/src/Application/Globals.h"


class BuffViewFactory
{
private:
	vector<BuffView> m_buffViews;
	ViewProfile * m_viewProfile;

public:
	BuffViewFactory();
	~BuffViewFactory();

	bool Init(ViewProfile * viewProfile);

	bool ConstructBuffView(BuffName name, BuffView ** buffViewOut);

	vector<BuffView> * GetLightweightBuffViews();

};

#endif