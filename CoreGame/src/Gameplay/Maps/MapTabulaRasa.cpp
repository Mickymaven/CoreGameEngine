#include "MapTabulaRasa.h"

MapTabulaRasa::MapTabulaRasa()
{
	m_teamLimit = 2;
	m_teamSpawns.resize(m_teamLimit);

	m_ground = Sprite(
		LMVector3(0.0f, 0.0f, 0.0f),		//Position
		LMVector3(0.0f, 0.0f, 0.0f),		//Rotation
		LMVector3(1.0f, 1.0f, 1.0f),		//Scale
		LMVector3(0.0f, 0.0f, 0.0f),		//Velocity
		LMVector3(0.0f, 0.0f, 0.0f),		//Spin
		LMVector3(0.0f, 0.0f, 0.0f),		//Resize
		0.0f);  //acceleration

	SpawnGen(0, 190.0f, 190.0f, 2.0f, 5);
	SpawnGen(1, 210.0f, 210.0f, 2.0f, 5);
}

MapTabulaRasa::~MapTabulaRasa()
{
}