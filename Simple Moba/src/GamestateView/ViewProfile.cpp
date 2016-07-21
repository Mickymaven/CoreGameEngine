#include "ViewProfile.h"

bool ViewProfile::InitElement(int elementID, UIElement * uiElement)
{
	return InitElementWithPath(elementID, uiElement, m_themeResourceProfile->GetPath(elementID));
}


bool ViewProfile::InitElementWithPath(int elementID, UIElement * uiElement, string path)
{
	if (!uiElement->Init(
		m_aspectProfile->GetWidthForElement(elementID),
		m_aspectProfile->GetHeightForElement(elementID),
		path
		)) return false;

	uiElement->SetBounds(
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID),
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID),
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID) + m_aspectProfile->GetWidthForElement(elementID),
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID) + m_aspectProfile->GetHeightForElement(elementID)
		);

	return true;
}


bool ViewProfile::InitLabel(int elementID, UILabel * label, FontGroup * fontGroup, string * string)
{
	
	RECT r = {
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID),
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID),
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID) + m_aspectProfile->GetWidthForElement(elementID),
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID) + m_aspectProfile->GetHeightForElement(elementID) };

	if (!label->Init(r, fontGroup, string)) return false;
	
	return true;
}

bool ViewProfile::InitLabelCstr(int elementID, UILabelCstr * label, FontGroup * fontGroup)
{

	RECT r = {
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID),
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID),
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID) + m_aspectProfile->GetWidthForElement(elementID),
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID) + m_aspectProfile->GetHeightForElement(elementID) };

	if (!label->Init(r, fontGroup)) return false;

	return true;
}

bool ViewProfile::InitKeybindLbl(int elementID, UILabelCstr * label, FontGroup * fontGroup)
{
	float keyWidth = 20;
	float keyHeight = 13;

	return InitRelativeLabel(elementID, label, fontGroup, keyWidth, keyHeight, 1.0, 1.0);
	

	return true;
}

bool ViewProfile::InitRelativeLabel(int elementID, UILabelCstr * label, FontGroup * fontGroup, float w, float h, float top, float left)
{
	RECT r = {
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID) + top*m_aspectProfile->GetWidthForElement(elementID) - 0.5f*w,
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID) + left*m_aspectProfile->GetHeightForElement(elementID) - 0.5f*h,
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID) + top*m_aspectProfile->GetWidthForElement(elementID) + 0.5f*w,
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID) + left*m_aspectProfile->GetHeightForElement(elementID) + 0.5f*h };

	if (!label->Init(r, fontGroup)) return false;

	return true;
}

bool ViewProfile::InitLayoutAvatar(int elementID, UILayoutAvatar * uiLayout, UIElement * uiElement)
{
	InitUIBase(elementID, uiLayout);
	
	uiElement->SetHeight(uiLayout->GetHeight());
	uiElement->SetHeight(uiLayout->GetWidth());

	return true;
}

bool ViewProfile::InitUIBase(int elementID, UIBase * uibase)
{
	uibase->SetBounds(
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID),
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID),
		m_aspectProfile->GetAlignX(elementID) + m_aspectProfile->GetXForElement(elementID) + m_aspectProfile->GetWidthForElement(elementID),
		m_aspectProfile->GetAlignY(elementID) + m_aspectProfile->GetYForElement(elementID) + m_aspectProfile->GetHeightForElement(elementID));

	//set bounds sets position for us

	uibase->SetWidth(m_aspectProfile->GetWidthForElement(elementID));
	uibase->SetHeight(m_aspectProfile->GetHeightForElement(elementID));
	
	return false;
}


