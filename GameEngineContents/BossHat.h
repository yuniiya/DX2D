#pragma once
#include "GlobalActor.h"

enum class BossHatState
{
	Fall,
	Ground,
	Idle,
	End,
	
	Max,
};

class GameEngineTextureRenderer;
class BossHat : public GlobalActor
{
public:
	// constrcuter destructer
	BossHat();
	~BossHat();

	// delete Function
	BossHat(const BossHat& _Other) = delete;
	BossHat(BossHat&& _Other) noexcept = delete;
	BossHat& operator=(const BossHat& _Other) = delete;
	BossHat& operator=(BossHat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	GameEngineTexture* GetCurMapTexture();
	void ChangeState(BossHatState _State);
	void StateUpdate();
	void CollisionCheck();
	bool StagePixelCheck();

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* HitRenderer_;
	GameEngineTexture* MapTexture_;

	GameEngineCollision* Collision_;
	BossHatState CurState_;

	void FallStart();
	void GroundStart();
	void IdleStart();
	void EndStart();

	void FallUpdate();
	void GroundUpdate();
	void IdleUpdate();
	void EndUpdate();

	void BindFallEnd(const FrameAnimation_DESC& _Info);
	void BindGroundEnd(const FrameAnimation_DESC& _Info);
	void BindIdleEnd(const FrameAnimation_DESC& _Info);
	void BindEndEnd(const FrameAnimation_DESC& _Info);
	void BindHitEnd(const FrameAnimation_DESC& _Info);

private:
	bool IsGround_;
	std::string CurLevelName_;
};

