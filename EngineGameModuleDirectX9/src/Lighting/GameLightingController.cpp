#include "GameLightingController.h"

GameLightingController::GameLightingController()
{
	
}

GameLightingController::~GameLightingController()
{


}

bool GameLightingController::Init()
{
	m_state = gameLightsOn;

	m_yellow.Type = D3DLIGHT_DIRECTIONAL;
	m_yellow.Direction = D3DXVECTOR3(10.0f, -5.0f, 0.0f);
	m_yellow.Ambient.r = 0.2f;
	m_yellow.Ambient.g = 0.2f;
	m_yellow.Ambient.b = 0.1f;
	m_yellow.Ambient.a = 1.0f;
	m_yellow.Diffuse.r = 0.7f;
	m_yellow.Diffuse.g = 0.7f;
	m_yellow.Diffuse.b = 0.1f;
	m_yellow.Diffuse.a = 1.0f;
	m_yellow.Specular.r = 1.0f;
	m_yellow.Specular.g = 1.0f;
	m_yellow.Specular.b = 1.0f;
	m_yellow.Specular.a = 1.0f;

	g_D3D_Device->SetLight(0, &m_yellow);
	//g_D3D_Device->LightEnable(0, TRUE);

	//second directional
	m_cyan.Type = D3DLIGHT_DIRECTIONAL;
	m_cyan.Direction = D3DXVECTOR3(-0.0f, -5.0f, -10.0f);
	m_cyan.Ambient.r = 0.1f;
	m_cyan.Ambient.g = 0.2f;
	m_cyan.Ambient.b = 0.2f;
	m_cyan.Ambient.a = 1.0f;
	m_cyan.Diffuse.r = 0.1f;
	m_cyan.Diffuse.g = 0.7f;
	m_cyan.Diffuse.b = 0.7f;
	m_cyan.Diffuse.a = 1.0f;
	m_cyan.Specular.r = 1.0f;
	m_cyan.Specular.g = 1.0f;
	m_cyan.Specular.b = 1.0f;
	m_cyan.Specular.a = 1.0f;

	g_D3D_Device->SetLight(1, &m_cyan);
	//g_D3D_Device->LightEnable(1, TRUE);

	//third directional
	m_magenta.Type = D3DLIGHT_DIRECTIONAL;
	m_magenta.Direction = D3DXVECTOR3(-10.0f, -5.0f, 10.0f);
	m_magenta.Ambient.r = 0.2f;
	m_magenta.Ambient.g = 0.1f;
	m_magenta.Ambient.b = 0.2f;
	m_magenta.Ambient.a = 1.0f;
	m_magenta.Diffuse.r = 0.7f;
	m_magenta.Diffuse.g = 0.1f;
	m_magenta.Diffuse.b = 0.7f;
	m_magenta.Diffuse.a = 1.0f;
	m_magenta.Specular.r = 1.0f;
	m_magenta.Specular.g = 1.0f;
	m_magenta.Specular.b = 1.0f;
	m_magenta.Specular.a = 1.0f;

	g_D3D_Device->SetLight(2, &m_magenta);
	//g_D3D_Device->LightEnable(2, TRUE);

	//white directional
	m_white.Type = D3DLIGHT_DIRECTIONAL;
	m_white.Direction = D3DXVECTOR3(10.0f, -5.0f, -10.0f);
	m_white.Ambient.r = 0.2f;
	m_white.Ambient.g = 0.2f;
	m_white.Ambient.b = 0.2f;
	m_white.Ambient.a = 1.0f;
	m_white.Diffuse.r = 0.7f;
	m_white.Diffuse.g = 0.7f;
	m_white.Diffuse.b = 0.7f;
	m_white.Diffuse.a = 1.0f;
	m_white.Specular.r = 1.0f;
	m_white.Specular.g = 1.0f;
	m_white.Specular.b = 1.0f;
	m_white.Specular.a = 1.0f;

	g_D3D_Device->SetLight(3, &m_white);
	g_D3D_Device->LightEnable(3, TRUE);


	/*
	//weak white directional
	m_white2.Type = D3DLIGHT_DIRECTIONAL;
	m_white2.Direction = D3DXVECTOR3(-10.0f, -5.0f, 10.0f);
	m_white2.Ambient.r = 0.3f;
	m_white2.Ambient.g = 0.3f;
	m_white2.Ambient.b = 0.2f;
	m_white2.Ambient.a = 1.0f;
	m_white2.Diffuse.r = 0.3f;
	m_white2.Diffuse.g = 0.3f;
	m_white2.Diffuse.b = 0.2f;
	m_white2.Diffuse.a = 1.0f;
	m_white2.Specular.r = 1.0f;
	m_white2.Specular.g = 1.0f;
	m_white2.Specular.b = 1.0f;
	m_white2.Specular.a = 1.0f;

	g_D3D_Device->SetLight(4, &m_white2);
	g_D3D_Device->LightEnable(4, TRUE);
	*/

	//purple directional
	m_purple.Type = D3DLIGHT_DIRECTIONAL;
	m_purple.Direction = D3DXVECTOR3(-10.0f, -5.0f, 10.0f); 
	m_purple.Ambient.r = 0.15f;
	m_purple.Ambient.g = 0.1f;
	m_purple.Ambient.b = 0.25f;
	m_purple.Ambient.a = 1.0f;
	m_purple.Diffuse.r = 0.45f;
	m_purple.Diffuse.g = 0.1f;
	m_purple.Diffuse.b = 0.7f;
	m_purple.Diffuse.a = 1.0f;
	m_purple.Specular.r = 1.0f;
	m_purple.Specular.g = 1.0f;
	m_purple.Specular.b = 1.0f;
	m_purple.Specular.a = 1.0f;

	g_D3D_Device->SetLight(4, &m_purple);
	g_D3D_Device->LightEnable(4, TRUE);

	purpleBaseLight.Type = D3DLIGHT_POINT;
	purpleBaseLight.Range = 40.0f;
	purpleBaseLight.Attenuation1 = 0.1f;
	purpleBaseLight.Attenuation0 = 0.0f;
	purpleBaseLight.Attenuation2 = 0.0f;
	purpleBaseLight.Position = D3DXVECTOR3(390.0f, 10.0f, 390.0f);
	purpleBaseLight.Ambient.r = 0.5f;
	purpleBaseLight.Ambient.g = 0.1f;
	purpleBaseLight.Ambient.b = 0.5f;
	purpleBaseLight.Ambient.a = 1.0f;
	purpleBaseLight.Diffuse.r = 0.3f;
	purpleBaseLight.Diffuse.g = 0.1f;
	purpleBaseLight.Diffuse.b = 0.3f;
	purpleBaseLight.Diffuse.a = 1.0f;
	purpleBaseLight.Specular.r = 0.3f;
	purpleBaseLight.Specular.g = 0.3f;
	purpleBaseLight.Specular.b = 0.3f;
	purpleBaseLight.Specular.a = 0.3f;

	g_D3D_Device->SetLight(5, &purpleBaseLight);
	g_D3D_Device->LightEnable(5, TRUE);



	


	
	yellowBaseLight.Type = D3DLIGHT_POINT;
	yellowBaseLight.Range = 40.0f;
	yellowBaseLight.Attenuation1 = 0.1f;
	yellowBaseLight.Attenuation0 = 0.0f;
	yellowBaseLight.Attenuation2 = 0.0f;
	yellowBaseLight.Position = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	yellowBaseLight.Ambient.r = 0.3f;
	yellowBaseLight.Ambient.g = 0.3f;
	yellowBaseLight.Ambient.b = 0.1f;
	yellowBaseLight.Ambient.a = 1.0f;
	yellowBaseLight.Diffuse.r = 0.3f;
	yellowBaseLight.Diffuse.g = 0.3f;
	yellowBaseLight.Diffuse.b = 0.1f;
	yellowBaseLight.Diffuse.a = 1.0f;
	yellowBaseLight.Specular.r = 0.3f;
	yellowBaseLight.Specular.g = 0.3f;
	yellowBaseLight.Specular.b = 0.3f;
	yellowBaseLight.Specular.a = 0.3f;

	g_D3D_Device->SetLight(6, &yellowBaseLight);
	g_D3D_Device->LightEnable(6, TRUE);

	


	//white directional
	m_BigWhite.Type = D3DLIGHT_DIRECTIONAL;
	m_BigWhite.Direction = D3DXVECTOR3(10.0f, -5.0f, -10.0f);
	m_BigWhite.Ambient.r = 0.01f;
	m_BigWhite.Ambient.g = 0.01f;
	m_BigWhite.Ambient.b = 0.01f;
	m_BigWhite.Ambient.a = 1.0f;
	m_BigWhite.Diffuse.r = 0.05f;
	m_BigWhite.Diffuse.g = 0.05f;
	m_BigWhite.Diffuse.b = 0.05f;
	m_BigWhite.Diffuse.a = 1.0f;
	m_BigWhite.Specular.r = 1.0f;
	m_BigWhite.Specular.g = 1.0f;
	m_BigWhite.Specular.b = 1.0f;
	m_BigWhite.Specular.a = 1.0f;

	g_D3D_Device->SetLight(gameLightBigWhite, &m_BigWhite);
	g_D3D_Device->LightEnable(gameLightBigWhite, FALSE);
	/*




	moonlight.Type = D3DLIGHT_POINT;
	moonlight.Range = 5000.0f;
	moonlight.Attenuation1 = 0.05f;
	moonlight.Attenuation0 = 0.0f;
	moonlight.Attenuation2 = 0.0f;
	moonlight.Position = D3DXVECTOR3(200.0f, 20.0f, 200.0f);
	moonlight.Ambient.r = 0.9f;
	moonlight.Ambient.g = 0.9f;
	moonlight.Ambient.b = 0.9f;
	moonlight.Ambient.a = 1.0f;
	moonlight.Diffuse.r = 0.9f;
	moonlight.Diffuse.g = 0.9f;
	moonlight.Diffuse.b = 0.9f;
	moonlight.Diffuse.a = 1.0f;
	moonlight.Specular.r = 1.0f;
	moonlight.Specular.g = 1.0f;
	moonlight.Specular.b = 1.0f;
	moonlight.Specular.a = 1.0f;

	//g_D3D_Device->SetLight(3, &moonlight);
	//g_D3D_Device->LightEnable(3, TRUE);

	*/

	return true;
}

