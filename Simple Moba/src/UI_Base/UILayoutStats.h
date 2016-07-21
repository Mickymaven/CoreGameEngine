#if !defined(UILAYOUTSTATS_H)
#define UILAYOUTSTATS_H

#include "../../../EngineMoba/src/Actors/ActorStats.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabel.h"
#include "UILayoutGroup.h"

struct UILayoutStats: public UILayoutGroup
{
public:
	vector<UILabel> m_stats;

	UILayoutStats();
	~UILayoutStats();

	bool Init();

	void SetStatLabels(ActorStats * actorStats);

	void Update(float deltaTime);
	void Render();

};
#endif