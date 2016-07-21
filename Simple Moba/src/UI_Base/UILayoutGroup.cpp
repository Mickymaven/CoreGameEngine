#include "UILayoutGroup.h"

UILayoutGroup::UILayoutGroup()
{

}

UILayoutGroup::~UILayoutGroup()
{

}

void UILayoutGroup::PositionItems(
	LMVector4 * bounds,
	float width, float height,
	float xSpace, float ySpace)
{
	float rowTop = 0.0f;
	float elementLeft = 0.0f;

	LMVector3 * pos = NULL;
	RECT * eleBounds = NULL;
	float eleWidth = 0.0f;
	float eleHeight = 0.0f;
	

	rowTop = bounds->top();
	elementLeft = bounds->left();

	for (unsigned int i = 0; i < m_pVector.size(); i++)
	{
		m_pVector.at(i)->SetWidth(width);
		m_pVector.at(i)->SetHeight(height);

		eleWidth = m_pVector.at(i)->GetWidth();
		eleHeight = m_pVector.at(i)->GetHeight();
		pos = m_pVector.at(i)->GetPosition();
		eleBounds = m_pVector.at(i)->GetBounds();

		pos->x = elementLeft;
		pos->z = rowTop;

		eleBounds->left = elementLeft;
		eleBounds->top = rowTop;
		eleBounds->bottom = rowTop + eleHeight;
		eleBounds->right = elementLeft + eleWidth;

		elementLeft += xSpace;
		rowTop += ySpace;
	}

}