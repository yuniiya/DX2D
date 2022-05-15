#pragma once
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

// 설명 :
class GameEngineCore
{
public:
	template<typename CoreType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		// 여기에서 만들어진 이 코어를 알아야 하는거지.
		CoreType Core;
		WindowCreate(Core.GetWindowTitle(), &Core);
	}


protected:
	virtual std::string GetWindowTitle() { return "MainWindow"; }


	virtual void UserGameStart() = 0;
	virtual void UserGameUpdate() = 0;
	virtual void UserGameEnd() = 0;

	GameEngineCore();
	~GameEngineCore();

	template<typename LevelType>
	void LevelCreate(const std::string& _Name) 
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	}





private:
	static void WindowCreate(const std::string& _Name, GameEngineCore* _UserCore);
	static void CoreStart(GameEngineCore* _UserCore); // 프로그램 시작
	static void CoreUpdate(GameEngineCore* _UserCore); // 프로그램 업데이트
	static void CoreEnd(GameEngineCore* _UserCore); // 프로그램 업데이트

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;


};

