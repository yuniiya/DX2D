#pragma once
#include "GameEngineCore/GameEngineLevel.h"

class MapBackGround;
class GameEngineTextureRenderer;
class GlobalLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	GlobalLevel();
	~GlobalLevel();

	// delete Function
	GlobalLevel(const GlobalLevel& _Other) = delete;
	GlobalLevel(GlobalLevel&& _Other) noexcept = delete;
	GlobalLevel& operator=(const GlobalLevel& _Other) = delete;
	GlobalLevel& operator=(GlobalLevel&& _Other) noexcept = delete;

protected:
	void Start() override {};
	void Update(float _DeltaTime) override {};;
	void End() override {};

private:
	MapBackGround* BackGround_;

	GameEngineTextureRenderer* BackGroundRenderer_;

protected:
	void SetCamera();
	void SetBackGround(const std::string& _Name);

};

