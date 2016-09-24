#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>
class CSprite
{
protected:
	LPDIRECT3DTEXTURE9 image;
	LPD3DXSPRITE _SpriteHandler;

	int index; // chi so sprite hien tai
	int width;	// do rong cua sprite
	int height;	// chieu cao cua sprite
	int count;	// so luong sprite/ frame anh
	int spritePerRow;	// so luong sprite/ frame anh tren 1 hang

public:
	CSprite::CSprite(LPD3DXSPRITE __SpriteHandler, LPCSTR _filePath, int _width, int _height, int _count, int _spritePerRow);
	~CSprite();
	
	void Next();
	void Reset();


	// render sprite hien tai tai vi vi tri x,y va tai doi tuong surface nao do
	void Render(int posX, int posY);
	void Render(LPDIRECT3DSURFACE9 targetSurface, int posX, int posY);
};
#endif 

