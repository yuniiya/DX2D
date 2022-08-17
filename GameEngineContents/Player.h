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

	inline std::string GetCurLevelName()
	{
		return CurLevelName_ = GetLevel()->GetNameCopy();
	}

	GameEngineTexture* GetCurMapTexture();

	void TakeDamage(int _Damage);
	
	inline int GetHP()
	{
		return CurHP_;
	}

	inline int GetMP()
	{
		return CurMP_;
	}

	inline int GetExp()
	{
		return CurExp_;
	}

	inline void UseMP(int _CurMP)
	{
		CurMP_ = CurHP_ - _CurMP;
	}

	inline void AddExp(int _CurExp)
	{
		CurExp_ = CurExp_ + _CurExp;
	}

	inline float GetAtk()
	{
		return Atk_;
	}

private:
	float CurHP_;
	float CurMP_;
	float CurExp_;
	float MaxHP_;
	float MaxMP_;
	float MaxExp_;

	float Atk_;
	float Speed_;

	float4 JumpPower_;
	float4 DownPower_;
	float4 Position_;
	float4 PrevPosition_;

	bool IsDebug;
	bool IsGround;
	bool CanMove;
	bool IsHit;
	bool IsUsePaSkill;
	bool IsUseSinSkill;
	bool SinAttackEnd;
	bool IsSinLoopStart;
	bool IsSinLoopEnd;

	std::string CurLevelName_;

	PLAYERSTATE CurState_;
	PLAYERSKILL CurSkill_;

	ACTORDIR CurDir_;
	ACTORDIR PrevDir_;

private:
	int SinSkillAttCount_;
	int SinSkillFrameCount_;

	float Time_;
	float DamageTime_;
	float SinLoopTime_;
	float SinEndTime_;
	float DoubleJumpTime_;

protected:
	float4 BottomColor;
	float4 JumpHighColor;
	float4 BottomDownColor;
	float4 TopColor;
	float4 MiddleColor;
	float4 BottomUpColor;

private:
	GameEngineCollision* PlayerCollision_;

	GameEngineCollision* InSkillCollision_;
	GameEngineCollision* PaSkillCollision_;
	GameEngineCollision* JiSkillCollision_;
	GameEngineCollision* SinACollision_;
	GameEngineCollision* SinBCollision_;
	GameEngineCollision* SinCCollision_;
	GameEngineCollision* SinDCollision_;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

protected:
	void DebugModeOnOff();
	void DebugRender();

private:
	GameEngineTextureRenderer* PlayerRenderer_;
	GameEngineTextureRenderer* ColMapRenderer_;

	GameEngineTexture* MapTexture_;
	GameEngineStateManager StateManager;

private:
	GameEngineTextureRenderer* InA_Renderer_;
	GameEngineTextureRenderer* InB_Renderer_;
	GameEngineTextureRenderer* InHit_Renderer_;

	GameEngineTextureRenderer* JiA_Renderer_;
	GameEngineTextureRenderer* JiB_Renderer_;
	GameEngineTextureRenderer* JiC_Renderer_;
	GameEngineTextureRenderer* JiHit_Renderer_;

	GameEngineTextureRenderer* PaA_Renderer_;
	GameEngineTextureRenderer* PaHit_Renderer_;

	GameEngineTextureRenderer* SinStart_Renderer_;
	GameEngineTextureRenderer* SinA_Renderer_;
	GameEngineTextureRenderer* SinAHit_Renderer_;
	GameEngineTextureRenderer* SinB_Renderer_;
	GameEngineTextureRenderer* SinBHit_Renderer_;
	GameEngineTextureRenderer* SinC_Renderer_;
	GameEngineTextureRenderer* SinCHit_Renderer_;
	GameEngineTextureRenderer* SinD_Renderer_;
	GameEngineTextureRenderer* SinDHit_Renderer_;

	GameEngineTextureRenderer* ChoA_Renderer_;
	GameEngineTextureRenderer* ChoB_Renderer_;

protected:
	bool StagePixelCheck();
	void ObjectPixelCheck();
	void CollisionCheck();

protected:
	bool IsMoveKey();
	bool IsUpDownMoveKey();
	bool IsSkillKey();

	void PlayerMove(float _DeltaTime);
	
	void UseSkill();
	void SkillSinLoop();

protected:
	void SkillEnd(const FrameAnimation_DESC& _Info);
	void SkillPositionUpdate(PLAYERSKILL _CurSkill);
	void JiCFrameEnd(const FrameAnimation_DESC& _Info);
	void SinSkillUpdate(const FrameAnimation_DESC& _Info);
	void SinSkillSoundUpdate(const FrameAnimation_DESC& _Info);
	void DoubleJumpEnd(const FrameAnimation_DESC& _Info);


protected:
	void IdleStart(const StateInfo& _Info);
	void MoveStart(const StateInfo& _Info);
	void JumpStart(const StateInfo& _Info);
	void FallStart(const StateInfo& _Info);
	void ProneStart(const StateInfo& _Info);
	void ProneStabStart(const StateInfo& _Info);
	void LadderStart(const StateInfo& _Info);
	void RopeStart(const StateInfo& _Info);
	void DefaultAttackStart(const StateInfo& _Info);
	void SkillAttackStart(const StateInfo& _Info);
	void DoubleJumpStart(const StateInfo& _Info);
	void DamagedStart(const StateInfo& _Info);
	void DieStart(const StateInfo& _Info);

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void FallUpdate(float _DeltaTime, const StateInfo& _Info);
	void ProneUpdate(float _DeltaTime, const StateInfo& _Info);
	void ProneStabUpdate(float _DeltaTime, const StateInfo& _Info);
	void LadderUpdate(float _DeltaTime, const StateInfo& _Info);
	void RopeUpdate(float _DeltaTime, const StateInfo& _Info);
	void DefaultAttackUpdate(float _DeltaTime, const StateInfo& _Info);
	void SkillAttackUpdate(float _DeltaTime, const StateInfo& _Info);
	void DoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void DamagedUpdate(float _DeltaTime, const StateInfo& _Info);
	void DieUpdate(float _DeltaTime, const StateInfo& _Info);
};

