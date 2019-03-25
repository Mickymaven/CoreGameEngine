#include "InputKeyDefines.h"


string g_keysEN[242];

string GetInputDefineString(int keybind)
{
	switch (keybind)
	{
	case 0x01: return "ESCAPE      "; break; //DIK_ESCAPE                                                             
	case 0x02: return "1           "; break; //DIK_1                                                                  
	case 0x03: return "2           "; break; //DIK_2                                                                  
	case 0x04: return "3           "; break; //DIK_3                                                                  
	case 0x05: return "4           "; break; //DIK_4                                                                  
	case 0x06: return "5           "; break; //DIK_5                                                                  
	case 0x07: return "6           "; break; //DIK_6                                                                  
	case 0x08: return "7           "; break; //DIK_7                                                                  
	case 0x09: return "8           "; break; //DIK_8                                                                  
	case 0x0A: return "9           "; break; //DIK_9                                                                  
	case 0x0B: return "0           "; break; //DIK_0                                                                  
	case 0x0C: return "MINUS       "; break; //DIK_MINUS                                                              
	case 0x0D: return "EQUALS      "; break; //DIK_EQUALS                                                             
	case 0x0E: return "BACK        "; break; //DIK_BACK                                                               
	case 0x0F: return "TAB         "; break; //DIK_TAB                                                                
	case 0x10: return "Q           "; break; //DIK_Q                                                                  
	case 0x11: return "W           "; break; //DIK_W                                                                  
	case 0x12: return "E           "; break; //DIK_E                                                                  
	case 0x13: return "R           "; break; //DIK_R                                                                  
	case 0x14: return "T           "; break; //DIK_T                                                                  
	case 0x15: return "Y           "; break; //DIK_Y                                                                  
	case 0x16: return "U           "; break; //DIK_U                                                                  
	case 0x17: return "I           "; break; //DIK_I                                                                  
	case 0x18: return "O           "; break; //DIK_O                                                                  
	case 0x19: return "P           "; break; //DIK_P                                                                  
	case 0x1A: return "LBRACKET    "; break; //DIK_LBRACKET                                                           
	case 0x1B: return "RBRACKET    "; break; //DIK_RBRACKET                                                           
	case 0x1C: return "RETURN      "; break; //DIK_RETURN                                                             
	case 0x1D: return "LCONTROL    "; break; //DIK_LCONTROL                                                           
	case 0x1E: return "A           "; break; //DIK_A                                                                  
	case 0x1F: return "S           "; break; //DIK_S                                                                  
	case 0x20: return "D           "; break; //DIK_D                                                                  
	case 0x21: return "F           "; break; //DIK_F                                                                  
	case 0x22: return "G           "; break; //DIK_G                                                                  
	case 0x23: return "H           "; break; //DIK_H                                                                  
	case 0x24: return "J           "; break; //DIK_J                                                                  
	case 0x25: return "K           "; break; //DIK_K                                                                  
	case 0x26: return "L           "; break; //DIK_L                                                                  
	case 0x27: return "SEMICOLON   "; break; //DIK_SEMICOLON                                                          
	case 0x28: return "APOSTROPHE  "; break; //DIK_APOSTROPHE                                                         
	case 0x29: return "GRAVE       "; break; //DIK_GRAVE                                                              
	case 0x2A: return "LSHIFT      "; break; //DIK_LSHIFT                                                             
	case 0x2B: return "BACKSLASH   "; break; //DIK_BACKSLASH                                                          
	case 0x2C: return "Z           "; break; //DIK_Z                                                                  
	case 0x2D: return "X           "; break; //DIK_X                                                                  
	case 0x2E: return "C           "; break; //DIK_C                                                                  
	case 0x2F: return "V           "; break; //DIK_V                                                                  
	case 0x30: return "B           "; break; //DIK_B                                                                  
	case 0x31: return "N           "; break; //DIK_N                                                                  
	case 0x32: return "M           "; break; //DIK_M                                                                  
	case 0x33: return "COMMA       "; break; //DIK_COMMA                                                              
	case 0x34: return "PERIOD      "; break; //DIK_PERIOD                                                             
	case 0x35: return "SLASH       "; break; //DIK_SLASH                                                              
	case 0x36: return "RSHIFT      "; break; //DIK_RSHIFT                                                             
	case 0x37: return "MULTIPLY    "; break; //DIK_MULTIPLY                                                           
	case 0x38: return "LMENU       "; break; //DIK_LMENU                                                              
	case 0x39: return "SPACE       "; break; //DIK_SPACE                                                              
	case 0x3A: return "CAPITAL     "; break; //DIK_CAPITAL                                                            
	case 0x3B: return "F1          "; break; //DIK_F1                                                                 
	case 0x3C: return "F2          "; break; //DIK_F2                                                                 
	case 0x3D: return "F3          "; break; //DIK_F3                                                                 
	case 0x3E: return "F4          "; break; //DIK_F4                                                                 
	case 0x3F: return "F5          "; break; //DIK_F5                                                                 
	case 0x40: return "F6          "; break; //DIK_F6                                                                 
	case 0x41: return "F7          "; break; //DIK_F7                                                                 
	case 0x42: return "F8          "; break; //DIK_F8                                                                 
	case 0x43: return "F9          "; break; //DIK_F9                                                                 
	case 0x44: return "F10         "; break; //DIK_F10                                                                
	case 0x45: return "NUMLOCK     "; break; //DIK_NUMLOCK                                                            
	case 0x46: return "SCROLL      "; break; //DIK_SCROLL                                                             
	case 0x47: return "NUMPAD7     "; break; //DIK_NUMPAD7                                                            
	case 0x48: return "NUMPAD8     "; break; //DIK_NUMPAD8                                                            
	case 0x49: return "NUMPAD9     "; break; //DIK_NUMPAD9                                                            
	case 0x4A: return "SUBTRACT    "; break; //DIK_SUBTRACT                                                           
	case 0x4B: return "NUMPAD4     "; break; //DIK_NUMPAD4                                                            
	case 0x4C: return "NUMPAD5     "; break; //DIK_NUMPAD5                                                            
	case 0x4D: return "NUMPAD6     "; break; //DIK_NUMPAD6                                                            
	case 0x4E: return "ADD         "; break; //DIK_ADD                                                                
	case 0x4F: return "NUMPAD1     "; break; //DIK_NUMPAD1                                                            
	case 0x50: return "NUMPAD2     "; break; //DIK_NUMPAD2                                                            
	case 0x51: return "NUMPAD3     "; break; //DIK_NUMPAD3                                                            
	case 0x52: return "NUMPAD0     "; break; //DIK_NUMPAD0                                                            
	case 0x53: return "DECIMAL     "; break; //DIK_DECIMAL                                                            
	case 0x56: return "OEM_102     "; break; //DIK_OEM_102                                                            
	case 0x57: return "F11         "; break; //DIK_F11                                                                
	case 0x58: return "F12         "; break; //DIK_F12                                                                
	case 0x64: return "F13         "; break; //DIK_F13                                                                
	case 0x65: return "F14         "; break; //DIK_F14                                                                
	case 0x66: return "F15         "; break; //DIK_F15                                                                
	case 0x70: return "KANA        "; break; //DIK_KANA                                                               
	case 0x73: return "ABNT_C1     "; break; //DIK_ABNT_C1                                                            
	case 0x79: return "CONVERT     "; break; //DIK_CONVERT                                                            
	case 0x7B: return "NOCONVERT   "; break; //DIK_NOCONVERT                                                          
	case 0x7D: return "YEN         "; break; //DIK_YEN                                                                
	case 0x7E: return "ABNT_C2     "; break; //DIK_ABNT_C2                                                            
	case 0x8D: return "NUMPADEQUALS"; break; //DIK_NUMPADEQUALS                                                       
	case 0x90: return "PREVTRACK   "; break; //DIK_PREVTRACK                                                          
	case 0x91: return "AT          "; break; //DIK_AT                                                                 
	case 0x92: return "COLON       "; break; //DIK_COLON                                                              
	case 0x93: return "UNDERLINE   "; break; //DIK_UNDERLINE                                                          
	case 0x94: return "KANJI       "; break; //DIK_KANJI                                                              
	case 0x95: return "STOP        "; break; //DIK_STOP                                                               
	case 0x96: return "AX          "; break; //DIK_AX                                                                 
	case 0x97: return "UNLABELED   "; break; //DIK_UNLABELED                                                          
	case 0x99: return "NEXTTRACK   "; break; //DIK_NEXTTRACK                                                          
	case 0x9C: return "NUMPADENTER "; break; //DIK_NUMPADENTER                                                        
	case 0x9D: return "RCONTROL    "; break; //DIK_RCONTROL                                                           
	case 0xA0: return "MUTE        "; break; //DIK_MUTE                                                               
	case 0xA1: return "CALCULATOR  "; break; //DIK_CALCULATOR                                                         
	case 0xA2: return "PLAYPAUSE   "; break; //DIK_PLAYPAUSE                                                          
	case 0xA4: return "MEDIASTOP   "; break; //DIK_MEDIASTOP                                                          
	case 0xAE: return "VOLUMEDOWN  "; break; //DIK_VOLUMEDOWN                                                         
	case 0xB0: return "VOLUMEUP    "; break; //DIK_VOLUMEUP                                                           
	case 0xB2: return "WEBHOME     "; break; //DIK_WEBHOME                                                            
	case 0xB3: return "NUMPADCOMMA "; break; //DIK_NUMPADCOMMA                                                        
	case 0xB5: return "DIVIDE      "; break; //DIK_DIVIDE                                                             
	case 0xB7: return "SYSRQ       "; break; //DIK_SYSRQ                                                              
	case 0xB8: return "RMENU       "; break; //DIK_RMENU                                                              
	case 0xC5: return "PAUSE       "; break; //DIK_PAUSE                                                              
	case 0xC7: return "HOME        "; break; //DIK_HOME                                                               
	case 0xC8: return "UP          "; break; //DIK_UP                                                                 
	case 0xC9: return "PRIOR       "; break; //DIK_PRIOR                                                              
	case 0xCB: return "LEFT        "; break; //DIK_LEFT                                                               
	case 0xCD: return "RIGHT       "; break; //DIK_RIGHT                                                              
	case 0xCF: return "END         "; break; //DIK_END                                                                
	case 0xD0: return "DOWN        "; break; //DIK_DOWN                                                               
	case 0xD1: return "NEXT        "; break; //DIK_NEXT                                                               
	case 0xD2: return "INSERT      "; break; //DIK_INSERT                                                             
	case 0xD3: return "DELETE      "; break; //DIK_DELETE                                                             
	case 0xDB: return "LWIN        "; break; //DIK_LWIN                                                               
	case 0xDC: return "RWIN        "; break; //DIK_RWIN                                                               
	case 0xDD: return "APPS        "; break; //DIK_APPS                                                               
	case 0xDE: return "POWER       "; break; //DIK_POWER                                                              
	case 0xDF: return "SLEEP       "; break; //DIK_SLEEP                                                              
	case 0xE3: return "WAKE        "; break; //DIK_WAKE                                                               
	case 0xE5: return "WEBSEARCH   "; break; //DIK_WEBSEARCH                                                          
	case 0xE6: return "WEBFAVORITES"; break; //DIK_WEBFAVORITES                                                       
	case 0xE7: return "WEBREFRESH  "; break; //DIK_WEBREFRESH                                                         
	case 0xE8: return "WEBSTOP     "; break; //DIK_WEBSTOP                                                            
	case 0xE9: return "WEBFORWARD  "; break; //DIK_WEBFORWARD                                                         
	case 0xEA: return "WEBBACK     "; break; //DIK_WEBBACK                                                            
	case 0xEB: return "MYCOMPUTER  "; break; //DIK_MYCOMPUTER                                                         
	case 0xEC: return "MAIL        "; break; //DIK_MAIL                                                               
	case 0xED: return "MEDIASELECT "; break; //DIK_MEDIASELECT     
	case MO_LEFT_BUTTON: return "Left Click"; break;
	case MO_RIGHT_BUTTON: return "Right Click"; break;
	case MO_MIDDLE_BUTTON: return "Middle Mouse Button"; break;
	case MO_ZDELTA: return "Mouse Wheel"; break;
	}

	return "NOPE. ";
}

