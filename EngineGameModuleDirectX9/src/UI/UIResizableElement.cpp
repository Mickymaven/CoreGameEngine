#include "UIResizableElement.h"

UIResizableElement::UIResizableElement()
{

}

UIResizableElement::UIResizableElement(
	float width, float height,
	PhysicsObject & physicsObject,
	LPDIRECT3DTEXTURE9 texture) : UIElement(width, height, texture)
{
	m_physicsObject = physicsObject;
}

UIResizableElement::~UIResizableElement()
{

}

void UIResizableElement::Render()
{
	//UIElement::UseViewAndProjection();

	D3DXMatrixScaling(
		&m_scale,
		m_physicsObject.GetScale()->x,
		m_physicsObject.GetScale()->y,
		m_physicsObject.GetScale()->z);

	D3DXMatrixRotationYawPitchRoll(
		&m_rotation,
		m_physicsObject.GetRotation()->x,
		m_physicsObject.GetRotation()->y,
		m_physicsObject.GetRotation()->z);

	D3DXMatrixTranslation(
		&m_translation,
		m_physicsObject.GetPosition()->x,
		m_physicsObject.GetPosition()->y,
		m_physicsObject.GetPosition()->z);

	m_world = m_scale * m_rotation * m_translation;

	g_D3D_Device->SetTransform(D3DTS_WORLD, &m_world);
	g_D3D_Device->SetMaterial(&DefaultMaterial);
	g_D3D_Device->SetTexture(0, UxTexture);
	g_D3D_Device->SetStreamSource(0, MyUX_Buffer, 0, sizeof(Vertex));
	g_D3D_Device->SetFVF(D3DFVF_D3DVertex);
	g_D3D_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

PhysicsObject * UIResizableElement::GetPhysicsObject()
{
	return &m_physicsObject;
}