#include "ChatMessage.h"

ChatMessage::ChatMessage()
{
	std::memset(&m_text, 0, m_messageMax);
}
