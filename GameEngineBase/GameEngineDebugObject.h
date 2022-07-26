#pragma once

// Ό³Έν :
class GameEngineDebugObject
{
public:
	// constrcuter destructer
	GameEngineDebugObject();
	~GameEngineDebugObject();

	// delete Function
	GameEngineDebugObject(const GameEngineDebugObject& _Other) = delete;
	GameEngineDebugObject(GameEngineDebugObject&& _Other) noexcept = delete;
	GameEngineDebugObject& operator=(const GameEngineDebugObject& _Other) = delete;
	GameEngineDebugObject& operator=(GameEngineDebugObject&& _Other) noexcept = delete;


	inline void DebugOn()
	{
		IsDebug_ = true;
	}

	inline void DebugOff()
	{
		IsDebug_ = false;
	}

	inline bool IsDebug()
	{
		return IsDebug_;
	}

	static void IsDebugModeSwitch()
	{
		IsDebug_ = !IsDebug_;
	}


protected:

private:
	static bool IsDebug_;

};

