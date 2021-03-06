#include "DisplayContent.h"

DisplayContent::DisplayContent()
{

}

DisplayContent::DisplayContent(const DisplayContent & k)
{

}

DisplayContent::~DisplayContent()
{

}

bool DisplayContent::Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds)
{
	UIContentArea::Init();

	m_name = "Display Options";

	m_bounds.values[0] = bounds->x;
	m_bounds.values[1] = bounds->y;
	m_bounds.values[2] = bounds->z;
	m_bounds.values[3] = bounds->w;

	m_categories.resize(1);
	ContentCat * cat = &m_categories.at(0);
	//cat->bounds = LMVector4();


	vector<UIBase*> * m_row = m_row = new vector < UIBase * >;

	RECT rect = { 0, 0, 0, 0 };

	SettingsLabel * label = NULL;
	UICheckBox * checkBox = NULL;

	label = new SettingsLabel();
	label->Init(rect, &theme->m_settingsLabel, new string("Display Option 1"));
	label->SetWidth(150.0f);
	label->SetHeight(50.0f);
	m_row->push_back(label);

	checkBox = new UICheckBox(false, 50.0f, 50.0f);
	m_row->push_back(checkBox);

	cat->allRows.push_back(*m_row);

	PositionContent(bounds);

	return true;
}

void DisplayContent::PositionContent(LMVector4 * bounds)
{
	PositionCategoryLayout(bounds);
}

void DisplayContent::Render()
{
	CategoryLayoutRender();
}

void DisplayContent::Select(POINT * p)
{

}

void DisplayContent::AltSelect(POINT * p)
{

}