void GameLightingController::GameLightsOff()
{
	if (! m_state == gameLightsOff)
	{
		m_state = gameLightsOff;
		//g_D3D_Device->LightEnable(0, TRUE);
		//g_D3D_Device->LightEnable(1, TRUE);
		//g_D3D_Device->LightEnable(2, TRUE);
		//g_D3D_Device->LightEnable(3, FALSE);
		g_D3D_Device->LightEnable(3, FALSE);
		g_D3D_Device->LightEnable(4, FALSE);
		g_D3D_Device->LightEnable(5, FALSE);
		g_D3D_Device->LightEnable(6, FALSE);

		g_D3D_Device->LightEnable(gameLightBigWhite, TRUE);
	}
}

void GameLightingController::GameLightsOn()
{
	if (!m_state == gameLightsOn)
	{
		m_state = gameLightsOn;

		//g_D3D_Device->LightEnable(0, TRUE);
		//g_D3D_Device->LightEnable(1, TRUE);
		//g_D3D_Device->LightEnable(2, TRUE);
		//g_D3D_Device->LightEnable(3, TRUE);
		g_D3D_Device->LightEnable(3, TRUE);
		g_D3D_Device->LightEnable(4, TRUE);
		g_D3D_Device->LightEnable(5, TRUE);
		g_D3D_Device->LightEnable(6, TRUE);

		g_D3D_Device->LightEnable(gameLightBigWhite, FALSE);
	}
}