#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__
#include "game.h"
#include "CRectangle.h"

class CBall : public CGame
{
protected:
	CRectangle *rect;

	LPDIRECT3DSURFACE9 surface;

	// ham render cho nhieu frame
	virtual void renderFrame(LPDIRECT3DDEVICE9 d3ddev, int delta);

	// ham load resource
	virtual	void loadResource(LPDIRECT3DDEVICE9 d3ddev);

public:
	CBall(HINSTANCE hInstance, LPCSTR name, int mode, int isFullScreen, int frameRate);
	~CBall();
};
#endif // !__SPRITE_H__
