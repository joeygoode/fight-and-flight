#pragma once

//header files
#define WIN32_EXTRA_LEAN
#define DirectInput_Version 0x0800
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <xinput.h>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

//libraries
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "xinput.lib")

//Program Values
extern string APPTITLE;
extern int SCREENW;
extern int SCREENH;
extern bool gameover;

//Direct 3D Objects
extern LPDIRECT3D10 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPD3DXSPRITE spriteobj;

//Direct 3D functions
bool Direct3D_Init(HWND hwnd,int windt, int height, bool fullscreen);
void Direct3D_Shutdown();
LPDIRECT3DSURFACE9 LoadSurface(string filename);
void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source);
D3DXVECTOR2 GetBitmapSize(string filename);
LPDIRECT3DTEXTURE9 LoadTexture(string filename,D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0));
RECT Sprite_Get_SrcRect(int framenum, int spritewidth, int spriteheight, bool horiz, int numroworcol, int horizoffset, int vertoffset, int delim);
LPD3DXFONT MakeFont(string name, int size);
void FontPrint(LPD3DXFONT font, int x, int y, string text, D3DXCOLOR color = D3DCOLOR_XRGB(255,255,255));

//Direct Input objects, devices, and states
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
extern DIMOUSESTATE mouse_state;
extern XINPUT_GAMEPAD controllers[4];

//Direct Input Functions
bool DirectInput_Init(HWND);
void DirectInput_Update();
void DirectInput_Shutdown();
int Key_Down(int);
int Mouse_Button(int);
int Mouse_X();
int Mouse_Y();
void XInput_Vibrate(int contNum = 0, int ammount = 65535);
bool XInput_Controller_Found();

//Game Functions 
void ReadWindowSettingsFromXML();
bool Game_Init(HWND window);
void Game_Run(HWND window);
void Game_End();

//Math Utilities
bool intersect(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d);

