#include "UITab.h"

UITab::UITab()
{
	m_target = nullptr;
	m_hasLabel = false;
}

UITab::UITab(UIContentArea * target, float width, float height, string path) :UIButton(width, height, path)
{
	m_target = target;
	m_hasLabel = false;

	m_label.SetWidth(width);
	m_label.SetHeight(height);
}

UITab::~UITab()
{

}

bool UITab::Init(FontGroup * font, string * text)
{
	RECT r = {0,0,0,0};

	if (font==nullptr || text ==nullptr) m_hasLabel = false;//bad init for a label
	else if (!m_label.Init(r, font, text) ) { m_hasLabel = false; return false; }
	else m_hasLabel = true;




	if (m_target == NULL) return false;
	if (!UIElement::Init()) return false;

	return true;
}

void UITab::Render()
{
	UIElement::Render();
	if (m_hasLabel) m_label.Render();
}

void UITab::Select(POINT * p)
{
	if (IsPointInBounds(p))
	{
		m_selectPageFunction(m_target);
	}
}

void UITab::AltSelect(POINT * p)
{

}

void UITab::SetCallbackSelectPage(std::function<bool(UIContentArea*)> f)
{
	m_selectPageFunction = f;
}

/* label could be invalid
UILabel * UITab::GetLabel()
{
	return &m_label;
}*/

void UITab::SetBounds(long left, long top, long right, long bottom)
{
	UIBase::SetBounds(left, top, right, bottom);
	m_label.SetBounds(left +10, top +10, right-10, bottom-10);
}
