#if !defined(BUFFRECIPIENT_H)
#define BUFFRECIPIENT_H

#include <vector>
using namespace std;

#include "../VitalEffect/Buff.h"

enum BuffType
{
	buffBuff,
	buffDebuff,
	buffTypeCount
};

class BuffRecipient
{
private:


protected:
	vector<Buff*> m_buffs; //Buffs
	vector<Buff*> m_debuffs; //Debuffs
	
public:
	BuffRecipient();
	~BuffRecipient();

	Buff * CreateBuff(BuffType buffType, int buffName, float duration);

	vector<Buff*> * GetBuffs();
	vector<Buff*> * GetDebuffs();

private://unprivate this if you want ability to push their own buffs.
	void PushBuff(Buff * buff);
	void PushDebuff(Buff * buff);

};


#endif