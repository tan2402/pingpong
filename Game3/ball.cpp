#include <time.h>
#include <d3dx9.h>
#include "ball.h"

#define BALL_IMAGE "ball.png"


CBall::CBall(HINSTANCE hInstance, LPCSTR name, int mode, int isFullScreen, int frameRate) :
	CGame(hInstance, name, mode, isFullScreen, frameRate)
{
	surface = NULL;
}

CBall::~CBall()
{
	delete rect;
}



void CBall::loadResource(LPDIRECT3DDEVICE9 d3ddev)
{
	// ham load rescource: load hinh anh, tao sprite, tao rectangle....


	// Create a small off-screen surface (will fill it contain in GameRun)
	d3ddev->CreateOffscreenPlainSurface(
		53,				// width 				
		53,			// height
		backBufferFormat,		// format
		D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
		&surface,
		NULL);

	// Fill the bitmap
	//d3ddev->ColorFill(surface, NULL, D3DCOLOR_XRGB(100, 100, 100));

	// Load ball image
	int result = D3DXLoadSurfaceFromFile(
		surface, 		// surface
		NULL,			// destination palette	
		NULL,			// destination rectangle 
		BALL_IMAGE,
		NULL,			// source rectangle
		D3DX_DEFAULT, 	// filter image
		D3DCOLOR_XRGB(0, 0, 0),				// transparency (0 = none)
		NULL);			// reserved
		

		if (result!=D3D_OK)
		{
			// khong the load hinh len duoc
		}

	// khoi tao doi tuong CRectangle
	float vx = (((rand() % 80) + 20) * (rand() % 2 == 0 ? 1 : -1)) / 100.0;
	float vy = (((rand() % 80) + 20) * (rand() % 2 == 0 ? 1 : -1)) / 100.0;
	rect = new CRectangle(100, 100, 25, 25);

	rect->setVelocityX(vx);
	rect->setVelocityY(vy);

	srand((unsigned)time(NULL));
}

void CBall::renderFrame(LPDIRECT3DDEVICE9 d3ddev, int delta)
{
	d3ddev->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));

	
		rect->moveNext(delta, screenWidth, screenHeight);

		RECT rec;
		rec.left = rect->getPositionX();
		rec.top = rect->getPositionY();
		rec.right = rec.left + rect->getWidth();
		rec.bottom = rec.top + rect->getHeight();

		// Draw the surface onto the back buffer
		d3ddev->StretchRect(
			surface,			// from 
			NULL,				// which portion?
			backBuffer,		// to 
			&rec,				// which portion?
			D3DTEXF_NONE);
}



