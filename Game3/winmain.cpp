#include <windows.h>
#include "ball.h"
#include "GameScene.h"

#define GAME_NAME "Ping Pong"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameScene rec(hInstance, GAME_NAME, GAME_SCREEN_RESOLUTION_800_600_24, 0, 24);

	rec.Init();
	rec.Run();


	return 0;
}