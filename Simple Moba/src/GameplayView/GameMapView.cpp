#include "GameMapView.h"

GameMapView::GameMapView()
{

}

GameMapView::~GameMapView()
{
	
}

void GameMapView::Render()
{
	m_groundView.Render();

}

SpriteView * GameMapView::GetGroundView() { return &m_groundView; }