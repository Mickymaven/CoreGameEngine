#include "UIGameMap.h"

UIGameMap::UIGameMap()
{

}

UIGameMap::~UIGameMap()
{

}

bool UIGameMap::Init()
{

	return true;
}

LMVector3 * UIGameMap::GetMapOrigin()
{
	return &m_mapOrigin;
}

LMVector3 * UIGameMap::GetMapSize()
{
	return &m_mapSize;
}