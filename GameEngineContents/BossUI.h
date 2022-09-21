#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
class Boss;
class BossUI : public GameEngineActor
{
public:
	// constrcuter destructer
	BossUI();
	~BossUI();

	// delete Function
	BossUI(const BossUI& _Other) = delete;
	BossUI(BossUI&& _Other) noexcept = delete;
	BossUI& operator=(const BossUI& _Other) = delete;
	BossUI& operator=(BossUI&& _Other) noexcept = delete;

public:
	inline void SetBoss(Boss* _Boss)
	{
		Boss_ = _Boss;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineUIRenderer* HPBack_;
	GameEngineUIRenderer* HPBar_;

	Boss* Boss_;

	float4 HPBarScale_;
	float BossHP_;
	float BossMaxHP_;

};

