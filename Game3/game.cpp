#include <windows.h>
#include "game.h"
#include "trace.h"

#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0 )

CGame::CGame(HINSTANCE hInstance, LPCSTR name, int mode, int isFullScreen, int frameRate)
{
	this->d3d = NULL;
	this->d3ddev = NULL;
	this->backBuffer = NULL;

	this->mode = mode;
	this->setScreenDimension(mode);
	this->name = name;
	this->isFullScreen = isFullScreen;
	this->frameRate = frameRate;
	this->hInstance = hInstance;

	this->dInput = NULL;
	this->didev = NULL;
}

CGame::~CGame()
{
	if (d3d != NULL)
		d3d->Release();
	if (d3ddev != NULL)
		d3ddev->Release();
}



void CGame::Run()
{
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 100 / frameRate;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		deltaTime = now - frame_start;
		if (deltaTime >= tick_per_frame)
		{
			frame_start = now;
			renderSingleFrame();
		}

		processKeyboard();
		ProcessInput(d3ddev, deltaTime);

		// TO-DO: need to improve in later version
		if (KEY_DOWN(VK_ESCAPE)) PostMessage(hWnd, WM_QUIT, 0, 0);
	}
}

void CGame::setScreenDimension(int mode)
{
	switch (mode)
	{
	case GAME_SCREEN_RESOLUTION_640_480_24:
		screenWidth = 640;
		screenHeight = 480;
		depth = 24;
		backBufferFormat = D3DFMT_X8R8G8B8;
		break;

	case GAME_SCREEN_RESOLUTION_800_600_24:
		screenWidth = 800;
		screenHeight = 600;
		depth = 24;
		backBufferFormat = D3DFMT_X8R8G8B8;
		break;

	case GAME_SCREEN_RESOLUTION_1024_768_24:
		screenWidth = 1024;
		screenHeight = 768;
		depth = 24;
		backBufferFormat = D3DFMT_X8R8G8B8;
		break;

	default:
		break;
	}
}

LRESULT CGame::winProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void CGame::initWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = this->hInstance;
	wc.lpfnWndProc = (WNDPROC)CGame::winProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = this->name;
	wc.lpszMenuName = NULL;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	DWORD style;
	if (this->isFullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	this->hWnd =
		CreateWindow(
			this->name,
			this->name,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			this->screenWidth,
			this->screenHeight,
			NULL,
			NULL,
			this->hInstance,
			NULL);

	if (this->hWnd)
	{
		DWORD ErrCode = GetLastError();
	}

	ShowWindow(this->hWnd, SW_SHOWNORMAL);
	UpdateWindow(this->hWnd);
}

void CGame::initDirectX()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = isFullScreen ? FALSE : TRUE;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.BackBufferFormat = backBufferFormat;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = screenHeight;
	d3dpp.BackBufferWidth = screenWidth;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL)
	{

	}

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
}

void CGame::initDirectInputDevice()
{
	HRESULT	hr = DirectInput8Create
		(
			this->hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&dInput, NULL
		);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	trace(L"DirectInput has been created");

	hr = dInput->CreateDevice(GUID_SysKeyboard, &didev, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	trace(L"DirectInput keyboard has been created");

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didev->SetDataFormat(&c_dfDIKeyboard);

	//trace(L"SetDataFormat for keyboard successfully");

	hr = didev->SetCooperativeLevel(this->hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	trace(L"SetCooperativeLevel for keyboard successfully");

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	trace(L"SetProperty for keyboard successfully");

	hr = didev->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = didev->Acquire();
	if (hr != DI_OK) return;

	trace(L"Keyboard has been acquired successfully");
}

void CGame::Init()
{
	initWindow();
	initDirectX();
	initDirectInputDevice();
	loadResource(d3ddev);
}

void CGame::processKeyboard()
{
	// lay tat ca cac su kien lien quan den keyboard
	didev->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	if (isKeyDown(DIK_ESCAPE))
	{
		//trace(L"Escape key pressed!");
		PostMessage(this->hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = didev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

void CGame::renderSingleFrame()
{
	if (d3ddev->BeginScene())
	{
		renderFrame(d3ddev, deltaTime);
		d3ddev->EndScene();
	}
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void CGame::renderFrame(LPDIRECT3DDEVICE9 d3ddev, int delta)
{
}

void CGame::loadResource(LPDIRECT3DDEVICE9 d3ddev)
{
}



int CGame::isKeyDown(int keyCode)
{
	return (_KeyStates[keyCode] & 0x80) > 0;
}

void CGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
}

void CGame::OnKeyDown(int KeyCode)
{
}

void CGame::OnKeyUp(int KeyCode)
{
}
