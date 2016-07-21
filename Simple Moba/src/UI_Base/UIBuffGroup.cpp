#include "UIBuffGroup.h"

UIBuffGroup::UIBuffGroup()
{

}

UIBuffGroup::~UIBuffGroup()
{

}

bool UIBuffGroup::Init(vector<BuffView> * buffView)
{
	m_buffViews = buffView;

	m_pVector.resize(m_buffs.size());

	for (unsigned int i = 0; i < m_buffs.size(); i++)
	{
		m_pVector.at(i) = &m_buffs.at(i);
	}

	return true;
}

void UIBuffGroup::SetBuffs(vector<Buff *> * buffs)
{
	//wont clear buffs bc next character with no buffs will have buff size zero


	for (unsigned int i = 0; i < buffs->size(); i++)
	{
		//if (i == m_buffs.size()) return;

		if (buffs->at(i) != NULL)
		{
			m_buffs.at(i).SetBuff(buffs->at(i));
			
			m_buffs.at(i).SetBuffView( &m_buffViews->at( buffs->at(i)->GetBuffClass() ) );
			m_buffs.at(i).SetIcon(m_buffs.at(i).GetBuffView()->GetIcon());
		}
		else
		{
			m_buffs.at(i).SetBuff(NULL);
			m_buffs.at(i).SetBuffView(NULL);
			m_buffs.at(i).SetIcon(NULL);
		}
	}

	//clear the rest of buffs beyond buffs size.
	for (unsigned int j = buffs->size(); j < m_buffs.size(); j++)
	{
		m_buffs.at(j).SetBuff(NULL);
		m_buffs.at(j).SetBuffView(NULL);
		m_buffs.at(j).SetIcon(NULL);
	}

}

void UIBuffGroup::Update(float deltaTime)
{

}

void UIBuffGroup::Render()
{
	for (unsigned int i = 0; i < m_buffs.size(); i++)
	{
		if (m_buffs.at(i).GetBuff() != NULL) m_buffs.at(i).Render();
	}
}

void UIBuffGroup::Select(POINT * p)
{

}

void UIBuffGroup::AltSelect(POINT * p)
{

}

bool UIBuffGroup::MouseOver(POINT * p)
{
	for (unsigned int i = 0; i < m_buffs.size(); i++)
	{
		if (m_buffs.at(i).GetBuff() != NULL)
			if (m_buffs.at(i).MouseOver(p)) return true;
	}
	return false;
}