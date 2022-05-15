#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineWindow.h>

#pragma comment(lib, "GameEngineBase.lib")

GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

// MessageLoop에서 _UserCore의 포인터를 넣어서 실행시켰고, 해당 포인터는 여기서 다시 사용된다 
// 따라서 _UserCore내부의 함수를 호출할 수 있다  
void GameEngineCore::CoreStart(GameEngineCore* _UserCore)
{
	_UserCore->UserGameStart();
}

void GameEngineCore::CoreUpdate(GameEngineCore* _UserCore)
{
	_UserCore->UserGameUpdate();
}

void GameEngineCore::CoreEnd(GameEngineCore* _UserCore) 
{
	_UserCore->UserGameEnd();
}


void GameEngineCore::WindowCreate(const std::string& _Name, GameEngineCore* _UserCore)
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, _Name.c_str());
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 0,0 }, {1024, 768});
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(
		std::bind(&GameEngineCore::CoreStart, _UserCore),
		std::bind(&GameEngineCore::CoreUpdate, _UserCore),
		std::bind(&GameEngineCore::CoreEnd, _UserCore)
		// funtion이기 때문에 Loop안에서 _UserCore의 포인터를 기억하고 있는다 
	);
}