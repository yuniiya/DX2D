#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>

// 설명 :
class GameEngineLevel :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend class GameEngineCore;
	// 레벨이 현재까지 얼마나 켜져있었는지 시간을 잴수 있게 한다.

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;		// 최상위 부모 클래스이기 때문에 소멸자를 가상함수로 만듦

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void UserStart() = 0;
	virtual void UserUpdate() = 0;
	virtual void UserEnd() = 0;

	//virtual void OnEvent() override;
	//virtual void OffEvent() override;

private:

};

