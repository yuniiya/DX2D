#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

GameEngineLevel* GameEngineCore::CurrentLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevels;


GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

class GameEngineLevel* GameEngineCore::FindLevel(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevels.find(UpperName);
	if (FindIter == AllLevels.end())
	{
		return nullptr;
	}
	return FindIter->second;
}

bool GameEngineCore::ChangeLevel(const std::string& _Name)
{
	NextLevel = FindLevel(_Name);

	if (nullptr == NextLevel)
	{
		MsgBoxAssert("존재하지 않는 레벨로 바꾸려고 했습니다.");
		return false;
	}

	return true;
}

void GameEngineCore::CoreStart(GameEngineCore* _UserCore)
{
	// 엔진이 뭔가를 할겁니다.
	// 준비를 먼저하고.
	_UserCore->UserStart();
}

void GameEngineCore::CoreUpdate(GameEngineCore* _UserCore)
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurrentLevel)
		{
			CurrentLevel->OffEvent();
		}

		CurrentLevel = NextLevel;
		NextLevel = nullptr;

		CurrentLevel->OnEvent();
	}


	if (nullptr == CurrentLevel)
	{
		MsgBoxAssert("레벨을 지정해주지 않으면 엔진을 시작할수가 업습니다.");
	}

	GameEngineTime::GetInst()->Update();

	_UserCore->UserUpdate();

	// 현재 레벨이 몇 초 동안 실행됐는지 시간 재기 위해 여기에 둔다
	CurrentLevel->AddAccTime(GameEngineTime::GetDeltaTime());
	CurrentLevel->UserUpdate();
}

void GameEngineCore::CoreEnd(GameEngineCore* _UserCore)
{
	_UserCore->UserEnd();

	for (auto& Level : AllLevels)
	{
		if (nullptr == Level.second)
		{
			continue;
		}
		delete Level.second;
		Level.second = nullptr;
	}

	// 싱글톤으로 만든 엔진의 메모리 해제는 여기서 
	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();

}


void GameEngineCore::WindowCreate(const std::string& _Name, GameEngineCore* _UserCore)
{
	GameEngineWindow::GetInst()->CreateGameWindow(nullptr, _Name.c_str());
	GameEngineWindow::GetInst()->SetWindowScaleAndPosition({ 0,0 }, { 1280, 720 });
	GameEngineWindow::GetInst()->ShowGameWindow();
	GameEngineWindow::GetInst()->MessageLoop(
		std::bind(&GameEngineCore::CoreStart, _UserCore),
		std::bind(&GameEngineCore::CoreUpdate, _UserCore),
		std::bind(&GameEngineCore::CoreEnd, _UserCore)
	);
}

void GameEngineCore::InitializeLevel(GameEngineLevel* _Level, const std::string _Name)
{
	_Level->UserStart();
	_Level->SetName(_Name);

	// AllLevels.insert(std::map<std::string, GameEngineLevel*>::value_type(_Name, NewLevel));
	AllLevels.insert(std::make_pair(_Name, _Level));
}