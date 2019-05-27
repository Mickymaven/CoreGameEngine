#include "GlobalsDX9.h"


LPDIRECT3D9 g_D3D_Object = NULL; //direct x object
LPDIRECT3DDEVICE9 g_D3D_Device = NULL;//direct x device

D3DDISPLAYMODE g_DisplayMode;//allows us to set screens display mode
D3DPRESENT_PARAMETERS g_Present_Parameters; //parameters of screen
D3DCAPS9 g_D3DCaps;//hardware capabilities

