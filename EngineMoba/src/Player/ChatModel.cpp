#include "ChatModel.h"

ChatModel::ChatModel()
{
	m_messageCount = 0;
	m_currentIndex = -1;
	m_messageLogSize = 100;
	m_messages.resize(m_messageLogSize);
}

ChatModel::~ChatModel()
{
}

vector<ChatMessage>* ChatModel::GetMessages() { return &m_messages; }

int ChatModel::IncrementMessageCount()
{ 
	if (m_currentIndex >= 99) m_currentIndex = 0;
	else m_currentIndex++;


	m_messageCount++;

	return m_currentIndex;
}

ChatMessage * ChatModel::GetNextFreeMessageAndIncrement()
{
	IncrementMessageCount();

	return &m_messages.at(m_currentIndex);

}

int ChatModel::GetMessageCount() { return m_messageCount; }

int ChatModel::GetCurrentIndex() { return m_currentIndex; }

int ChatModel::GetPreviousIndex(int i)
{
	if (i == 0) return 99;
	else if (i > 0) return i-1;

	return 0;
}
