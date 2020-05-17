#include "KeybindContent.h"

KeybindContent::KeybindContent()
{

}

KeybindContent::KeybindContent(const KeybindContent & k)
{

}

KeybindContent::~KeybindContent()
{

}

bool KeybindContent::Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds, vector<InputModel*> * inputModels)
{
	m_name = "Keybinds";

	m_bounds.values[0] = bounds->x;
	m_bounds.values[1] = bounds->y;
	m_bounds.values[2] = bounds->z;
	m_bounds.values[3] = bounds->w;

	/*
	m_img = UIElement(50.0f, 50.0f, "Resources/UI/Squares/Grey.png");
	if (!m_img.Init()) return false;

	UICheckBox * box = new UICheckBox(true, 30.0f, 30.0f);
	if (!box->Init()) return false;
	m_checkboxes.push_back(box);
	*/


	m_categories.resize(1);
	ContentCat * cat = &m_categories.at(0);

	cat->bounds = LMVector4();


	vector<UIBase*> * m_row = m_row = new vector < UIBase * >;


	//AspectProfile * aspect, ThemeProfile * theme,

	RECT rect = { 0, 0, 0, 0 };


	SettingsLabel * label = NULL;
	KeyLabel * bindLabel = NULL;
	// Input Category Init for mainMenuInputModel
	// Input Category Init for shopMenuInputModel
	// Input Category Init for editorInputModel
	// Input Category Init for devInputModel
	// Input Category Init for cameraInputModel
	// Input Category Init for interfaceInputModel
	
	// Input Category Init for characterInputModel

	
	m_noKeys.Init(keylistEmpty);
	m_usableKeys.Init(keylistUsable);// every key inc MMB, except ESC and L/M mouse button
	m_selectOnlyKeys.Init(keylistMouseButton12);//LMB, RMB


	for (unsigned int i = 0; i < characterActionCount; i++)
	{
		label = new SettingsLabel();
		if (!label->Init(rect, &theme->m_settingsLabel, &inputModels->at(8)->m_name->at(i)))return false;
		label->SetWidth(150.0f);
		label->SetHeight(50.0f);

		bindLabel = new KeyLabel(&m_usableKeys);
		m_keylabels.push_back(bindLabel);
		
		if (i == 4 || i == 5) bindLabel->SetKeylist(&m_selectOnlyKeys);

		if (!bindLabel->Init(rect, &theme->m_settingsLabel, &inputModels->at(8)->m_keybinds[i]))return false;
		bindLabel->SetWidth(150.0f);
		bindLabel->SetHeight(50.0f);

		m_row->push_back(label);
		m_row->push_back(bindLabel);


		if (i == characterActionCount - 1) cat->allRows.push_back(*m_row);
		else if (i % 2 != 0)
		{
			cat->allRows.push_back(*m_row);
			m_row = new vector < UIBase * > ;
		}
	}

	PositionContent(bounds);

	return true;
}

void KeybindContent::PositionContent(LMVector4 * bounds)
{
	PositionCategoryLayout(bounds);
}

void KeybindContent::Render()
{

	CategoryLayoutRender();
	
	/*
	for (unsigned int i = 0; i < m_checkboxes.size(); i++)
	{
		m_checkboxes.at(i)->Render();
	}
	*/
}

void KeybindContent::Select(POINT * p)
{
	/*
	for (unsigned int i = 0; i < m_checkboxes.size(); i++)
	{
		m_checkboxes.at(i)->Select(p);
	}*/

	for (unsigned int i = 0; i < m_keylabels.size(); i++)
	{
		//m_keylabels.at(i)->Select(p);

		if (m_keylabels.at(i)->IsPointInBounds(p))
		{
			
			ActivateKeyDialogViaCallback(m_keylabels.at(i));
			return;
		}
	}
}

void KeybindContent::AltSelect(POINT * p)
{

}

void KeybindContent::SetKeyDialogCallback(std::function<void(KeyLabel*)> f)
{
	m_keyDialogActivate = f;
}

void KeybindContent::ActivateKeyDialogViaCallback(KeyLabel * label)
{
	m_keyDialogActivate(label);
}