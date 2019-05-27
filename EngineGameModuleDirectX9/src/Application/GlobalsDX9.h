#if !defined(GLOBALSDX9_H)
#define GLOBALSDX9_H

//the purpose of this class is to expose client and direct x variables to controllers in the client in an easy way.

//todo move main out probs
//mainly direct x

#include<d3d9.h>
#include<d3dx9.h>


extern LPDIRECT3D9 g_D3D_Object; //direct x object
extern LPDIRECT3DDEVICE9 g_D3D_Device;//direct x device
extern D3DDISPLAYMODE g_DisplayMode;//allows us to set screens display mode
extern D3DPRESENT_PARAMETERS g_Present_Parameters; //parameters of screen
extern D3DCAPS9 g_D3DCaps;//hardware capabilities
#endif
