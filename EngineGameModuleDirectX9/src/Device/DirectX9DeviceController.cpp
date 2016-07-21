#include "DirectX9DeviceController.h"

DirectX9DeviceController::DirectX9DeviceController(){}
DirectX9DeviceController::~DirectX9DeviceController(){}


void DirectX9DeviceController::SetRenderSettings(CustomRenderSettings settings)
{
	


	switch (settings)
	{
	case customRenderSettingsUniversal:

		g_D3D_Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(0.8f, 0.8f, 0.8f, 1.0f));
		g_D3D_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
		g_D3D_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		//g_D3D_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		g_D3D_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_D3D_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		//game only stuff that doesnt affect interface render
		//so we put this stuff here so we only do it once
		//at start of the game.
		g_D3D_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_D3D_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_D3D_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		
		//g_D3D_Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		g_D3D_Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		g_D3D_Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
		g_D3D_Device->SetRenderState(D3DRS_DITHERENABLE, TRUE);

		break;
	case customRenderSettingsMenuUI:

		g_D3D_Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));
		g_D3D_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_D3D_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_D3D_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_D3D_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
		//g_D3D_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

		break;
	case customRenderSettingsGameUI:
		
		//g_D3D_Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));
		g_D3D_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_D3D_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_D3D_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_D3D_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
		//g_D3D_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);


		break;
	case customRenderSettingsGame3d:

		g_D3D_Device->SetRenderState(D3DRS_ZENABLE, TRUE);
		//g_D3D_Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(0.6f, 0.6f, 0.6f, 1.0f));
		g_D3D_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_D3D_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		// new settings

		break;
	default:break;
	}
	
	
}
