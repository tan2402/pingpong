#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <windows.h>
#include <d3d9.h>
#include <dinput.h>

// Screen resolution
//
#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12

#define KEYBOARD_BUFFER_SIZE	1024
class CGame
{
protected:

	// cac parameter cua Direct3D
	LPDIRECT3D9			d3d;			// bien direct3d
	LPDIRECT3DDEVICE9	d3ddev;			// bien direct3d device
	LPDIRECT3DSURFACE9	backBuffer;		//bien direct3d sufure

	// cac param cua DirectInput
	LPDIRECTINPUT8			dInput; // doi tuong direct input
	LPDIRECTINPUTDEVICE8	didev;	// doi tuong direct input device: mouse, keyboard...

	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 		
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data



	DWORD deltaTime;					// khoang cach giua frame cuoi cung va frame hien tai
	int mode;		// fullscreen or windowed
	int isFullScreen;
	int frameRate;

	int screenWidth;
	int screenHeight;
	int depth;

	D3DFORMAT backBufferFormat;

	HINSTANCE hInstance;		// xu ly game
	HWND hWnd;					// xu ly cua so game
	LPCSTR name;				// ten game (ten cua so)

	void setScreenDimension(int mode); //

	// xu ly su kien
	static LRESULT CALLBACK winProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// ham khoi tao cua so
	void initWindow();

	//ham khoi tao DirectX
	void initDirectX();

	//ham khoi tao Direct Input Device
	void initDirectInputDevice();

	// ham render cho 1 frame
	void renderSingleFrame();

	// ham render cho nhieu frame
	virtual void renderFrame(LPDIRECT3DDEVICE9 d3ddev, int delta);

	// ham load resource
	virtual	void loadResource(LPDIRECT3DDEVICE9 d3ddev);

	////
	void processKeyboard();
	int isKeyDown(int keyCode);

	// ham xu ly input
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);

	// xu ly su kien key down: nhan ban phim
	virtual void OnKeyDown(int KeyCode);

	// xy ly su kien key up: tha ban phim
	virtual void OnKeyUp(int KeyCode);

public:
	
	// constructor
	CGame(HINSTANCE hInstance, LPCSTR name, int mode, int isFullScreen, int frameRate);

	// destructor
	~CGame();

	// ham khoi tao game
	void Init();

	// run
	void Run();
};
#endif // !__GAME_H__
