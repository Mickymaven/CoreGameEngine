#include "UIStatLabelGroup.h"

UIStatLabelGroup::UIStatLabelGroup()
{
}

UIStatLabelGroup::~UIStatLabelGroup()
{
}

bool UIStatLabelGroup::Init(ViewProfile * viewProfile, ThemeResources * themeResources, MobaState * gameState, TooltipController * tooltipController, PlayerCharacterController * initCharControl)
{
	m_gameState = gameState;
	m_tooltipController = tooltipController;
	m_viewProfile = viewProfile;
	m_theme = themeResources;

	m_statLabels.resize(10);

	int elementIDs[] =
	{
		gameElementCharacterStatLabelRange,
		gameElementCharacterStatLabelAttackSpeed,
		gameElementCharacterStatLabelPhysical,
		gameElementCharacterStatLabelCatVoodoo,
		gameElementCharacterStatLabelMoveSpeed,
		gameElementCharacterStatLabelArmor,
		gameElementCharacterStatLabelCatVoodooResist,
		gameElementCharacterStatLabelHPRegen,
		gameElementCharacterStatLabelHealth,
		gameElementCharacterStatLabelMaxHealth

	};

	for (unsigned int i = 0; i < 10; i++)
	{
		if (!viewProfile->InitLabelCstr(elementIDs[i], &m_statLabels[i], &themeResources->m_mediumText)) return false;
	}

	return true;
}

void UIStatLabelGroup::Update(float deltaTime, ActorStats * a)
{
	m_statLabels[statLabelRange].SetText(a->m_range);
	m_statLabels[statLabelAS].SetText(a->m_attackSpeed);
	m_statLabels[statLabelAD].SetText(a->m_physicalDamage);
	m_statLabels[statLabelCV].SetText(a->m_catVoodoo);
	m_statLabels[statLabelMS].SetText(a->m_moveSpeed);
	m_statLabels[statLabelARM].SetText(a->m_armor);
	m_statLabels[statLabelCVR].SetText(a->m_catVoodooResist);
	m_statLabels[statLabelHPR].SetText(a->m_healthRegen);
	m_statLabels[statLabelHP].SetText(a->m_health);
	m_statLabels[statLabelMHP].SetText(a->m_maxHealth);

	//format string
	m_statLabels[statLabelRange].SetFloatFormat(5, 1);
	m_statLabels[statLabelAS].SetFloatFormat(5, 1);
	m_statLabels[statLabelAD].SetFloatFormat(5, 0);
	m_statLabels[statLabelCV].SetFloatFormat(5, 0);
	m_statLabels[statLabelMS].SetFloatFormat(5, 1);
	m_statLabels[statLabelARM].SetFloatFormat(5, 0);
	m_statLabels[statLabelCVR].SetFloatFormat(5, 0);
	m_statLabels[statLabelHPR].SetFloatFormat(5, 1);
	m_statLabels[statLabelHP].SetFloatFormat(5, 0);
	m_statLabels[statLabelMHP].SetFloatFormat(5, 0);

}

void UIStatLabelGroup::Render()
{
	for (size_t i = 0; i < m_statLabels.size(); i++)
	{
		m_statLabels[i].Render();
	}
}
