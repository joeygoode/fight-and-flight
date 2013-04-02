#include "MyDirectX.h"
#include <iostream>
using namespace std;

//Direct3D variables
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;
LPD3DXSPRITE spriteobj = NULL;

//Direct Input Variables
LPDIRECTINPUT8 dinput = NULL;
LPDIRECTINPUTDEVICE8 dimouse = NULL;
LPDIRECTINPUTDEVICE8 dikeyboard = NULL;
DIMOUSESTATE mouse_state;
char keys[256];
XINPUT_GAMEPAD controllers[4];

//Direct 3D Initialization
bool Direct3D_Init(HWND window, int width, int height, bool fullscreen)
{
	//initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) return false;

	//set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = window;

	//create Direct 3D Device
	d3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,window,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &d3ddev);
	if(!d3ddev) return false;

	//get a pointer to the back buffer surface
	d3ddev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);

	//create sprite object
	D3DXCreateSprite(d3ddev, &spriteobj);

	return true;
}
//Direct 3D Shutdown
void Direct3D_Shutdown()
{
	if(spriteobj) spriteobj->Release();
	if(d3ddev) d3ddev->Release();
	if(d3d) d3d->Release();
}

//Draws a surface to the screen using StretchRect

void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source)
{
	//get width/height from source surface
	D3DSURFACE_DESC desc;
	source->GetDesc(&desc);

	//create rects for drawing
	RECT source_rect = {0,0,(long)desc.Width, (long) desc.Height};
	RECT dest_rect = {(long) x, (long) y, (long) x+desc.Width, (long) y+desc.Height};

	//draw the source surface onto the dest
	d3ddev->StretchRect(source, &source_rect, dest, &dest_rect, D3DTEXF_NONE);
}

//Loads a bitmap file into a surface

LPDIRECT3DSURFACE9 LoadSurface(string filename)
{
	LPDIRECT3DSURFACE9 image = NULL;

	//get width and height from bitmap file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (result != D3D_OK) return NULL;

	//create surface
	result = d3ddev->CreateOffscreenPlainSurface(info.Width,info.Height,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&image,NULL);

	if (result != D3D_OK) return NULL;

	//load surface from file into newly created surface
	result = D3DXLoadSurfaceFromFile(image,NULL, NULL, filename.c_str(),NULL,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),NULL);

	if (result != D3D_OK) return NULL;

	return image;
}

bool DirectInput_Init(HWND hwnd)
{
	//initialize DirectInput object
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&dinput,NULL);

	//initialize thekeyboard
	dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	dikeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	dikeyboard->Acquire();

	//initialize the mouse
	dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
	dimouse->SetDataFormat(&c_dfDIMouse);
	dimouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	dimouse->Acquire();
	d3ddev->ShowCursor(false);

	return true;
}

//DirectInput update
void DirectInput_Update()
{
	//update mouse
	dimouse->GetDeviceState(sizeof(mouse_state), (LPVOID) &mouse_state);

	//update keyboard
	dikeyboard->GetDeviceState(sizeof(keys), (LPVOID) &keys);

	//UPDATE CONTROLLERS
	for (int i = 0; i<4; i++)
	{
		ZeroMemory(&controllers[i], sizeof (XINPUT_STATE));

		//GET THE STATE OF THE CONTROLLER
		XINPUT_STATE state;
		DWORD result = XInputGetState(i, &state);

		//store state in global controllers array
		if (result == 0) controllers[i] = state.Gamepad;
	}
}

//Return mouse x movement
int Mouse_X()
{
	return mouse_state.lX;
}

//Return mouse y movement
int Mouse_Y()
{
	return mouse_state.lY;
}

//Return mouse button state
int Mouse_Button(int button)
{
	return mouse_state.rgbButtons[button] & 0x80;
}

//return key press state
int Key_Down(int key)
{
	return (keys[key] & 0x80);
}

//DirectInput shutdown
void DirectInput_Shutdown()
{
	if (dikeyboard)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
	if (dimouse)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}
}

