#include "UIInvPanel.h"

const int UIInvPanel::elementIDs[] =
{
	gameElementInv0,
	gameElementInv1,
	gameElementInv2,
	gameElementInv3,
	gameElementInv4,
	gameElementInv5,
	gameElementInv6,
	gameElementInv7,
	gameElementInv8,
	gameElementInv9
};

UIInvPanel::UIInvPanel()
{
	m_isDragging = false;
}

UIInvPanel::~UIInvPanel()
{
}

bool UIInvPanel::Init(
	ViewProfile * viewProfile,
	ThemeResources * themeResources,
	MobaState * gameState,
	TooltipController * tooltipController,
	vector<InputModel*>* inputModels,
	vector<ItemView> * itemViews,
	PlayerCharacterController * initCharControl)
{

	m_gameState = gameState;
	m_tooltipController = tooltipController;
	m_viewProfile = viewProfile;
	m_theme = themeResources;


	m_playerInventory.SetItemViews(itemViews);
	m_playerInventory.m_items.resize(initCharControl->GetCharacter()->GetInventory()->size());

 	for (unsigned int i = 0; i < m_playerInventory.m_items.size(); i++)
		m_playerInventory.m_items.at(i).SetMouseOverCallback(
			std::bind(&TooltipController::ActivateTooltipItem, m_tooltipController, _1, _2, _3));
	InitInvPositions(viewProfile);

	m_bindLabels.resize(10);

	int elementText[] =//CharacterAction
	{
		characterActionInventory1,
		characterActionInventory2,
		characterActionInventory3,
		characterActionInventory4,
		characterActionInventory5,
		characterActionInventory6,
		characterActionInventory7,
		characterActionInventory8,
		characterActionInventory9,
		characterActionInventory0
	};


	for (unsigned int i = 0; i < 10; i++) //10 counted from elements, could resize bind labels
	{
		if (!viewProfile->InitRelativeLabel(elementIDs[i], &m_bindLabels[i], &themeResources->m_smallText, 20.0f, 14.0f, 0.7f, 0.7f)) return false;
		m_bindLabels[i].SetText(
			GetInputDefineString(
				inputModels->at(7)->m_keybinds[elementText[i]]
				).c_str()

			);
	}

	return true;
}


void UIInvPanel::InitInvPositions(ViewProfile * viewProfile)
{
	RECT * eleBounds = nullptr;
	LMVector3 * pos = nullptr;
	int elementID = 0;


	for (unsigned int i = 0; i < m_playerInventory.m_items.size(); i++)
	{
		elementID = elementIDs[i];

		eleBounds = m_playerInventory.m_items.at(i).GetBounds();
		pos = m_playerInventory.m_items.at(i).GetPosition();

		eleBounds->left = viewProfile->m_aspectProfile->GetAlignX(elementID) + viewProfile->m_aspectProfile->GetXForElement(elementID);
		eleBounds->top = viewProfile->m_aspectProfile->GetAlignY(elementID) + viewProfile->m_aspectProfile->GetYForElement(elementID);
		eleBounds->right = viewProfile->m_aspectProfile->GetAlignX(elementID) + viewProfile->m_aspectProfile->GetXForElement(elementID) + viewProfile->m_aspectProfile->GetWidthForElement(elementID);
		eleBounds->bottom = viewProfile->m_aspectProfile->GetAlignY(elementID) + viewProfile->m_aspectProfile->GetYForElement(elementID) + viewProfile->m_aspectProfile->GetHeightForElement(elementID);

		pos->x = eleBounds->left;
		pos->z = eleBounds->top;

		m_playerInventory.m_items.at(i).SetWidth(viewProfile->m_aspectProfile->GetWidthForElement(elementID));
		m_playerInventory.m_items.at(i).SetHeight(viewProfile->m_aspectProfile->GetHeightForElement(elementID));
	}
}

void UIInvPanel::Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView)
{
	//set inv items every update.
	m_playerInventory.SetItems(playerCharacterController->GetCharacter()->GetInventory());

	m_playerCharacter = playerCharacterController;
}

void UIInvPanel::Render()
{
	//m_playerInventory.m_items.at(index).GetIcon()->SetPosition(&m_inventoryPositons[index]);

	for (unsigned int i = 0; i < m_playerInventory.m_items.size(); i++)
	{

		//only when dragging
		if (m_isDragging == true && i == m_dragIndex)
		{
			if (m_playerInventory.m_items.at(i).GetIcon() != NULL)
			{
				m_playerInventory.m_items.at(i).GetIcon()->Render(
					(float)g_mouseClientPosition.x - 20.0f,
					m_playerInventory.m_items.at(i).GetPosition()->y,
					(float)(g_mouseClientPosition.y) - 20.0f);
			}
		}

		//normal render
		else if (m_playerInventory.m_items.at(i).GetIcon() != NULL)
		{
			m_playerInventory.m_items.at(i).GetIcon()->Render(
				m_playerInventory.m_items.at(i).GetPosition()->x,
				m_playerInventory.m_items.at(i).GetPosition()->y,
				m_playerInventory.m_items.at(i).GetPosition()->z);
		}
	}
	for (unsigned int i = 0; i < m_bindLabels.size(); i++)
	{
		m_bindLabels[i].Render();
	}

}

void UIInvPanel::Select(POINT * p)
{
	if (m_isDragging == false)
	{
		for (unsigned int i = 0; i < m_playerInventory.m_items.size(); i++)
		{
			if (m_playerInventory.m_items.at(i).IsPointInBounds(p))
			{
				m_dragIndex = i;

				m_dragTimer.RestartWithDuration(0.5f, true);
				m_isDragging = true;
			}
		}
	}
}

void UIInvPanel::SelectMouseUp(POINT * p)
{
	if (m_isDragging == true)
	{
		for (unsigned int i = 0; i < m_playerInventory.m_items.size(); i++)
		{
			if (m_playerInventory.m_items.at(i).IsPointInBounds(p))
			{
				//we can swap
				if (m_playerCharacter->GetCharacter()->GetInventory()->at(i) == NULL)
				{
					//swap method a
					m_playerCharacter->GetCharacter()->GetInventory()->at(i) = m_playerCharacter->GetCharacter()->GetInventory()->at(m_dragIndex);
					m_playerCharacter->GetCharacter()->GetInventory()->at(m_dragIndex) = NULL;
				}
				else
				{
					//swap method b
					Item * tempItemPointer = NULL;
					tempItemPointer = m_playerCharacter->GetCharacter()->GetInventory()->at(i);
					m_playerCharacter->GetCharacter()->GetInventory()->at(i) = m_playerCharacter->GetCharacter()->GetInventory()->at(m_dragIndex);
					m_playerCharacter->GetCharacter()->GetInventory()->at(m_dragIndex) = tempItemPointer;

				}
				m_isDragging = false;
			}
		}

		m_isDragging = false;
		m_dragTimer.Stop();
	}
}

void UIInvPanel::AltSelect(POINT * p)
{
}

bool UIInvPanel::MouseOver(POINT * p)
{
	for (unsigned int i = 0; i < m_playerInventory.m_items.size(); i++)
	{
		if (m_playerInventory.m_items.at(i).MouseOver(p)) return true;
	}

	return false;
}

UILayoutInventory * UIInvPanel::GetLayoutInventory()
{
	return &m_playerInventory;
}

bool UIInvPanel::GetIsDraggingItem()
{
	return m_isDragging;
}
