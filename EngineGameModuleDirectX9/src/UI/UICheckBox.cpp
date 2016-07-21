#include "UICheckBox.h"

LPDIRECT3DTEXTURE9 UICheckBox::m_checked = NULL;
LPDIRECT3DTEXTURE9 UICheckBox::m_unchecked = NULL;

float UICheckBox::m_width;
float UICheckBox::m_height;

UICheckBox::UICheckBox() :UIElement()
{
	m_state = false;
}

UICheckBox::UICheckBox(bool checked, float width, float height) : UIElement()
{
	m_state = checked;

	m_width = width;
	m_height = height;
}
UICheckBox::~UICheckBox()
{

}

bool UICheckBox::Init()
{
	if (m_checked == NULL)
	{
		if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/UI/Menu/Shared/checked.png", &m_checked) != D3D_OK)
		{
			MessageBox(NULL, "UICheckbox::Init (Bad texture)", "Error", MB_OK);
			return false;
		}
	}

	if (m_unchecked == NULL)
	{
		if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/UI/Menu/Shared/unchecked.png", &m_unchecked) != D3D_OK)
		{
			MessageBox(NULL, "UICheckbox::Init (Bad texture)", "Error", MB_OK);
			return false;
		}
	}

	if (m_state) SetChecked();
	else SetUnchecked();

	InitMaterial();

	return InitVertexData(m_width, m_height);
}

void UICheckBox::Render()
{
	//OutputDebugString("UICheckBox::Render");
	UIElement::Render();
}

bool UICheckBox::Cycle()
{
	switch (m_state)
	{
	case true:
		UxTexture = m_unchecked;

		//g_Present_Parameters.MultiSampleQuality = 0;
		break;
	case false:
		UxTexture = m_checked;

		//g_Present_Parameters.MultiSampleQuality = 4;
		
		break;
	}
	
	return m_state = !m_state;
}

bool UICheckBox::GetIsChecked()
{
	return m_state;
}

void UICheckBox::SetChecked()
{
	m_state = true;
	UxTexture = m_checked;

}

void UICheckBox::SetUnchecked()
{
	m_state = true;
	UxTexture = m_unchecked;
}


float UICheckBox::GetWidth()
{
	return m_width;
}
float UICheckBox::GetHeight()
{
	return m_height;
}

void UICheckBox::Select(POINT * p)
{
	if (IsPointInBounds(p)) Cycle();
}

void UICheckBox::AltSelect(POINT * p)
{
	if (IsPointInBounds(p)) Cycle();
}