//Returns true if controller is plugged in
bool XInput_Controller_Found()
{
	XINPUT_CAPABILITIES caps;
	ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
	XInputGetCapabilities(0, XINPUT_FLAG_GAMEPAD, &caps);
	if (caps.Type != 0) return false;

	return true;
}

//Vibrate the controller
void XInput_Vibrate(int contNum, int amount)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = amount;
	vibration.wRightMotorSpeed = amount;
	XInputSetState(contNum, &vibration);
}

LPDIRECT3DTEXTURE9 LoadTexture(string filename, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	cout << "attempting to load textures" << endl;
	//get width and height from bitmap file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if(result != D3D_OK) return NULL;

	//Create the new texture by loading a bitmap image file
	result = D3DXCreateTextureFromFileEx(d3ddev, filename.c_str(), info.Width , info.Height, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,transcolor,&info,NULL, &texture);
	//make sure the bitmap texture was loaded correctly
	if(result != D3D_OK) return NULL;

	return texture;
}

D3DXVECTOR2 GetBitmapSize(string filename)
{
	D3DXIMAGE_INFO info;
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f,0.0f);
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (result == D3D_OK)
		size = D3DXVECTOR2((float)info.Width, (float) info.Height);
	else
		size = D3DXVECTOR2((float) info.Width, (float) info.Height);
	return size;
}

RECT Sprite_Get_SrcRect(int framenum, int spritewidth, int spriteheight, bool horiz, int numroworcol, int horizoffset, int vertoffset, int delim)
{
	//horiz indicates the frame order goes horizontally or vertically
	RECT srcRect = RECT();
	if (horiz)
	{
		srcRect.left = horizoffset + (framenum % numroworcol) * (spritewidth + delim);
		srcRect.top = vertoffset + (framenum / numroworcol) * (spriteheight + delim);
	}
	else
	{
		srcRect.left = horizoffset + (framenum / numroworcol) * (spritewidth + delim);
		srcRect.top = vertoffset + (framenum % numroworcol) * (spriteheight + delim);
	}
	srcRect.bottom = srcRect.top + spriteheight;
	srcRect.right = srcRect.left + spritewidth;

	return srcRect;
}

bool intersect(D3DXVECTOR2 a,D3DXVECTOR2 b,D3DXVECTOR2 c,D3DXVECTOR2 d)
{
	float den = ((d.y-c.y)*(b.x-a.x)-(d.x-c.x)*(b.y-a.y)); 
	float num1 = ((d.x - c.x)*(a.y-c.y) - (d.y- c.y)*(a.x-c.x)); 
	float num2 = ((b.x-a.x)*(a.y-c.y)-(b.y-a.y)*(a.x-c.x)); 
	float u1 = num1/den; 
	float u2 = num2/den;
	std::cout << u1 << ":" << u2 << std::endl; 
	if (den == 0 && num1 == 0 && num2 == 0)
		/* The two lines are coincidents */
		return false;
	if (den == 0) 
		/* The two lines are parallel */ 
		return false; 
	if (u1 <0 || u1 > 1 || u2 < 0 || u2 > 1) 
		/* Lines do not collide */ 
		return false; 
	/* Lines DO collide */ 
	return true; 
} 
LPD3DXFONT MakeFont(string name, int size)
{
	LPD3DXFONT font = NULL;
	D3DXFONT_DESC desc = {
		size,
		0,
		0,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH,
		""
	};
	strcpy(desc.FaceName, name.c_str());
	D3DXCreateFontIndirect(d3ddev, &desc, &font);
	return font;
}

void FontPrint(LPD3DXFONT font, int x, int y, string text, D3DXCOLOR color)
{
	RECT rect = {x,y,0,0};
	HRESULT result = font->DrawText(NULL,text.c_str(),text.length(),&rect,DT_CALCRECT,color);
	if (SUCCEEDED(result))
	{
		cout << result << endl;
	}
	result = font->DrawText(NULL,text.c_str(),text.length(),&rect,DT_LEFT,color);
	if (SUCCEEDED(result))
	{
		cout << result << endl;
	}
}