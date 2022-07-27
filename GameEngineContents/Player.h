#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GlobalActor.h"

class GameEngineTextureRenderer;
class GlobalLevel;
class Player : public GlobalActor
{
public:
	static Player* MainPlayer_;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

public:
	inline float4 GetPosition()
	{
		Position_ = MainPlayer_->GetTransform().GetLocalPosition();
		return Position_;
	}

private:
	float Speed_;
	float4 Position_;

	PLAYERSTATE CurState_;
	ACTORDIR CurDir_;
	bool IsDebug;
	bool IsLeftMove;
	bool IsRightMove;
	bool IsGround;
	bool CanMove;

private:
	GameEngineCollision* PlayerCollision_;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End()  {}

	void DebugModeOnOff();
	void DebugRender();
protected:
	GameEngineTextureRenderer* PlayerRenderer_;
	GameEngineTextureRenderer* ColMapRenderer_;
	std::string AnimationName_;


protected:
	bool StagePixelCheck();
	void PixelColiisionCheck();
	void ColiisionCheck();

protected:
	void ChangeState(PLAYERSTATE _State);
	void PlayerStateUpdate();
	bool IsMoveKey();
	void PlayerMove(float _DeltaTime);

protected:
	void IdleStart();
	void MoveStart();
	void JumpStart();
	void ProneStart();
	void ProneStabStart();
	void LadderStart();
	void RopeStart();
	void AttackStart();
	void DamagedStart();
	void DieStart();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void ProneUpdate();
	void ProneStabUpdate();
	void LadderUpdate();
	void RopeUpdate();
	void AttackUpdate();
	void DamagedUpdate();
	void DieUpdate();
};

