#include "UIElement.h"

UIElement::UIElement()
{
	UxTexture = NULL;
	MyUX_Buffer = NULL;

	m_position = LMVector3(0.0f, 0.0f, 0.0f);
}

UIElement::~UIElement()
{
}

UIElement::UIElement(float width, float height, string path)
{
	UxTexture = NULL;
	MyUX_Buffer = NULL;

	m_position = LMVector3(0.0f, 0.0f, 0.0f);

	m_texturePath = path;
	m_width = width;
	m_height = height;
}

UIElement::UIElement(float width, float height)//new constructor for derived class GameCursor
{
	UxTexture = NULL;
	MyUX_Buffer = NULL;

	m_position = LMVector3(0.0f, 0.0f, 0.0f);

	m_width = width;
	m_height = height;
}

UIElement::UIElement(float width, float height, LPDIRECT3DTEXTURE9 texture)
{
	UxTexture = texture;
	MyUX_Buffer = NULL;

	m_position = LMVector3(0.0f, 0.0f, 0.0f);

	m_texturePath = "";
	m_width = width;
	m_height = height;

	InitMaterial();
}

bool UIElement::Init(float width, float height, string path)
{
	UxTexture = NULL;
	MyUX_Buffer = NULL;

	m_position = LMVector3(0.0f, 0.0f, 0.0f);

	m_texturePath = path;
	m_width = width;
	m_height = height;

	return Init();

	return true;
}

bool UIElement::Init()
{
	if (D3DXCreateTextureFromFile(g_D3D_Device, m_texturePath.c_str(), &UxTexture) != D3D_OK)
	{
		//MessageBox(NULL, "Bad texture; ", "Error", MB_OK);	return false;
		OutputDebugString("Bad texture UIElement.cpp");
	}

	InitMaterial();
	//float xval = (float)g_clientSizeRect->right / 120.0f;
	//float yval = (float)g_clientSizeRect->bottom / 120.0f;

	return InitVertexData();

	return true;
}


void UIElement::InitMaterial()
{
	ZeroMemory(&DefaultMaterial, sizeof(D3DMATERIAL9));
	DefaultMaterial.Diffuse.r = DefaultMaterial.Ambient.r = 1.0f;
	DefaultMaterial.Diffuse.g = DefaultMaterial.Ambient.g = 1.0f;
	DefaultMaterial.Diffuse.b = DefaultMaterial.Ambient.b = 1.0f;
	DefaultMaterial.Specular.r = 1.0f;
	DefaultMaterial.Specular.g = 1.0f;
	DefaultMaterial.Specular.b = 1.0f;
	DefaultMaterial.Power = 8.0f;
}

bool UIElement::InitVertexData()
{
	return InitVertexData(m_width, m_height);
}

bool UIElement::InitVertexData(float m_width, float m_height)
{
	Vertex MyUX_Data[] =
	{
		{ 0.0f, 0.0f, m_height, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f },
		{ m_width, 0.0f, m_height, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f },
		{ m_width, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f }
	};

	// Create the vertex buffer that will hold the triangle.
	if (FAILED(g_D3D_Device->CreateVertexBuffer(sizeof(MyUX_Data),
		0, D3DFVF_D3DVertex, D3DPOOL_DEFAULT, &MyUX_Buffer, NULL)))
	{
		MessageBox(NULL, "Bad  createvertex buffer ", "Error", MB_OK);	return false;

	}

	// Lock the buffer we can write to it.
	if (FAILED(MyUX_Buffer->Lock(0, sizeof(MyUX_Data), (void**)&MyUXVertices, 0)))
	{
		MessageBox(NULL, "Bad lock buffer ", "Error", MB_OK);	return false;

	}

	// Here we copy the triangle's data into the vertex buffer.
	memcpy(MyUXVertices, MyUX_Data, sizeof(MyUX_Data));

	// Unlock when your done coping data into the buffer.
	MyUX_Buffer->Unlock();

	return true;
}

void UIElement::Update(float feltaTime)
{

}

void UIElement::Render()
{

	Render(m_position.x, m_position.y, m_position.z);
}


void UIElement::Render(float position_x, float position_y, float position_z)
{
	//UseViewAndProjection();

	D3DXMatrixScaling(&m_scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationYawPitchRoll(&m_rotation, 0.0f, 0.0f, 0.0f);

	D3DXMatrixTranslation(&m_translation, position_x, position_y, position_z);
	//else D3DXMatrixTranslation(&m_translation, 0.0f, 0.0f, 0.0f);

	m_world = m_scale * m_rotation * m_translation;

	g_D3D_Device->SetTransform(D3DTS_WORLD, &m_world);
	g_D3D_Device->SetMaterial(&DefaultMaterial);
	g_D3D_Device->SetTexture(0, UxTexture);
	g_D3D_Device->SetStreamSource(0, MyUX_Buffer, 0, sizeof(Vertex));
	g_D3D_Device->SetFVF(D3DFVF_D3DVertex);
	g_D3D_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
/*
void UIElement::UseViewAndProjection()
{

	GetClientRect(g_hwnd, g_clientSizeRect);
	//proj
	D3DXMATRIX m_orthographicmatrix;
	D3DXMatrixOrthoLH(&m_orthographicmatrix, (float)g_clientSizeRect->right, (float)g_clientSizeRect->bottom, 0.0f, 1.1f);
	g_D3D_Device->SetTransform(D3DTS_PROJECTION, &m_orthographicmatrix);


	//view
	D3DXMATRIX m_view2dmatrix;
	
	//D3DXVECTOR3 oposition = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, 1.0f, 0.5f * (float)g_clientSizeRect->bottom - 0.0001f);
	//D3DXVECTOR3 olookat = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, 0.0f, 0.5f * (float)g_clientSizeRect->bottom);
	//D3DXVECTOR3 oup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


	



	D3DXVECTOR3 oposition = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, -1.0f, 0.5f * (float)g_clientSizeRect->bottom - 0.0001f);
	D3DXVECTOR3 olookat = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, 0.0f, 0.5f * (float)g_clientSizeRect->bottom);
	D3DXVECTOR3 oup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&m_view2dmatrix, &oposition, &olookat, &oup);

	g_D3D_Device->SetTransform(D3DTS_VIEW, &m_view2dmatrix);


	//rs



	g_D3D_Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	g_D3D_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_D3D_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_D3D_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//temp disable depth bbuffer
	g_D3D_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
	//works to show interface
	g_D3D_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);


}*/