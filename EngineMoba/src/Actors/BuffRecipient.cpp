#include "BuffRecipient.h"

BuffRecipient::BuffRecipient()
{

}
BuffRecipient::~BuffRecipient()
{

}

Buff * BuffRecipient::CreateBuff(BuffType buffType, int buffName, float duration)
{
	Buff * buff = new Buff();

	if (buff->Init(buffName, duration))
	{
		switch (buffType)
		{
		case buffBuff: PushBuff(buff); break;
		case buffDebuff: PushDebuff(buff); break;
		}
	}
	else
	{
		delete buff;
		return nullptr;
	}

	return buff;
}

vector<Buff*> * BuffRecipient::GetBuffs()
{
	return &m_buffs;
}

vector<Buff*> * BuffRecipient::GetDebuffs()
{
	return &m_debuffs;
}

void BuffRecipient::PushBuff(Buff * buff) //todo move "move operation" stuff here potentially.
{
	for (unsigned int i = 0; i < m_buffs.size(); i++)
	{
		if (m_buffs.at(i) == NULL)
		{
			m_buffs.at(i) = buff; return;
		}
	}

	m_buffs.push_back(buff);
}

void BuffRecipient::PushDebuff(Buff * buff)
{
	//Duplicate

	for (unsigned int i = 0; i < m_debuffs.size(); i++)
	{
		if (m_debuffs.at(i) == NULL)
		{
			m_debuffs.at(i) = buff; return;
		}
	}

	m_debuffs.push_back(buff);
}