char CharForKey(int keybind, bool caps, bool shift)
{

	if (shift & !caps)
	{
		switch (keybind)
		{
		case 0x02: return '!'; break; //DIK_1                                                                  
		case 0x03: return '@'; break; //DIK_2                                                                  
		case 0x04: return '#'; break; //DIK_3                                                                  
		case 0x05: return '$'; break; //DIK_4                                                                  
		case 0x06: return '%'; break; //DIK_5                                                                  
		case 0x07: return '^'; break; //DIK_6                                                                  
		case 0x08: return '&'; break; //DIK_7                                                                  
		case 0x09: return '*'; break; //DIK_8                                                                  
		case 0x0A: return '('; break; //DIK_9                                                                  
		case 0x0B: return ')'; break; //DIK_0                                                                  
		case 0x0C: return '_'; break; //DIK_MINUS                                                              
		case 0x0D: return '+'; break; //DIK_EQUALS                                                             
		case 0x0E: return ' '; break; //DIK_BACK                                                               
		case 0x0F: return ' '; break; //DIK_TAB                                                                
		case 0x10: return 'Q'; break; //DIK_Q                                                                  
		case 0x11: return 'W'; break; //DIK_W                                                                  
		case 0x12: return 'E'; break; //DIK_E                                                                  
		case 0x13: return 'R'; break; //DIK_R                                                                  
		case 0x14: return 'T'; break; //DIK_T                                                                  
		case 0x15: return 'Y'; break; //DIK_Y                                                                  
		case 0x16: return 'U'; break; //DIK_U                                                                  
		case 0x17: return 'I'; break; //DIK_I                                                                  
		case 0x18: return 'O'; break; //DIK_O                                                                  
		case 0x19: return 'P'; break; //DIK_P                                                                  
		case 0x1A: return '{'; break; //DIK_LBRACKET                                                           
		case 0x1B: return '}'; break; //DIK_RBRACKET                                                           
		case 0x1C: return ' '; break; //DIK_RETURN                                                             
		case 0x1D: return ' '; break; //DIK_LCONTROL                                                           
		case 0x1E: return 'A'; break; //DIK_A                                                                  
		case 0x1F: return 'S'; break; //DIK_S                                                                  
		case 0x20: return 'D'; break; //DIK_D                                                                  
		case 0x21: return 'F'; break; //DIK_F                                                                  
		case 0x22: return 'G'; break; //DIK_G                                                                  
		case 0x23: return 'H'; break; //DIK_H                                                                  
		case 0x24: return 'J'; break; //DIK_J                                                                  
		case 0x25: return 'K'; break; //DIK_K                                                                  
		case 0x26: return 'L'; break; //DIK_L                                                                  
		case 0x27: return ':'; break; //DIK_SEMICOLON                                                          
		case 0x28: return '\"'; break; //DIK_APOSTROPHE                                                         
		case 0x29: return '~'; break; //DIK_GRAVE                                                              
		case 0x2A: return ' '; break; //DIK_LSHIFT                                                             
		case 0x2B: return '|'; break; //DIK_BACKSLASH                                                          
		case 0x2C: return 'Z'; break; //DIK_Z                                                                  
		case 0x2D: return 'X'; break; //DIK_X                                                                  
		case 0x2E: return 'C'; break; //DIK_C                                                                  
		case 0x2F: return 'V'; break; //DIK_V                                                                  
		case 0x30: return 'B'; break; //DIK_B                                                                  
		case 0x31: return 'N'; break; //DIK_N                                                                  
		case 0x32: return 'M'; break; //DIK_M                                                                  
		case 0x33: return '<'; break; //DIK_COMMA                                                              
		case 0x34: return '>'; break; //DIK_PERIOD                                                             
		case 0x35: return '?'; break; //DIK_SLASH                                                              
		case 0x36: return ' '; break; //DIK_RSHIFT                                                             
		case 0x37: return '*'; break; //DIK_MULTIPLY                                                           
		case 0x38: return ' '; break; //DIK_LMENU                                                              
		case 0x39: return ' '; break; //DIK_SPACE                                                              
		case 0x3A: return ' '; break; //DIK_CAPITAL                                                            
		case 0x3B: return ' '; break; //DIK_F1                                                                 
		case 0x3C: return ' '; break; //DIK_F2                                                                 
		case 0x3D: return ' '; break; //DIK_F3                                                                 
		case 0x3E: return ' '; break; //DIK_F4                                                                 
		case 0x3F: return ' '; break; //DIK_F5                                                                 
		case 0x40: return ' '; break; //DIK_F6                                                                 
		case 0x41: return ' '; break; //DIK_F7                                                                 
		case 0x42: return ' '; break; //DIK_F8                                                                 
		case 0x43: return ' '; break; //DIK_F9                                                                 
		case 0x44: return ' '; break; //DIK_F10                                                                
		case 0x45: return ' '; break; //DIK_NUMLOCK                                                            
		case 0x46: return ' '; break; //DIK_SCROLL                                                             
		case 0x47: return '7'; break; //DIK_NUMPAD7                                                            
		case 0x48: return '8'; break; //DIK_NUMPAD8                                                            
		case 0x49: return '9'; break; //DIK_NUMPAD9                                                            
		case 0x4A: return '-'; break; //DIK_SUBTRACT                                                           
		case 0x4B: return '4'; break; //DIK_NUMPAD4                                                            
		case 0x4C: return '5'; break; //DIK_NUMPAD5                                                            
		case 0x4D: return '6'; break; //DIK_NUMPAD6                                                            
		case 0x4E: return '+'; break; //DIK_ADD                                                                
		case 0x4F: return '1'; break; //DIK_NUMPAD1                                                            
		case 0x50: return '2'; break; //DIK_NUMPAD2                                                            
		case 0x51: return '3'; break; //DIK_NUMPAD3                                                            
		case 0x52: return '0'; break; //DIK_NUMPAD0                                                            
		case 0x53: return '.'; break; //DIK_DECIMAL                                                            
		case 0x56: return ' '; break; //DIK_OEM_102                                                            
		case 0x57: return ' '; break; //DIK_F11                                                                
		case 0x58: return ' '; break; //DIK_F12                                                                
		case 0x64: return ' '; break; //DIK_F13                                                                
		case 0x65: return ' '; break; //DIK_F14                                                                
		case 0x66: return ' '; break; //DIK_F15                                                                
		case 0x70: return ' '; break; //DIK_KANA                                                               
		case 0x73: return ' '; break; //DIK_ABNT_C1                                                            
		case 0x79: return ' '; break; //DIK_CONVERT                                                            
		case 0x7B: return ' '; break; //DIK_NOCONVERT                                                          
		case 0x7D: return ' '; break; //DIK_YEN                                                                
		case 0x7E: return ' '; break; //DIK_ABNT_C2                                                            
		case 0x8D: return '='; break; //DIK_NUMPADEQUALS                                                       
		case 0x90: return ' '; break; //DIK_PREVTRACK                                                          
		case 0x91: return ' '; break; //DIK_AT                                                                 
		case 0x92: return ':'; break; //DIK_COLON                                                              
		case 0x93: return '_'; break; //DIK_UNDERLINE                                                          
		case 0x94: return ' '; break; //DIK_KANJI                                                              
		case 0x95: return ' '; break; //DIK_STOP                                                               
		case 0x96: return ' '; break; //DIK_AX                                                                 
		case 0x97: return ' '; break; //DIK_UNLABELED                                                          
		case 0x99: return ' '; break; //DIK_NEXTTRACK                                                          
		case 0x9C: return ' '; break; //DIK_NUMPADENTER                                                        
		case 0x9D: return ' '; break; //DIK_RCONTROL                                                           
		case 0xA0: return ' '; break; //DIK_MUTE                                                               
		case 0xA1: return ' '; break; //DIK_CALCULATOR                                                         
		case 0xA2: return ' '; break; //DIK_PLAYPAUSE                                                          
		case 0xA4: return ' '; break; //DIK_MEDIASTOP                                                          
		case 0xAE: return ' '; break; //DIK_VOLUMEDOWN                                                         
		case 0xB0: return ' '; break; //DIK_VOLUMEUP                                                           
		case 0xB2: return ' '; break; //DIK_WEBHOME                                                            
		case 0xB3: return ' '; break; //DIK_NUMPADCOMMA                                                        
		case 0xB5: return '/'; break; //DIK_DIVIDE                                                             
		case 0xB7: return ' '; break; //DIK_SYSRQ                                                              
		case 0xB8: return ' '; break; //DIK_RMENU                                                              
		case 0xC5: return ' '; break; //DIK_PAUSE                                                              
		case 0xC7: return ' '; break; //DIK_HOME                                                               
		case 0xC8: return ' '; break; //DIK_UP                                                                 
		case 0xC9: return ' '; break; //DIK_PRIOR                                                              
		case 0xCB: return ' '; break; //DIK_LEFT                                                               
		case 0xCD: return ' '; break; //DIK_RIGHT                                                              
		case 0xCF: return ' '; break; //DIK_END                                                                
		case 0xD0: return ' '; break; //DIK_DOWN                                                               
		case 0xD1: return ' '; break; //DIK_NEXT                                                               
		case 0xD2: return ' '; break; //DIK_INSERT                                                             
		case 0xD3: return ' '; break; //DIK_DELETE                                                             
		case 0xDB: return ' '; break; //DIK_LWIN                                                               
		case 0xDC: return ' '; break; //DIK_RWIN                                                               
		case 0xDD: return ' '; break; //DIK_APPS                                                               
		case 0xDE: return ' '; break; //DIK_POWER                                                              
		case 0xDF: return ' '; break; //DIK_SLEEP                                                              
		case 0xE3: return ' '; break; //DIK_WAKE                                                               
		case 0xE5: return ' '; break; //DIK_WEBSEARCH                                                          
		case 0xE6: return ' '; break; //DIK_WEBFAVORITES                                                       
		case 0xE7: return ' '; break; //DIK_WEBREFRESH                                                         
		case 0xE8: return ' '; break; //DIK_WEBSTOP                                                            
		case 0xE9: return ' '; break; //DIK_WEBFORWARD                                                         
		case 0xEA: return ' '; break; //DIK_WEBBACK                                                            
		case 0xEB: return ' '; break; //DIK_MYCOMPUTER                                                         
		case 0xEC: return ' '; break; //DIK_MAIL                                                               
		case 0xED: return ' '; break; //DIK_MEDIASELECT     
		case MO_LEFT_BUTTON: return ' '; break;
		case MO_RIGHT_BUTTON: return ' '; break;
		case MO_MIDDLE_BUTTON: return ' '; break;
		case MO_ZDELTA: return ' '; break;
		}
	}



	switch (keybind)
	{
	//case 0x01: return "ESCAPE      "; break; //DIK_ESCAPE                                                             
	case 0x02: return '1'; break; //DIK_1                                                                  
	case 0x03: return '2'; break; //DIK_2                                                                  
	case 0x04: return '3'; break; //DIK_3                                                                  
	case 0x05: return '4'; break; //DIK_4                                                                  
	case 0x06: return '5'; break; //DIK_5                                                                  
	case 0x07: return '6'; break; //DIK_6                                                                  
	case 0x08: return '7'; break; //DIK_7                                                                  
	case 0x09: return '8'; break; //DIK_8                                                                  
	case 0x0A: return '9'; break; //DIK_9                                                                  
	case 0x0B: return '0'; break; //DIK_0                                                                  
	case 0x0C: return '-'; break; //DIK_MINUS                                                              
	case 0x0D: return '='; break; //DIK_EQUALS                                                             
	case 0x0E: return ' '; break; //DIK_BACK                                                               
	case 0x0F: return ' '; break; //DIK_TAB                                                                
	case 0x10: return 'q'; break; //DIK_Q                                                                  
	case 0x11: return 'w'; break; //DIK_W                                                                  
	case 0x12: return 'e'; break; //DIK_E                                                                  
	case 0x13: return 'r'; break; //DIK_R                                                                  
	case 0x14: return 't'; break; //DIK_T                                                                  
	case 0x15: return 'y'; break; //DIK_Y                                                                  
	case 0x16: return 'u'; break; //DIK_U                                                                  
	case 0x17: return 'i'; break; //DIK_I                                                                  
	case 0x18: return 'o'; break; //DIK_O                                                                  
	case 0x19: return 'p'; break; //DIK_P                                                                  
	case 0x1A: return '['; break; //DIK_LBRACKET                                                           
	case 0x1B: return ']'; break; //DIK_RBRACKET                                                           
	case 0x1C: return ' '; break; //DIK_RETURN                                                             
	case 0x1D: return ' '; break; //DIK_LCONTROL                                                           
	case 0x1E: return 'a'; break; //DIK_A                                                                  
	case 0x1F: return 's'; break; //DIK_S                                                                  
	case 0x20: return 'd'; break; //DIK_D                                                                  
	case 0x21: return 'f'; break; //DIK_F                                                                  
	case 0x22: return 'g'; break; //DIK_G                                                                  
	case 0x23: return 'h'; break; //DIK_H                                                                  
	case 0x24: return 'j'; break; //DIK_J                                                                  
	case 0x25: return 'k'; break; //DIK_K                                                                  
	case 0x26: return 'l'; break; //DIK_L                                                                  
	case 0x27: return ';'; break; //DIK_SEMICOLON                                                          
	case 0x28: return '\''; break; //DIK_APOSTROPHE                                                         
	case 0x29: return '`'; break; //DIK_GRAVE                                                              
	case 0x2A: return ' '; break; //DIK_LSHIFT                                                             
	case 0x2B: return '\\'; break; //DIK_BACKSLASH                                                          
	case 0x2C: return 'z'; break; //DIK_Z                                                                  
	case 0x2D: return 'x'; break; //DIK_X                                                                  
	case 0x2E: return 'c'; break; //DIK_C                                                                  
	case 0x2F: return 'v'; break; //DIK_V                                                                  
	case 0x30: return 'b'; break; //DIK_B                                                                  
	case 0x31: return 'n'; break; //DIK_N                                                                  
	case 0x32: return 'm'; break; //DIK_M                                                                  
	case 0x33: return ','; break; //DIK_COMMA                                                              
	case 0x34: return '.'; break; //DIK_PERIOD                                                             
	case 0x35: return '/'; break; //DIK_SLASH                                                              
	case 0x36: return ' '; break; //DIK_RSHIFT                                                             
	case 0x37: return '*'; break; //DIK_MULTIPLY                                                           
	case 0x38: return ' '; break; //DIK_LMENU                                                              
	case 0x39: return ' '; break; //DIK_SPACE                                                              
	case 0x3A: return ' '; break; //DIK_CAPITAL                                                            
	case 0x3B: return ' '; break; //DIK_F1                                                                 
	case 0x3C: return ' '; break; //DIK_F2                                                                 
	case 0x3D: return ' '; break; //DIK_F3                                                                 
	case 0x3E: return ' '; break; //DIK_F4                                                                 
	case 0x3F: return ' '; break; //DIK_F5                                                                 
	case 0x40: return ' '; break; //DIK_F6                                                                 
	case 0x41: return ' '; break; //DIK_F7                                                                 
	case 0x42: return ' '; break; //DIK_F8                                                                 
	case 0x43: return ' '; break; //DIK_F9                                                                 
	case 0x44: return ' '; break; //DIK_F10                                                                
	case 0x45: return ' '; break; //DIK_NUMLOCK                                                            
	case 0x46: return ' '; break; //DIK_SCROLL                                                             
	case 0x47: return '7'; break; //DIK_NUMPAD7                                                            
	case 0x48: return '8'; break; //DIK_NUMPAD8                                                            
	case 0x49: return '9'; break; //DIK_NUMPAD9                                                            
	case 0x4A: return '-'; break; //DIK_SUBTRACT                                                           
	case 0x4B: return '4'; break; //DIK_NUMPAD4                                                            
	case 0x4C: return '5'; break; //DIK_NUMPAD5                                                            
	case 0x4D: return '6'; break; //DIK_NUMPAD6                                                            
	case 0x4E: return '+'; break; //DIK_ADD                                                                
	case 0x4F: return '1'; break; //DIK_NUMPAD1                                                            
	case 0x50: return '2'; break; //DIK_NUMPAD2                                                            
	case 0x51: return '3'; break; //DIK_NUMPAD3                                                            
	case 0x52: return '0'; break; //DIK_NUMPAD0                                                            
	case 0x53: return '.'; break; //DIK_DECIMAL                                                            
	case 0x56: return ' '; break; //DIK_OEM_102                                                            
	case 0x57: return ' '; break; //DIK_F11                                                                
	case 0x58: return ' '; break; //DIK_F12                                                                
	case 0x64: return ' '; break; //DIK_F13                                                                
	case 0x65: return ' '; break; //DIK_F14                                                                
	case 0x66: return ' '; break; //DIK_F15                                                                
	case 0x70: return ' '; break; //DIK_KANA                                                               
	case 0x73: return ' '; break; //DIK_ABNT_C1                                                            
	case 0x79: return ' '; break; //DIK_CONVERT                                                            
	case 0x7B: return ' '; break; //DIK_NOCONVERT                                                          
	case 0x7D: return ' '; break; //DIK_YEN                                                                
	case 0x7E: return ' '; break; //DIK_ABNT_C2                                                            
	case 0x8D: return '='; break; //DIK_NUMPADEQUALS                                                       
	case 0x90: return ' '; break; //DIK_PREVTRACK                                                          
	case 0x91: return ' '; break; //DIK_AT                                                                 
	case 0x92: return ':'; break; //DIK_COLON                                                              
	case 0x93: return '_'; break; //DIK_UNDERLINE                                                          
	case 0x94: return ' '; break; //DIK_KANJI                                                              
	case 0x95: return ' '; break; //DIK_STOP                                                               
	case 0x96: return ' '; break; //DIK_AX                                                                 
	case 0x97: return ' '; break; //DIK_UNLABELED                                                          
	case 0x99: return ' '; break; //DIK_NEXTTRACK                                                          
	case 0x9C: return ' '; break; //DIK_NUMPADENTER                                                        
	case 0x9D: return ' '; break; //DIK_RCONTROL                                                           
	case 0xA0: return ' '; break; //DIK_MUTE                                                               
	case 0xA1: return ' '; break; //DIK_CALCULATOR                                                         
	case 0xA2: return ' '; break; //DIK_PLAYPAUSE                                                          
	case 0xA4: return ' '; break; //DIK_MEDIASTOP                                                          
	case 0xAE: return ' '; break; //DIK_VOLUMEDOWN                                                         
	case 0xB0: return ' '; break; //DIK_VOLUMEUP                                                           
	case 0xB2: return ' '; break; //DIK_WEBHOME                                                            
	case 0xB3: return ' '; break; //DIK_NUMPADCOMMA                                                        
	case 0xB5: return '/'; break; //DIK_DIVIDE                                                             
	case 0xB7: return ' '; break; //DIK_SYSRQ                                                              
	case 0xB8: return ' '; break; //DIK_RMENU                                                              
	case 0xC5: return ' '; break; //DIK_PAUSE                                                              
	case 0xC7: return ' '; break; //DIK_HOME                                                               
	case 0xC8: return ' '; break; //DIK_UP                                                                 
	case 0xC9: return ' '; break; //DIK_PRIOR                                                              
	case 0xCB: return ' '; break; //DIK_LEFT                                                               
	case 0xCD: return ' '; break; //DIK_RIGHT                                                              
	case 0xCF: return ' '; break; //DIK_END                                                                
	case 0xD0: return ' '; break; //DIK_DOWN                                                               
	case 0xD1: return ' '; break; //DIK_NEXT                                                               
	case 0xD2: return ' '; break; //DIK_INSERT                                                             
	case 0xD3: return ' '; break; //DIK_DELETE                                                             
	case 0xDB: return ' '; break; //DIK_LWIN                                                               
	case 0xDC: return ' '; break; //DIK_RWIN                                                               
	case 0xDD: return ' '; break; //DIK_APPS                                                               
	case 0xDE: return ' '; break; //DIK_POWER                                                              
	case 0xDF: return ' '; break; //DIK_SLEEP                                                              
	case 0xE3: return ' '; break; //DIK_WAKE                                                               
	case 0xE5: return ' '; break; //DIK_WEBSEARCH                                                          
	case 0xE6: return ' '; break; //DIK_WEBFAVORITES                                                       
	case 0xE7: return ' '; break; //DIK_WEBREFRESH                                                         
	case 0xE8: return ' '; break; //DIK_WEBSTOP                                                            
	case 0xE9: return ' '; break; //DIK_WEBFORWARD                                                         
	case 0xEA: return ' '; break; //DIK_WEBBACK                                                            
	case 0xEB: return ' '; break; //DIK_MYCOMPUTER                                                         
	case 0xEC: return ' '; break; //DIK_MAIL                                                               
	case 0xED: return ' '; break; //DIK_MEDIASELECT     
	case MO_LEFT_BUTTON: return ' '; break;
	case MO_RIGHT_BUTTON: return ' '; break;
	case MO_MIDDLE_BUTTON: return ' '; break;
	case MO_ZDELTA: return ' '; break;
	}

	return ' ';
}