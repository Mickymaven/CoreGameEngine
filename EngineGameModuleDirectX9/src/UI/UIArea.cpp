#include "UIArea.h"

UIArea::UIArea()
{
	m_positions = NULL;
	m_arraySize = 0;
}

UIArea::~UIArea()
{
	
}

bool UIArea::IsCursorPointInBounds()
{
	if (g_mouseClientPosition.x > m_bounds.left)
	{
		if (g_mouseClientPosition.x < m_bounds.right)
		{
			if (g_mouseClientPosition.y > m_bounds.top)
			{
				if (g_mouseClientPosition.y < m_bounds.bottom)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool UIArea::IsPointInBounds(POINT * p)
{
	if (p->x > m_bounds.left)
	{
		if (p->x < m_bounds.right)
		{
			if (p->y > m_bounds.top)
			{
				if (p->y < m_bounds.bottom)
				{
					//OutputDebugString("We go a hit in a UIArea\n");
					return true;
				}
			}
		}
	}

	return false;
}

void UIArea::Select(POINT * p)//is virtual;
{}

void UIArea::AltSelect(POINT * p)//is virtual;
{}
bool UIArea::MouseOver(POINT * p)//is virtual;
{ return false; }






void UIArea::SetBounds(long left, long top, long right, long bottom)
{
	m_bounds.left = left;
	m_bounds.top = top;
	m_bounds.right = right;
	m_bounds.bottom = bottom;

	//m_position.x = left;
	//m_position.z = top;
}





void UIArea::BehaviorOnFirstHit(float width, float height, vector<UICheckBox *> * vec, int enumIndex)
{

	OutputDebugString("HIT TEST CHECK BOXES\n\n");
	for (unsigned int index = 0; index < vec->size(); index++)
	{
		if (vec->at(index) != NULL)
		{
			if (Test(vec->at(index)->GetPosition()->x,
				vec->at(index)->GetPosition()->z,
				width, height, index, enumIndex))
			{
				break;
			}
		}
	}
}

bool UIArea::Test(float x, float y, float width, float height, unsigned int index, int enumIndex)
{
	if (g_mouseClientPosition.x > x)
	{
		if (g_mouseClientPosition.x < x + width)
		{
			if (g_mouseClientPosition.y > y)
			{
				if (g_mouseClientPosition.y < y + height)
				{
					ImplementBehavior(index, enumIndex);
					return true;
				}
			}
		}
	}
	return false;
	}

void UIArea::BehaviorOnFirstHit(float width, float height, vector<LMVector3 *> * vec, int enumIndex)
{
	for (unsigned int index = 0; index < vec->size(); index++)
	{
		if (vec->at(index) != NULL)
		{
			if (g_mouseClientPosition.x > vec->at(index)->x)
			{
				if (g_mouseClientPosition.x < vec->at(index)->x + width)
				{
					if (g_mouseClientPosition.y > vec->at(index)->z)
					{
						if (g_mouseClientPosition.y < vec->at(index)->z + height)
						{
							ImplementBehavior(index, enumIndex);
							break;
						}
					}
				}
			}
		}
	}
}

void UIArea::BehaviorOnFirstHit(vector<Buff*> * vec, int enumIndex)
{
	int m_xIndexCount = 0;

	LMVector2 m_origin = LMVector2(0.3f, 0.75f);
	m_origin.x *= g_clientSizeRect->right;
	m_origin.y *= g_clientSizeRect->bottom;

	if (enumIndex == 5) m_origin.y -= 50.0f;

	for (unsigned int index = 0;
		index < vec->size();
		index++)
	{
		if (vec->at(index) != NULL)
		{
			if (g_mouseClientPosition.x > m_origin.x + (m_xIndexCount * 44.0f))
			{
				if (g_mouseClientPosition.x < m_origin.x + (m_xIndexCount * 44.0f) + 44.0f)
				{
					if (g_mouseClientPosition.y > m_origin.y)
					{
						if (g_mouseClientPosition.y < m_origin.y + 44.0f)
						{
							ImplementBehavior(index, enumIndex);
							break;
						}
					}
				}
			}
			m_xIndexCount++;
		}
	}
}

void UIArea::BehaviorOnFirstHit(float width, float height, LMVector3 * posArray, int arraySize, int enumIndex)
{
	for (int index = 0; index < arraySize; index++) // 
	{
		if (g_mouseClientPosition.x > posArray[index].x)
		{
			if (g_mouseClientPosition.x < posArray[index].x + width)
			{
				if (g_mouseClientPosition.y > posArray[index].z)
				{
					if (g_mouseClientPosition.y < posArray[index].z + height)
					{
						ImplementBehavior(index, enumIndex);
						break;
					}
				}
			}
		}
		//end hit test
	}
}

void UIArea::BehaviorOnFirstHit(UIElement * posArray, int arraySize, int enumIndex)
{
	for (int index = 0; index < arraySize; index++) // 
	{
		/*
		char bufferx[100];
		sprintf_s(
		bufferx,
		"test %f, %f\n",
		posArray[index].GetPosition().x,
		posArray[index].GetPosition().z
		);
		OutputDebugString(bufferx);*/


		if (g_mouseClientPosition.x > posArray[index].GetPosition()->x)
		{
			if (g_mouseClientPosition.x < posArray[index].GetPosition()->x + 50.0f)
			{
				if (g_mouseClientPosition.y > posArray[index].GetPosition()->z)
				{
					if (g_mouseClientPosition.y < posArray[index].GetPosition()->z + 50)
					{
						ImplementBehavior(index, enumIndex);
						break;
					}
				}
			}
		}
		//end hit test
	}
}



void UIArea::ImplementBehavior(int index, int enumIndex)
{

}