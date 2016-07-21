#if !defined(CHATMODEL_H)
#define CHATMODEL_H

#include <vector>
using std::vector;

#include "ChatMessage.h"

class ChatModel
{
	int m_messageLogSize;

	vector<ChatMessage> m_messages;
	int m_currentIndex;
	int m_messageCount;

public:
	ChatModel();
	~ChatModel();

	vector<ChatMessage> * GetMessages();

	int IncrementMessageCount();

	ChatMessage * GetNextFreeMessageAndIncrement();

	int GetMessageCount();

	int GetCurrentIndex();

	int GetPreviousIndex(int i);


};

#endif