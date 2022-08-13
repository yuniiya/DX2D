#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ContentsUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsUI();
	~ContentsUI();

	// delete Function
	ContentsUI(const ContentsUI& _Other) = delete;
	ContentsUI(ContentsUI&& _Other) noexcept = delete;
	ContentsUI& operator=(const ContentsUI& _Other) = delete;
	ContentsUI& operator=(ContentsUI&& _Other) noexcept = delete;

protected:
	bool MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	void CollisionCheck();

	void MainBarSizeUpdate();

	float4 HpPos_;
	float4 MpPos_;
	float4 ExpPos_;

	int CurHP_;
	int CurMP_;
	int CurExp_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* MainBar_;
	GameEngineTextureRenderer* ExpBack_;
	GameEngineTextureRenderer* QuickSlotBack_;
	GameEngineTextureRenderer* QuickSlot_;

	GameEngineTextureRenderer* HpBar_;
	GameEngineTextureRenderer* MpBar_;
	GameEngineTextureRenderer* ExpBar_;
};

