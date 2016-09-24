#pragma once
#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "game.h"
#include "CRectangle.h"
#include "sprite.h"

class GameScene : public CGame
{
protected:
	CRectangle *ball, *racket;

	LPDIRECT3DSURFACE9 ballSurface;
	LPDIRECT3DSURFACE9 racketSurface;

	// SPRITE
	//LPD3DXSPRITE _SpriteHandler;
	//CSprite* ballx;
	
	// ham render cho nhieu frame
	virtual void renderFrame(LPDIRECT3DDEVICE9 d3ddev, int delta);

	// ham load resource
	virtual	void loadResource(LPDIRECT3DDEVICE9 d3ddev);


	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void OnKeyDown(int KeyCode);

public:
	GameScene(HINSTANCE hInstance, LPCSTR name, int mode, int isFullScreen, int frameRate);
	~GameScene();
};
#endif // !__GAMESCENE_H__

