#if !defined(UITAB_H)
#define UITAB_H

#include "UIButton.h"
#include "UIContentArea.h"
#include "UILabel.h"

class UITab : public UIButton
{
protected:
	UIContentArea * m_target;
	std::function<bool(UIContentArea  * contentArea)> m_selectPageFunction;

	bool m_hasLabel;
	UILabel m_label;

public:
	UITab();
	UITab(UIContentArea * target, float width, float height, string path);
	~UITab();

	bool Init(FontGroup * font, string * text);

	void Render();

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);

	void SetCallbackSelectPage(std::function<bool(UIContentArea*)> f);

	//UILabel * GetLabel();

	void SetBounds(long left, long top, long right, long bottom);


};

#endif