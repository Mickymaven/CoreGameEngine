#include "HealthBar.h"

HealthBar::HealthBar()
{

}

HealthBar::HealthBar(
	LPDIRECT3DTEXTURE9 friendlyFrameTexture,
	LPDIRECT3DTEXTURE9 friendlyHealthTexture,
	LPDIRECT3DTEXTURE9 opponentFrameTexture,
	LPDIRECT3DTEXTURE9 opponentHealthTexture,
	bool * isHealthMirrorOn,
	LPD3DXFONT font,
	D3DCOLOR * fontColor
	)
{
	m_owner = NULL;
	
	m_font = font;
	m_fontColor = fontColor;
	

	m_tempIsFriendly = true;
	//LMVector3 m_position;
	m_healthMirrorOnPointer = isHealthMirrorOn;

	m_frameFriendly = UIElement(100.0f, 50.0f, friendlyFrameTexture);
	m_frameOpponent = UIElement(100.0f, 50.0f, opponentFrameTexture);

	PhysicsObject physicsObject =
		PhysicsObject(
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(1.0f, 1.0f, 1.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f);

	m_healthFriendly = UIResizableElement(0.9707f * 100.0f, 50.0f, physicsObject, friendlyHealthTexture);
	m_healthOpponent = UIResizableElement(0.9707f * 100.0f, 50.0f, PhysicsObject(physicsObject), opponentHealthTexture);

}

HealthBar::~HealthBar()
{

}

bool HealthBar::Init(VitalEntity * owner)
{

	m_visibility = true;

	m_owner = owner;

	m_position = LMVector2(0.0f, 0.0f);

	m_frameFriendly.InitMaterial();
	if (!m_frameFriendly.InitVertexData()) return false;

	m_healthFriendly.InitMaterial();
	if (!m_healthFriendly.InitVertexData()) return false;


	m_frameOpponent.InitMaterial();
	if (!m_frameOpponent.InitVertexData()) return false;

	m_healthOpponent.InitMaterial();
	if (!m_healthOpponent.InitVertexData()) return false;

	m_frameFriendly.GetPosition()->y = 0;
	m_healthFriendly.GetPosition()->y = 0;

	m_frameOpponent.GetPosition()->y = 0;
	m_healthOpponent.GetPosition()->y = 0;




	// FONT STUFF //////////////////////////////////////////

	deviceContext = CreateCompatibleDC(NULL);
	my3dfont = CreateFont(
		20,//Height
		0, //Width
		0, //Escapement
		0, //Orientation
		FW_NORMAL, //Weight
		false, //Italic
		false, //Underline
		false,//Strikeout
		DEFAULT_CHARSET, //Charset
		OUT_DEFAULT_PRECIS,//Output Precision
		CLIP_DEFAULT_PRECIS,//Clipping Precision
		DEFAULT_QUALITY, //Quality
		DEFAULT_PITCH | FF_DONTCARE,
		"Nanum Brush Script");
	SelectObject(deviceContext, my3dfont);

	//	string name = (m_owner)->GetUniqueName().c_str();

	//char * nameChars = new char[name.length() + 1];

	//strcpy(nameChars, name.c_str());

	m_nameText = NULL;

	ZeroMemory(&m_nameMaterial, sizeof(D3DMATERIAL9));
	
	m_nameMaterial.Diffuse.r = 0.5f;
	m_nameMaterial.Diffuse.g = 0.5f;
	m_nameMaterial.Diffuse.b = 0.5f;
	m_nameMaterial.Ambient.r = 0.5f;
	m_nameMaterial.Ambient.g = 0.5f;
	m_nameMaterial.Ambient.b = 0.5f;
	m_nameMaterial.Specular.r = 0.4f;
	m_nameMaterial.Specular.g = 0.4f;
	m_nameMaterial.Specular.b = 0.4f;
	m_nameMaterial.Power = 7.0f;

	/*m_nameMaterial.Diffuse.r = 1.0f;
	m_nameMaterial.Diffuse.g = 1.0f;
	m_nameMaterial.Diffuse.b = 1.0f;
	m_nameMaterial.Diffuse.a = 1.0f;
	m_nameMaterial.Ambient.r = 1.0f;
	m_nameMaterial.Ambient.g = 1.0f;
	m_nameMaterial.Ambient.b = 1.0f;
	m_nameMaterial.Ambient.a = 1.0f;
	m_nameMaterial.Specular.r = 1.0f;
	m_nameMaterial.Specular.g = 1.0f;
	m_nameMaterial.Specular.b = 1.0f;
	m_nameMaterial.Specular.a = 1.0f;
	m_nameMaterial.Power = 8.0f;
	*/
	/////////////////////////////////////////////////////////


	//update stuf
	myVector = D3DXVECTOR2(0.0f, 0.0f);
	crunchpc = 10.0f; //reset each update
	pcDownScreen = 0.60f; //reset each update

	scalex = 0.5f; //reset each update

	return true;
}

bool HealthBar::Init3DNamesForActors(Actor * owner)
{

	if (FAILED(D3DXCreateTextA(
	g_D3D_Device, //device
	deviceContext, //Device Context
	owner->GetUniqueName().c_str(), //text
	0.001f, //Maximum chordal deviation fromtrue font outlines
	0.1f, //Extrusion depth (along -z axis)
	&m_nameText, //Mesh
	NULL, //Adjacency Information
	NULL //Glyph Metrics
	))) return false;

	return true;
}

void HealthBar::Update(float deltaTime, LMCamera * camera, float healthPercent, bool isFriendly, int ci)
{
	m_tempIsFriendly = isFriendly;
	
	//position with our new function in GraphicsAlgorithms.h
	ConvertRayToScreenCoords(camera, m_owner->GetPhysicsObject()->GetPosition(), &m_position, ci);
	



	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	myVector.x = 0.0f, myVector.y = 0.0f; //reset each update

	myVector.x = m_owner->GetPhysicsObject()->GetPosition()->x - camera->GetPosition()->x;
	myVector.y = m_owner->GetPhysicsObject()->GetPosition()->z - camera->GetPosition()->z;

	D3DXVec2Normalize(&myVector, &myVector);

	direction1 = atan2(myVector.y, myVector.x);

	myVector.x = camera->GetLookAt()->x - camera->GetPosition()->x;
	myVector.y = camera->GetLookAt()->z - camera->GetPosition()->z;

	D3DXVec2Normalize(&myVector, &myVector);

	direction2 = atan2(myVector.y, myVector.x);

	direction1 += D3DX_PI;
	direction2 += D3DX_PI;

	if (direction2 - direction1 > D3DX_PI) direction1 += D3DX_PI*2.0f;

	if (direction2 - direction1 < -D3DX_PI) direction1 -= D3DX_PI*2.0f;

	if ((direction2 - direction1) < (0.5f*D3DX_PI))
	{
		if ((direction2 - direction1)  > (-0.5f*D3DX_PI))
		{
			m_visibility = true;
		}
		else
		{
			m_visibility = false;
			//OutputDebugString("Conditions met to cancel render \n");
		}
	}
	else
	{
		m_visibility = false;
		//OutputDebugString("Conditions met to cancel render \n");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// the position has to account for ui elements position origin
	m_position.x -= 50.0f;
	m_position.y -= 90.0f;

	healthbar = NULL;
	switch (m_tempIsFriendly)
	{
	case true:
		healthbar = &m_healthFriendly;
		m_frameFriendly.GetPosition()->x = m_position.x;
		m_frameFriendly.GetPosition()->z = m_position.y;
		m_healthFriendly.GetPosition()->x = m_position.x;
		m_healthFriendly.GetPosition()->z = m_position.y;

		break;
	case false:
		healthbar = &m_healthOpponent;
		m_frameOpponent.GetPosition()->x = m_position.x;
		m_frameOpponent.GetPosition()->z = m_position.y;
		m_healthOpponent.GetPosition()->x = m_position.x;
		m_healthOpponent.GetPosition()->z = m_position.y;

		break;
	}

	//float healthPercent = 0.1f;

	subValue = ((1.0f - healthPercent)) * (0.9707f * -1);

	healthbar->GetPhysicsObject()->GetScale()->x = healthPercent;
	healthbar->GetPhysicsObject()->GetPosition()->x = m_position.x + subValue + ((healthbar->GetWidth() * (1.0f - 0.9707f)) / 2.0f);
	healthbar->GetPhysicsObject()->GetPosition()->z = m_position.y;
	
	
	if (*m_healthMirrorOnPointer)
	{
		if (!m_visibility)
		{
			healthbar->GetPhysicsObject()->GetPosition()->x -= g_clientSizeRect->right * 0.5f;
			healthbar->GetPhysicsObject()->GetPosition()->x *= scalex;
			healthbar->GetPhysicsObject()->GetPosition()->x += g_clientSizeRect->right * 0.5f;

			healthbar->GetPhysicsObject()->GetPosition()->z = healthbar->GetPhysicsObject()->GetPosition()->z /= crunchpc;
			healthbar->GetPhysicsObject()->GetPosition()->z = healthbar->GetPhysicsObject()->GetPosition()->z += pcDownScreen * g_clientSizeRect->bottom;

			FrameForTeam = NULL;

			if (m_tempIsFriendly) FrameForTeam = &m_frameFriendly;
			else if (!m_tempIsFriendly) FrameForTeam = &m_frameOpponent;

			FrameForTeam->GetPosition()->z = healthbar->GetPhysicsObject()->GetPosition()->z /= crunchpc;
			FrameForTeam->GetPosition()->z = healthbar->GetPhysicsObject()->GetPosition()->z += pcDownScreen * g_clientSizeRect->bottom;

			FrameForTeam->GetPosition()->x = FrameForTeam->GetPosition()->x -= g_clientSizeRect->right * 0.5f;
			FrameForTeam->GetPosition()->x = FrameForTeam->GetPosition()->x *= scalex;
			FrameForTeam->GetPosition()->x = FrameForTeam->GetPosition()->x += g_clientSizeRect->right * 0.5f;

		}
	}
}

void HealthBar::Render()
{

	if (*m_healthMirrorOnPointer){}
	else if (!m_visibility) return;

	switch (m_tempIsFriendly)
	{
	case true:
		 m_frameFriendly.Render();
		 m_healthFriendly.Render();

		break;
	case false:
		 m_frameOpponent.Render();
		 m_healthOpponent.Render();

		break;
	}
}

void HealthBar::RenderName(bool is3d)
{
	if (*m_healthMirrorOnPointer){}
	else if (!m_visibility) return;


	if (!is3d)
	{
		//D3D9 DrawText

		m_fontPosition = {
			(int)(m_position.x),
			(int)(m_position.y) + 5,
			(int)(m_position.x) + 150,
			(int)(m_position.y) + 40 };

		m_font->DrawText(
			NULL,
			((Actor*)m_owner)->GetUniqueName().c_str(),
			-1,
			&m_fontPosition,
			DT_LEFT,
			*m_fontColor);

		m_fontPosition = {
			(int)(m_position.x) + 5,
			(int)(m_position.y) + 28,
			(int)(m_position.x) + 150,
			(int)(m_position.y) + 43 };

		sprintf_s(buffer, "%.0f", ceil(((Actor*)m_owner)->GetStats()->GetHealth()));

		m_font->DrawText(
			NULL,
			buffer,
			-1,
			&m_fontPosition,
			DT_LEFT,
			*m_fontColor);

	}
	else
	{
		/*
		//proj
		D3DXMATRIX m_orthographicmatrix;
		D3DXMatrixOrthoLH(&m_orthographicmatrix, (float)g_clientSizeRect->right, (float)g_clientSizeRect->bottom, 0.0f, 1.1f);
		g_D3D_Device->SetTransform(D3DTS_PROJECTION, &m_orthographicmatrix);


		//view
		D3DXMATRIX m_view2dmatrix;
		D3DXVECTOR3 oposition = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, -1.0f, 0.5f * (float)g_clientSizeRect->bottom - 0.0001f);
		D3DXVECTOR3 olookat = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, 0.0f, 0.5f * (float)g_clientSizeRect->bottom);
		D3DXVECTOR3 oup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		D3DXMatrixLookAtLH(&m_view2dmatrix, &oposition, &olookat, &oup);
		
		*/
		


		if (m_nameText != NULL)
		{
			//name rendering

			D3DXMatrixTranslation(&localtrans, -0.9f, 0.0f, -0.2f);
			D3DXMatrixTranslation(
				&m_translation,
				m_owner->GetPhysicsObject()->GetPosition()->x,
				2.2f,
				m_owner->GetPhysicsObject()->GetPosition()->z);
			D3DXMatrixRotationYawPitchRoll(&m_rotation, 0.0f, 0.6f, 0.0f);
			D3DXMatrixScaling(&m_scale, 1.0f,1.0f,1.0f);

			m_world = m_scale * localtrans * m_rotation * m_translation;

			g_D3D_Device->SetTransform(D3DTS_WORLD, &m_world);
			g_D3D_Device->SetTexture(0, NULL);
			g_D3D_Device->SetMaterial(&m_nameMaterial);
			m_nameText->DrawSubset(0);
			
		}

	}
}


void HealthBar::RenderName3d()
{
	if (m_nameText != NULL)
	{

		/*
		//proj
		D3DXMATRIX m_orthographicmatrix;
		D3DXMatrixOrthoLH(&m_orthographicmatrix, (float)g_clientSizeRect->right, (float)g_clientSizeRect->bottom, 0.0f, 1.1f);
		g_D3D_Device->SetTransform(D3DTS_PROJECTION, &m_orthographicmatrix);



		//view
		D3DXMATRIX m_view2dmatrix;



		D3DXVECTOR3 oposition = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, -1.0f, 0.5f * (float)g_clientSizeRect->bottom - 0.0001f);
		D3DXVECTOR3 olookat = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, 0.0f, 0.5f * (float)g_clientSizeRect->bottom);
		D3DXVECTOR3 oup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		D3DXMatrixLookAtLH(&m_view2dmatrix, &oposition, &olookat, &oup);

		g_D3D_Device->SetTransform(D3DTS_VIEW, &m_view2dmatrix);
*/



		D3DXMatrixScaling(&m_scale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationYawPitchRoll(&m_rotation, 0.0f, 0.0f, 0.0f);

		D3DXMatrixTranslation(&m_translation, 50.0f, 0.0f, 50.0f);
		//else D3DXMatrixTranslation(&m_translation, 0.0f, 0.0f, 0.0f);

		m_world = m_scale * m_rotation * m_translation;



		g_D3D_Device->SetTransform(D3DTS_WORLD, &m_world);

		g_D3D_Device->SetMaterial(&m_nameMaterial);
		g_D3D_Device->SetTexture(0, NULL);
		m_nameText->DrawSubset(0);
	}
}