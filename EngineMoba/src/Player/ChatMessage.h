#if !defined (CHATMESSAGE_H)
#define CHATMESSAGE_H

#include <cstring>


enum ChatMessageTarget
{
	targetTeam,
	targetPlayer,
	targetGlobal
};

struct ChatMessage
{
	static const int m_messageMax = 64;

	char m_text[m_messageMax];

	unsigned long m_playerID; //player who wrote msg
	int m_teamID; // team of player who wrote msg
	ChatMessageTarget m_messageTarget;
	int m_playerReciepientID;
	
	ChatMessage();
};

#endif