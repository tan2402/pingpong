#include "GameScene.h"

#include <time.h>
#include <d3dx9.h>
#include "racket.h"
#include "trace.h"
#include "utils.h"


GameScene::GameScene(HINSTANCE hInstance, LPCSTR name, int mode, int isFullScreen, int frameRate) :
	CGame(hInstance, name, mode, isFullScreen, frameRate)
{
	ballSurface = NULL;
	racketSurface = NULL;

	//ballx = NULL;
}

GameScene::~GameScene()
{
	delete ball;
	delete racket;
	//delete ballx;
}

//int GameScene::loadSurface(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DSURFACE9 &surface, char *filename, int width, int height)
//{
//	// Fill the bitmap
//	//d3ddev->ColorFill(surface, NULL, D3DCOLOR_XRGB(100, 100, 100));
//
//	// Create a small off-screen surface (will fill it contain in GameRun)
//	d3ddev->CreateOffscreenPlainSurface(
//		width,					// width 				
//		height,					// height
//		backBufferFormat,		// format
//		D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
//		&surface,
//		NULL);
//
//	
//	// Load image
//	int result = D3DXLoadSurfaceFromFile(
//		surface, 		// surface
//		NULL,			// destination palette	
//		NULL,			// destination rectangle 
//		filename,
//		NULL,			// source rectangle
//		D3DX_DEFAULT, 	// filter image
//		D3DCOLOR_XRGB(0, 0, 0),				// transparency (0 = none)
//		NULL);			// reserved
//		
//	return 0;
//}


void GameScene::loadResource(LPDIRECT3DDEVICE9 d3ddev)
{
	// ham load rescource: load hinh anh, tao sprite, tao rectangle....
	

	// create sprite
	//D3DXCreateSprite(d3ddev, &_SpriteHandler);
	//ballx = new CSprite(_SpriteHandler, "ball.png", 53, 53, 1, 1);
	
	// create surface
	ballSurface = CreateSurfaceFromFile(d3ddev, "ball.png");
	racketSurface = CreateSurfaceFromFile(d3ddev, "racket.png");


	// khoi tao doi tuong CRectangle
	float vx = (((rand() % 80) + 20) * (rand() % 2 == 0 ? 1 : -1)) / 100.0;
	float vy = (((rand() % 80) + 20) * (rand() % 2 == 0 ? 1 : -1)) / 100.0;
	ball = new CRectangle(300, 300, 25, 25);

	ball->setVelocityX(vx);
	ball->setVelocityY(vy);

	// khoi tao doi tuong racket
	racket = new CRectangle(200, 100, 50, 378);
	racket->setVelocityX(0);
	racket->setVelocityY(0);

	srand((unsigned)time(NULL));
}

void GameScene::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	if (isKeyDown(DIK_UP))
	{
		trace(L".............left");
		racket->MoveBy(0, -7, screenWidth, screenHeight);
	}
	else if (isKeyDown(DIK_DOWN))
	{
		trace(L".............right");
		racket->MoveBy(0, 7, screenWidth, screenHeight);
	}
	else if(isKeyDown(DIK_LEFT))
	{
		//ball->MoveBy(-5, 0, screenWidth, screenHeight);
	}
	else if (isKeyDown(DIK_RIGHT))
	{
		//ball->MoveBy(5, 0, screenWidth, screenHeight);
	}
}

void GameScene::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		
		break;
	}
}

void GameScene::renderFrame(LPDIRECT3DDEVICE9 d3ddev, int delta)
{
	d3ddev->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));


	ball->moveNext(delta, screenWidth, screenHeight, racket->getPositionX(), racket->getPositionY(), racket->getWidth(), racket->getHeight());

	RECT rec;
	rec.left = ball->getPositionX();
	rec.top = ball->getPositionY();
	rec.right = rec.left + ball->getWidth();
	rec.bottom = rec.top + ball->getHeight();

	// Draw the surface onto the back buffer
	d3ddev->StretchRect(
		ballSurface,		// from 
		NULL,				// which portion?
		backBuffer,			// to 
		&rec,				// which portion?
		D3DTEXF_NONE);


	// Draw racket
	RECT racketRECT;
	racketRECT.left = racket->getPositionX();
	racketRECT.top = racket->getPositionY();
	racketRECT.right = racketRECT.left + racket->getWidth();
	racketRECT.bottom = racketRECT.top + racket->getHeight();

	// Draw the surface onto the back buffer
	d3ddev->StretchRect(
		racketSurface,			// from 
		NULL,				// which portion?
		backBuffer,		// to 
		&racketRECT,				// which portion?
		D3DTEXF_NONE);


	//draw sprite
	//_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//ballx->Render(100, 300);

	//_SpriteHandler->End();
}

