#include "UIContentArea.h"

UIContentArea::UIContentArea()
{}

UIContentArea::UIContentArea(const UIContentArea & c)
{}

UIContentArea::~UIContentArea()
{}

bool UIContentArea::Init()//is virtual
{
	return true;
}

void UIContentArea::Render()//is virtual
{}

void UIContentArea::Select(POINT * p)//is virtual;
{}

void UIContentArea::AltSelect(POINT * p)//is virtual;
{}

bool UIContentArea::MouseOver(POINT * p)//is virtual;
{
	return false;
}

void UIContentArea::PositionCategoryLayout(LMVector4 * bounds)
{

	float rowTop = 0.0f;
	float elementLeft = 0.0f;
	LMVector3 * pos = NULL;
	RECT * eleBounds = NULL;
	float eleWidth = 0.0f;
	float eleHeight = 0.0f;

	for (unsigned int i = 0; i < m_categories.size(); i++)
	{
		m_categories.at(i).bounds.left() = bounds->left() + 25.0f;
		m_categories.at(i).bounds.top() = bounds->top() + 10.0f;

		if (i > 0) {
			m_categories.at(i).bounds.top() +=
				m_categories.at(i - 1).bounds.bottom() - m_categories.at(i - 1).bounds.top();
		}

		rowTop = m_categories.at(i).bounds.top();

		for (unsigned int rowI = 0; rowI < m_categories.at(i).allRows.size(); rowI++)
		{
			elementLeft = bounds->left();
			pos = NULL;

			for (unsigned int elementI = 0; elementI < m_categories.at(i).allRows.at(rowI).size(); elementI++)
			{
				eleWidth = m_categories.at(i).allRows.at(rowI).at(elementI)->GetWidth();
				eleHeight = m_categories.at(i).allRows.at(rowI).at(elementI)->GetHeight();
				pos = m_categories.at(i).allRows.at(rowI).at(elementI)->GetPosition();

				pos->x = elementLeft;
				pos->z = rowTop;

				eleBounds = m_categories.at(i).allRows.at(rowI).at(elementI)->GetBounds();

				eleBounds->left = elementLeft;
				eleBounds->top = rowTop;
				eleBounds->bottom = rowTop + eleHeight;
				eleBounds->right = elementLeft + eleWidth;

				elementLeft += 10.0f + eleWidth;
			}

			rowTop += 45.0f;
		}
	}
}

void UIContentArea::CategoryLayoutRender()
{
	for (unsigned int i = 0; i < m_categories.size(); i++)
	{
		for (unsigned int rowI = 0; rowI < m_categories.at(i).allRows.size(); rowI++)
		{
			for (unsigned int elementI = 0; elementI < m_categories.at(i).allRows.at(rowI).size(); elementI++)
			{
				m_categories.at(i).allRows.at(rowI).at(elementI)->Render();
			}
		}
	}
}