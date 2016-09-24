#pragma once
#ifndef __RACKET_H__
#define __RACKET_H__
#include "game.h"
#include "CRectangle.h"

class CRacket : public CGame
{
protected:
	CRectangle *rect;

	LPDIRECT3DSURFACE9 surface;

	// ham render cho nhieu frame
	virtual void renderFrame(LPDIRECT3DDEVICE9 d3ddev, int delta);

	// ham load resource
	virtual	void loadResource(LPDIRECT3DDEVICE9 d3ddev);

public:
	CRacket(HINSTANCE hInstance, LPCSTR name, int mode, int isFullScreen, int frameRate);
	~CRacket();
};
#endif // !__RACKET_H__

