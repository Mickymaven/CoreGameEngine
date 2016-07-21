#if !defined(TOOLTIPINFOITEM_H)
#define TOOLTIPINFOITEM_H

#include <vector>
using std::vector;

#include "TooltipInfo.h"

struct TootipItemStat
{
	float fNumber;
	string number;
	string name;
};

class TooltipInfoItem : public TooltipInfo
{
public:
	static UIElement m_background;
	protected:

		vector < TootipItemStat > * m_stats;
		vector < TooltipEffect > * m_effects;

	public:
		TooltipInfoItem();
		~TooltipInfoItem();

		void Render();

		//accessors
		UIElement * GetBackground();

		//mutators
		void SetStats(vector<TootipItemStat> * stats);
		void SetEffects(vector<TooltipEffect> * effects);
};


#endif