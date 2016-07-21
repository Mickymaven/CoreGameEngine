#include "HealthBarFrame.h"

HealthBarFrame::HealthBarFrame()
{
	m_HealthFrameTeam = NULL;
	m_HealthFrameOpponent = NULL;


	 m_Vertex_Buffer = NULL;

	 m_Vertices = NULL;

	 m_TextureHealthTeam = NULL;
	 m_TextureHealthOpponent = NULL;
	 m_Vertex_BufferHealth = NULL;

	 m_nameText = NULL;

	 m_owner = NULL;

	x = 0.0f, y = 0.0f, multFactor = 0.0f, m_interfaceScale = 1.0f;
}

HealthBarFrame::~HealthBarFrame()
{

}

bool HealthBarFrame::Init(Actor * owner)
{
	m_owner = owner;


	m_HealthFrameTeam = NULL;
	m_HealthFrameOpponent = NULL;


	if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/misc/health-bar-frame-friendly.png", &m_HealthFrameTeam))
		return false;

	if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/misc/health-bar-frame-opponent.png", &m_HealthFrameOpponent))
		return false;

	//if (D3DXCreateTextureFromFile(g_D3D_Device, "health-bar-frame.png", &m_Texture))
	//	return false;

	ZeroMemory(&m_Material, sizeof(D3DMATERIAL9));

	m_Material.Diffuse.r = 1.0f;
	m_Material.Diffuse.g = 1.0f;
	m_Material.Diffuse.b = 1.0f;
	m_Material.Diffuse.a = 1.0f;
	m_Material.Ambient.r = 1.0f;
	m_Material.Ambient.g = 1.0f;
	m_Material.Ambient.b = 1.0f;
	m_Material.Ambient.a = 1.0f;
	m_Material.Specular.r = 1.0f;
	m_Material.Specular.g = 1.0f;
	m_Material.Specular.b = 1.0f;
	m_Material.Specular.a = 1.0f;
	m_Material.Power = 8.0f;

	//Health Bar Frame
	x = 1.0f, y = 1.0f;

	Vertex vertexData[] =
	{
		{ -x, 0.0f, -0.5f*y, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f },
		{ -x, 0.0f, 0.5f*y, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f },
		{ x, 0.0f, -0.5f*y, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f },
		{ x, 0.0f, 0.5f*y, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f }
	};

	if (FAILED(g_D3D_Device->CreateVertexBuffer(sizeof(vertexData), 0, D3DFVF_D3DVertex, D3DPOOL_DEFAULT, &m_Vertex_Buffer, NULL)))
		return false;

	if (FAILED(m_Vertex_Buffer->Lock(0, sizeof(vertexData), (void**)&m_Vertices, 0)))
		return false;

	memcpy(m_Vertices, vertexData, sizeof(vertexData));

	m_Vertex_Buffer->Unlock();

	m_physicsObject = PhysicsObject(
		LMVector3(m_owner->GetPhysicsObject()->GetPosition()->x,3.5f, m_owner->GetPhysicsObject()->GetPosition()->z+0.2f),//Position
		LMVector3(0.0f, -0.77f, 0.0f),//Rotation
		LMVector3(1.0f, 1.0f, 1.0f),//Scale
		LMVector3(0.0f, 0.0f, 0.0f),//Velocity
		LMVector3(0.0f, 0.0f, 0.0f),//Spin
		LMVector3(0.0f, 0.0f, 0.0f),//Resize
		0.0f); //acceleration
	
	if (D3DXCreateTextureFromFile(g_D3D_Device, "health-bar-green.png", &m_TextureHealthTeam))
		return false;

	if (D3DXCreateTextureFromFile(g_D3D_Device, "health-bar-red.png", &m_TextureHealthOpponent))
		return false;
	//health representation

	multFactor = 0.9707f;
	//x *= 0.9707f, y *= 0.9707f;

	Vertex vertexDataHealth[] =
	{
		{ -x*multFactor, 0.0f, -0.5f*y, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f },
		{ -x*multFactor, 0.0f, 0.5f*y, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f },
		{ x*multFactor, 0.0f, -0.5f*y, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f },
		{ x*multFactor, 0.0f, 0.5f*y, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f }
	};

	if (FAILED(g_D3D_Device->CreateVertexBuffer(sizeof(vertexDataHealth), 0, D3DFVF_D3DVertex, D3DPOOL_DEFAULT, &m_Vertex_BufferHealth, NULL)))
		return false;
	
	if (FAILED(m_Vertex_BufferHealth->Lock(0, sizeof(vertexDataHealth), (void**)&m_VerticesHealth, 0)))
		return false;

	memcpy(m_VerticesHealth, vertexDataHealth, sizeof(vertexDataHealth));

	m_Vertex_BufferHealth->Unlock();

	m_physicsObjectHealth = PhysicsObject(
		LMVector3(m_owner->GetPhysicsObject()->GetPosition()->x, 3.5f, m_owner->GetPhysicsObject()->GetPosition()->z + 0.2f),//Position
		LMVector3(0.0f, -0.77f, 0.0f),//Rotation
		LMVector3(1.0f, 1.0f, 1.0f),//Scale
		LMVector3(0.0f, 0.0f, 0.0f),//Velocity
		LMVector3(0.0f, 0.0f, 0.0f),//Spin
		LMVector3(0.0f, 0.0f, 0.0f),//Resize
		0.0f); //acceleration

	deviceContext = CreateCompatibleDC(NULL);
	my3dfont = CreateFont(
		150,//Height
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

	string name = m_owner->GetUniqueName().c_str();

	char * nameChars = new char[name.length() + 1];

	strcpy(nameChars, name.c_str());

	if (FAILED(D3DXCreateTextA(
		g_D3D_Device, //device
		deviceContext, //Device Context
		nameChars,//text
		0.001f,//Maximum chordal deviation fromtrue font outlines
		0.1f,//Extrusion depth (along -z axis)
		&m_nameText,//Mesh
		NULL, //Adjacency Information
		NULL //Glyph Metrics
		))) return false;

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
	
	return true;
}

void HealthBarFrame::Update(float deltaTime, float healthPercent)
{
	m_physicsObject.GetPosition()->x = m_owner->GetPhysicsObject()->GetPosition()->x;
	//y = 2.9f
	m_physicsObject.GetPosition()->z = m_owner->GetPhysicsObject()->GetPosition()->z;

	//float healthPercent = 0.1f;

	float subValue = ((1.0f - healthPercent)) * (0.9707f * -x);

	m_physicsObjectHealth.GetScale()->x = healthPercent;

	m_physicsObjectHealth.GetPosition()->x = m_owner->GetPhysicsObject()->GetPosition()->x + subValue;
	//y = 2.9f
	m_physicsObjectHealth.GetPosition()->z = m_owner->GetPhysicsObject()->GetPosition()->z;

}

void HealthBarFrame::Render(bool isFriendly)
{

	//frame
	D3DXMatrixScaling(&m_scale, m_interfaceScale*m_physicsObject.GetScale()->x, m_interfaceScale*m_physicsObject.GetScale()->y, m_interfaceScale*m_physicsObject.GetScale()->z);
	D3DXMatrixRotationYawPitchRoll(&m_rotation, m_physicsObject.GetRotation()->x, m_physicsObject.GetRotation()->y, m_physicsObject.GetRotation()->z);
	D3DXMatrixTranslation(&m_translation, m_physicsObject.GetPosition()->x, m_physicsObject.GetPosition()->y + m_interfaceScale, m_physicsObject.GetPosition()->z);

	m_world = m_scale * m_rotation * m_translation;

	g_D3D_Device->SetTransform(D3DTS_WORLD, &m_world);
	g_D3D_Device->SetMaterial(&m_Material);

	if (isFriendly) g_D3D_Device->SetTexture(0, m_HealthFrameTeam);
	else g_D3D_Device->SetTexture(0, m_HealthFrameOpponent);

	g_D3D_Device->SetStreamSource(0, m_Vertex_Buffer, 0, sizeof(Vertex));
	g_D3D_Device->SetFVF(D3DFVF_D3DVertex);
	g_D3D_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	//bar
	D3DXMatrixScaling(&m_scale, m_interfaceScale*m_physicsObjectHealth.GetScale()->x, m_interfaceScale*m_physicsObjectHealth.GetScale()->y, m_interfaceScale*m_physicsObjectHealth.GetScale()->z);
	D3DXMatrixRotationYawPitchRoll(&m_rotation, m_physicsObjectHealth.GetRotation()->x, m_physicsObjectHealth.GetRotation()->y, m_physicsObjectHealth.GetRotation()->z);
	D3DXMatrixTranslation(&m_translation, m_physicsObjectHealth.GetPosition()->x, m_physicsObjectHealth.GetPosition()->y + m_interfaceScale, m_physicsObjectHealth.GetPosition()->z);

	m_world = m_scale * m_rotation * m_translation;

	g_D3D_Device->SetTransform(D3DTS_WORLD, &m_world);
	g_D3D_Device->SetMaterial(&m_Material);


	if (isFriendly) g_D3D_Device->SetTexture(0, m_TextureHealthTeam);
	else g_D3D_Device->SetTexture(0, m_TextureHealthOpponent);

	g_D3D_Device->SetStreamSource(0, m_Vertex_BufferHealth, 0, sizeof(Vertex));
	g_D3D_Device->SetFVF(D3DFVF_D3DVertex);
	g_D3D_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	


	//this class whould be more like a view set
	//where we would iterate again for this name stuff
	/*
	g_deviceControl.SetRenderSettings(customRenderSettingsGame3d);

	//name rendering
	D3DXMATRIX localtrans;
	D3DXMatrixTranslation(&localtrans, m_interfaceScale * -0.9f, 0.0f, -0.2f);
	D3DXMatrixTranslation(&m_translation, m_physicsObject.GetPosition()->x, m_physicsObject.GetPosition()->y + m_interfaceScale, m_physicsObject.GetPosition()->z);
	D3DXMatrixRotationYawPitchRoll(&m_rotation, 0.0f,0.6f,0.0f);
	D3DXMatrixScaling(&m_scale, m_interfaceScale*0.7f, m_interfaceScale*0.7f, m_interfaceScale*0.7f);

	m_world = m_scale * localtrans * m_rotation * m_translation;

	g_D3D_Device->SetTransform(D3DTS_WORLD, &m_world);
	g_D3D_Device->SetTexture(0, NULL);
	g_D3D_Device->SetMaterial(&m_nameMaterial);
	m_nameText->DrawSubset(0);
	*/
}