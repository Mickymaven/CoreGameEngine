#include "TooltipController.h"

TooltipController::TooltipController()
{
	m_timeout = LMTimer();
	m_state = tooltipStateInactive;
	m_abilityOwnsTooltip = NULL;
	m_activeTooltip = NULL;
}


TooltipController::~TooltipController()
{

}

bool TooltipController::Init()
{
	return true;
}

void TooltipController::Update(float deltaTime)
{
	
	m_timeout.Update(deltaTime);
	
	//1.  when whe have no active tooltips (timerfinished:
	//    we will look for a new mouse over to show ////


	

}

void TooltipController::Render()
{
	if (m_timeout.GetState() != timerFinished)//active tool tip
	{
		if (m_activeTooltip != NULL) m_activeTooltip->Render();

		//render background element at tooltip pos for selected element
			// calc text position from tooltip origin
			//ddraw text
		
	}
}

void TooltipController::ActivateTooltipItem(RECT * bounds, TooltipInfoItem * tooltipInfoItem, Ability * ability)
{
	m_activeTooltip = tooltipInfoItem;
	m_abilityOwnsTooltip = ability;
	
	if (m_activeTooltip != NULL)
	{
		if (bounds->left > 814.0f) m_activeTooltip->GetBackground()->GetPosition()->x = bounds->left - m_activeTooltip->GetBackground()->GetWidth();
		else m_activeTooltip->GetBackground()->GetPosition()->x = bounds->left;

		if (bounds->top > 600.f) m_activeTooltip->GetBackground()->GetPosition()->z = bounds->top - m_activeTooltip->GetBackground()->GetHeight();
		else m_activeTooltip->GetBackground()->GetPosition()->z = bounds->bottom;

		ActiveTooltipSetup(bounds);
	}
}

void TooltipController::ActivateTooltipAbility(RECT * bounds, TooltipInfo * tooltipInfo, Ability * ability)
{
	m_activeTooltip = tooltipInfo;
	m_abilityOwnsTooltip = ability;

	DEBUG_IF(tooltipInfo == NULL || m_abilityOwnsTooltip ==NULL)
	{
		MessageBox(NULL, "TooltipController::ActivateTooltipAbility  a param  was null,TooltipInfo", "Error", MB_OK);
		OutputDebugString("TooltipController::ActivateTooltipAbility  a param was null,TooltipInfo");
		return;
	}

	

	if (m_activeTooltip != NULL)
	{
		m_activeTooltip->GetBackground()->GetPosition()->x = bounds->left;
		m_activeTooltip->GetBackground()->GetPosition()->z = bounds->top - 267.0f;

		ActiveTooltipSetup(bounds);
	}
}

void TooltipController::ActivateTooltipBuff(RECT * bounds, TooltipInfo * tooltipInfo)
{
	DEBUG_IF (tooltipInfo == NULL)
	{
		MessageBox(NULL, "TooltipController::ActivateTooltipBuff  tooltipInfo  was null,TooltipInfo","Error",MB_OK);
		OutputDebugString("TooltipController::ActivateTooltipBuff  tooltipInfo  was null,TooltipInfo");
		return;
	}

	m_activeTooltip = tooltipInfo;

	if (m_activeTooltip != NULL)
	{
		m_activeTooltip->GetBackground()->GetPosition()->x = bounds->left;
		m_activeTooltip->GetBackground()->GetPosition()->z = bounds->top - 267.0f;

		ActiveTooltipSetup(bounds);
	}
}

void TooltipController::ActiveTooltipSetup(RECT * bounds)
{
	m_timeout.RestartWithDuration(0.1f, true);
}

Ability * TooltipController::GetAbilityOwner()
{
	return m_abilityOwnsTooltip;
}

LMTimer * TooltipController::GetTimer()
{
	return &m_timeout;
}
