#include "UILayoutStats.h"

UILayoutStats::UILayoutStats()
{
	
}

UILayoutStats::~UILayoutStats()
{

}

bool UILayoutStats::Init()
{

	m_pVector.resize(m_stats.size());

	for (unsigned int i = 0; i < m_stats.size(); i++)
	{
		m_pVector.at(i) = &m_stats.at(i);
	}

	return true;
}


void UILayoutStats::SetStatLabels(ActorStats * actorStats)
{
	vector<UILabel> m_stats;

}

void UILayoutStats::Update(float deltaTime)
{

}


void UILayoutStats::Render()
{
	for (unsigned int i = 0; i < m_stats.size(); i++)
	{
		m_stats.at(i).Render();
	}
}

