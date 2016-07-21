#include "Billboard.h"

LPDIRECT3DDEVICE9 Billboard::m_device = nullptr;

Billboard::Billboard()
{
	m_texture = nullptr;
	m_vertexBuffer = nullptr;
	m_vertices = nullptr;

	pos = m_physicsObject.GetPosition();
	rot = m_physicsObject.GetRotation();
	sca = m_physicsObject.GetScale();

	sca->x = 1.0f;
	sca->y = 1.0f;
	sca->z = 1.0f;
}

Billboard::~Billboard()
{
}

bool Billboard::Init(LPDIRECT3DDEVICE9 device, string path, BillboardAlignment alignment, float width, float height)
{


	if (m_device == nullptr) m_device = device;

	if (D3D_OK != D3DXCreateTextureFromFile(m_device, path.c_str(), &m_texture)) return false;

	Vertex vertexData[4];

	switch (alignment)
	{
	case billboardAlignBottomCentre:
		
		vertexData[0] = { -0.5f*width, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f };
		vertexData[1] = { -0.5f*width, 0.0f, height, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f };
		vertexData[2] = { 0.5f*width, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f };
		vertexData[3] = { 0.5f*width, 0.0f, height, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f };

		break;
	case billboardAlignMiddleCentre:

		vertexData[0] = { -0.5f*width, 0.0f, -0.5f*height, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f };
		vertexData[1] = { -0.5f*width, 0.0f, 0.5f*height, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f };
		vertexData[2] = { 0.5f*width, 0.0f, -0.5f*height, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f };
		vertexData[3] = { 0.5f*width, 0.0f, 0.5f*height, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f };

		break;
	}



	m_width = width;
	m_height = height;


	if (FAILED(m_device->CreateVertexBuffer(sizeof(vertexData), 0, D3DFVF_D3DVertex, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL)))
		return false;

	if (FAILED(m_vertexBuffer->Lock(0, sizeof(vertexData), (void**)&m_vertices, 0)))
		return false;

	memcpy(m_vertices, vertexData, sizeof(vertexData));

	m_vertexBuffer->Unlock();


	//material

	ZeroMemory(&m_material, sizeof(D3DMATERIAL9));

	m_material.Diffuse.r = 1.0f;
	m_material.Diffuse.g = 1.0f;
	m_material.Diffuse.b = 1.0f;
	m_material.Diffuse.a = 1.0f;
	m_material.Ambient.r = 1.0f;
	m_material.Ambient.g = 1.0f;
	m_material.Ambient.b = 1.0f;
	m_material.Ambient.a = 1.0f;
	m_material.Specular.r = 1.0f;
	m_material.Specular.g = 1.0f;
	m_material.Specular.b = 1.0f;
	m_material.Specular.a = 1.0f;
	m_material.Power = 8.0f;

	return true;
}

void Billboard::Update(float deltaTime)
{
}

void Billboard::Render()
{
	D3DXMatrixScaling(&m_scale, sca->x, sca->y, sca->z);
	D3DXMatrixRotationYawPitchRoll(&m_rotation, rot->x, rot->y, rot->z);
	D3DXMatrixTranslation(&m_translation, pos->x, pos->y, pos->z);

	m_world = m_scale * m_rotation * m_translation;

	m_device->SetTransform(D3DTS_WORLD, &m_world);
	m_device->SetMaterial(&m_material);
	m_device->SetTexture(0, m_texture);
	m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));
	m_device->SetFVF(D3DFVF_D3DVertex);
	m_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

PhysicsObject * Billboard::GetPhysicsObject() { return &m_physicsObject; }

void Billboard::SetRadius(float radius)
{
	sca->x = radius*2.0f;
	sca->z = radius*2.0f;
}