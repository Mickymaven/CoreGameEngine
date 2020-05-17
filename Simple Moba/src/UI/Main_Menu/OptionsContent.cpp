#include "OptionsContent.h"

OptionsContent::OptionsContent()
{

}

OptionsContent::OptionsContent(const OptionsContent & k)
{

}

OptionsContent::~OptionsContent()
{

}

bool OptionsContent::Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds)
{
	UIContentArea::Init();

	m_name = "Gameplay Options";

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
	label->Init(rect, &theme->m_settingsLabel, new string("Game Option 1"));//todo new keyword
	label->SetWidth(150.0f);
	label->SetHeight(50.0f);
	m_row->push_back(label);

	checkBox = new UICheckBox(false, 50.0f, 50.0f);
	m_row->push_back(checkBox);

	cat->allRows.push_back(*m_row);

	PositionContent(bounds);

	return true;
}

void OptionsContent::PositionContent(LMVector4 * bounds)
{
	PositionCategoryLayout(bounds);
}

void OptionsContent::Render()
{
	CategoryLayoutRender();
}

void OptionsContent::Select(POINT * p)
{

}

void OptionsContent::AltSelect(POINT * p)
{

}
