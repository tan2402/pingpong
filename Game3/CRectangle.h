#pragma once
#include "windows.h"
class CRectangle
{
private:
	double height;
	double width;

	double positionX;
	double positionY;

	float scaleX = 1.0f;
	float scaleY = 1.0f;

	float velocityX = 1.0f;
	float velocityY = 1.0f;

public:
	CRectangle();
	CRectangle(double width, double height);
	CRectangle(double posX, double posY, double width, double height);
	~CRectangle();

	void setPosition(double x, double y);
	void setPositionX(double x);
	void setPositionY(double y);
	double getPositionX();
	double getPositionY();

	void setVelocityX(float Vx);
	void setVelocityY(float Vy);
	float getVelocityX();
	float getVelocityY();


	double getWidth();
	double getHeight();
	void setWidth(double width);
	void setHeight(double height);

	void MoveTo(double x, double y);
	void MoveBy(double distanceX, double distanceY, int screenWidth, int screenHeight);
	void moveNext(float velocity, int screenWidth, int screenHeight);
	void moveNext(float velocity, int screenWidth, int screenHeight, int targetPosX, int targetPosY, int targetWidth, int targetHeight);

	void ScaleX(float scale);
	void ScaleY(float scale);
	void Scale(float scale);
	float getScaleX();
	float getScaleY();

	void moveUp(float velocity);
	void moveDown(float velocity);

};
