#include "sprite.h"
#include "trace.h"

CSprite::CSprite(LPD3DXSPRITE __SpriteHandler, LPCSTR _filePath, int _width, int _height, int _count, int _spritePerRow)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	image = NULL;
	_SpriteHandler = __SpriteHandler;

	width = _width;
	height = _height;
	count = _count;
	spritePerRow = _spritePerRow;
	index = 0;

	result = D3DXGetImageInfoFromFile(_filePath, &info);
	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to get information from image file '%s'", _filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	_SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		_filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&image);

	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to create texture from file '%s'", _filePath);
		return;
	}
}

CSprite::~CSprite()
{
	image->Release();
}

void CSprite::Next()
{
	index = (index + count - 1) % count;
}

void CSprite::Reset()
{
	index = 0;
}

// render sprite hien tai tai vi vi tri x,y
void CSprite::Render(int posX, int posY)
{
	this->Render(NULL, posX, posY);
}
// render sprite hien tai tai vi vi tri x,y va  doi tuong surface nao do
void CSprite::Render(LPDIRECT3DSURFACE9 targetSurface, int posX, int posY)
{
	RECT srect;

	srect.left = (index % spritePerRow) * (width) + 1;
	srect.top = (index / spritePerRow) * (height) + 1;
	srect.right = srect.left + width;
	srect.bottom = srect.top + height + 1;

	D3DXVECTOR3 position((float)posX, (float)posY, 0);

	_SpriteHandler->Draw(
		image,
		&srect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}
