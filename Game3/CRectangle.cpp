#include "CRectangle.h"
#include "trace.h"
CRectangle::CRectangle()
{
	this->height = 0;
	this->width = 0;
	this->positionX = this->positionY = 0;
}

CRectangle::CRectangle(double width, double height)
{

	this->height = height;
	this->width = width;
	this->positionX = this->positionY = 0;

}

CRectangle::CRectangle(double posX, double posY, double width, double height)
{

	this->height = height;
	this->width = width;
	this->positionX = posX;
	this->positionY = posY;

}

CRectangle::~CRectangle()
{
}

void CRectangle::setPosition(double x, double y)
{
	this->positionX = x;
	this->positionY = y;

}

void CRectangle::setPositionX(double x)
{
	this->positionX = x;
}

void CRectangle::setPositionY(double y)
{
	this->positionY = y;
}

double CRectangle::getPositionX()
{
	return this->positionX;
}

double CRectangle::getPositionY()
{
	return this->positionY;
}

void CRectangle::setVelocityX(float Vx)
{
	this->velocityX = Vx;
}

void CRectangle::setVelocityY(float Vy)
{
	this->velocityY = Vy;
}

float CRectangle::getVelocityX()
{
	return this->velocityX;
}

float CRectangle::getVelocityY()
{
	return this->velocityY;
}

double CRectangle::getWidth()
{
	return this->width;
}

double CRectangle::getHeight()
{
	return this->height;
}

void CRectangle::setWidth(double width)
{
	this->width = width;
}

void CRectangle::setHeight(double height)
{
	this->height = height;
}

void CRectangle::MoveTo(double x, double y)
{

}

void CRectangle::MoveBy(double distanceX, double distanceY, int screenWidth, int screenHeight)
{
	//MoveBy: di chuyen them 1 doan (distanceX, distanceY)
	// update lai position
	/*if (this->getPositionX() <= 0 || 
		(this->getPositionX() + this->getWidth()) >= screenWidth)
	{
		return;
	}
	
	if (this->getPositionY() <= 0 ||
		this->getPositionY() + this->getHeight() >= screenHeight)
	{
		return;
	}

	this->positionX += distanceX;
	this->positionY += distanceY;*/

	// kiem tra distanceX voi khoang cach con lai
	// vd truong hop distanceX = 5 ma khoang cach con lai = 3 --> bi mat object
	
	
	

	if (distanceX > 0 && this->getPositionX() + this->getWidth() < screenWidth)
	{
		// di chuyen qua ben phai
		double disX = screenWidth - (this->getPositionX() + this->getWidth());
		if (distanceX > disX)
			distanceX = disX;
		
		this->positionX += distanceX;
		trace(L"dis X = %f", disX);
		trace(L"distanceX = %f", distanceX);
		
	}
	else if (distanceX < 0 && this->getPositionX() > 0)
	{
		//di chuyen qua trai
		double disX = this->getPositionX();
		if (-distanceX > disX)
			distanceX = -disX;

		this->positionX += distanceX;
		trace(L"dis X = %f", disX);
		trace(L"distanceX = %f", distanceX);
	}

	if (distanceY > 0 && this->getPositionY() + this->getHeight() < screenHeight)
	{
		// di chuyen xuong duoi
		double disY = screenHeight - (this->getPositionY() + this->getHeight());
		if (distanceY > disY)
			distanceY = disY;

		this->positionY += distanceY;
		
	}
	else if (distanceY < 0 && this->getPositionY() > 0)
	{
		// di chuyen len tren
		double disY = this->getPositionY();
		if (-distanceY > disY)
			distanceY = -disY;
			this->positionY += distanceY;
		
	}


	
}

void CRectangle::ScaleX(float scale)
{
	float x = float(scale / this->scaleX);
	this->width *= x;
	this->scaleX = x;
}

void CRectangle::ScaleY(float scale)
{
	float y = float(scale / this->scaleY);
	this->height *= y;
	this->scaleY = y;
}

void CRectangle::Scale(float scale)
{
	ScaleX(scale);
	ScaleY(scale);
}

float CRectangle::getScaleX()
{
	return this->scaleX;
}

float CRectangle::getScaleY()
{
	return this->scaleY;
}

void CRectangle::moveUp(float velocity)
{
	this->positionY -= velocity;
}

void CRectangle::moveDown(float velocity)
{
	this->positionY += velocity;
}


void CRectangle::moveNext(float velocity, int screenWidth, int screenHeight)
{
	// update position
	this->positionX += this->velocityX * velocity;
	this->positionY += this->velocityY * velocity;

	// kiem tra va cham voi canh man hinh
	if ((this->getPositionX() + this->getWidth()) >= screenWidth || this->getPositionX() <= 0)
	{
		// neu ma posX + width >= screen_width thi se quay lai --> velocityX = -velocityX
		this->velocityX = -this->velocityX;
	}
	if ((this->getPositionY() + this->getHeight()) >= screenHeight || this->getPositionY() <= 0)
	{
		// neu ma posY + height >= screen_height thi se quay lai --> velocityY = -velocityY
		this->velocityY = -this->velocityY;
	}
}

void CRectangle::moveNext(float velocity, int screenWidth, int screenHeight, int targetPosX, int targetPosY, int targetWidth, int targetHeight)
{
	// update position
	this->positionX += this->velocityX * velocity;
	this->positionY += this->velocityY * velocity;

	// kiem tra va cham voi canh man hinh
	if ((this->getPositionX() + this->getWidth()) >= screenWidth || this->getPositionX() <= 0)
	{
		// neu ma posX + width >= screen_width thi se quay lai --> velocityX = -velocityX

		// va cham canh trai + phai
		this->velocityX = -this->velocityX;
	}
	if ((this->getPositionY() + this->getHeight()) >= screenHeight || this->getPositionY() <= 0)
	{
		// neu ma posY + height >= screen_height thi se quay lai --> velocityY = -velocityY

		// va cham canh tren + duoi
		this->velocityY = -this->velocityY;
	}
	if (this->getPositionX() <= targetPosX + targetWidth &&
		(  (this->getPositionY() + this->getHeight() /2 ) >= targetPosY) &&
		(this->getPositionY() - this->getHeight() / 2) <= targetPosY + targetHeight)
	{
		// trung cai racket ben trai
		this->velocityX = -this->velocityX;

		trace(L"----Va cham------");
	}
}
