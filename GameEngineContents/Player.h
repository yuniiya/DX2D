#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GlobalActor.h"

class GameEngineTextureRenderer;
class GlobalLevel;
class Skill;
class Boss;
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

	void TakeDamage(float _Damage);
	
	inline float GetPlayerLevel()
	{
		return CurLevel_;
	}

	inline float GetHP()
	{
		return CurHP_;
	}

	inline float GetMP()
	{
		return CurMP_;
	}

	inline float GetExp()
	{
		return CurExp_;
	}

	inline float GetMaxHP()
	{
		return MaxHP_;
	}

	inline float GetMaxMP()
	{
		return MaxMP_;
	}

	inline float GetMaxExp()
	{
		return MaxExp_;
	}

	inline void UseMP(float _MP)
	{
		CurMP_ = CurMP_ - _MP;
	}

	inline void AddHP(float _HP)
	{
		if (CurHP_ + _HP >= MaxHP_)
		{
			CurHP_ = 100.f;
			return;
		}
		CurHP_ = CurHP_ + _HP;
	}

	inline void AddMP(float _MP)
	{
		if (CurMP_ + _MP >= MaxMP_)
		{
			CurMP_ = 100.f;
			return;
		}
		CurMP_ = CurMP_ + _MP;
	}

	inline void AddExp(float _Exp)
	{
		CurExp_ = CurExp_ + _Exp;
	}

	inline float GetAtk()
	{
		return Atk_;
	}

	inline int GetPlayerMeso()
	{
		return CurMeso_;
	}

	inline void AddPlayerMeso(int _Meso)
	{
		CurMeso_ = CurMeso_+ _Meso;
	}

	inline void UsePlayerMeso(int _Meso)
	{
		CurMeso_ = CurMeso_ - _Meso;
	}

	bool IsCactusQuestOngoing_;
	bool IsEntranceQuestClear_;
	bool IsCactusQuestClear_;
	bool IsCastleQuestClear_;
	bool IsCactusQuestEnd_;
	bool IsChase_;
	bool IsBlueHat_;
	bool IsRedHat_;


private:
	float CurLevel_;
	float CurHP_;
	float CurMP_;
	float CurExp_;
	float MaxHP_;
	float MaxMP_;
	float MaxExp_;

	float Atk_;
	float Speed_;
	int CurMeso_;

	float4 JumpPower_;
	float4 DownPower_;
	float4 Position_;
	float4 PrevPosition_;

	float4 MoveDir_;

	bool IsDebug;
	bool IsGround;
	bool CanMove;
	bool IsHit;
	bool IsUsePaSkill;
	bool IsUseSinSkill;
	bool SinAttackEnd;
	bool IsSinLoopStart;
	bool IsSinLoopEnd;
	bool IsLevelUp;

	bool IsInvincible_;
	bool IsMoveKeyChange_;
	bool IsStun_; 
	bool IsSkillLock_;

	std::string CurLevelName_;

	PLAYERSTATE CurState_;
	PLAYERSKILL CurSkill_;

	ACTORDIR CurDir_;
	ACTORDIR PrevDir_;

	Skill* Skill_;
	Boss* Boss_;

private:
	int SinSkillAttCount_;
	int SinSkillFrameCount_;

	float Time_;
	float DamageTime_;
	float SinLoopTime_;
	float SinEndTime_;
	float DoubleJumpTime_;
	float MoveKeyChaneTime_;
	float StunTime_;
	float SkillLockTime_;

protected:
	float4 BottomColor;
	float4 JumpHighColor;
	float4 BottomDownColor;
	float4 TopColor;
	float4 MiddleColor;
	float4 BottomUpColor;
	float4 LeftColor;
	float4 RightColor;
	float4 LeftLeftColor;
	float4 RightRightColor;

private:
	GameEngineCollision* PlayerCollision_;
	GameEngineCollision* LevelUpCollision_;

	GameEngineCollision* InSkillCollision_;
	GameEngineCollision* PaSkillCollision_;
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
	GameEngineTextureRenderer* LevelUpEffRenderer_;

	GameEngineTexture* MapTexture_;
	GameEngineStateManager StateManager;

private:
	GameEngineTextureRenderer* InA_Renderer_;
	GameEngineTextureRenderer* InB_Renderer_;
	GameEngineTextureRenderer* InHit_Renderer_;

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

	GameEngineTextureRenderer* StunRenderer_;
	GameEngineTextureRenderer* HatChaseRenderer_;
	GameEngineTextureRenderer* SkillLockRenderer_;
	GameEngineTextureRenderer* RedHatRenderer_;
	GameEngineTextureRenderer* BlueHatRenderer_;
	GameEngineTextureRenderer* MissRenderer_;


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

	void LevelUpUpdate();

protected:
	void SkillEnd(const FrameAnimation_DESC& _Info);
	void SkillPositionUpdate(PLAYERSKILL _CurSkill);
	void SinSkillUpdate(const FrameAnimation_DESC& _Info);
	void SinSkillSoundUpdate(const FrameAnimation_DESC& _Info);
	void DoubleJumpEnd(const FrameAnimation_DESC& _Info);
	void LevelUpEffectEnd(const FrameAnimation_DESC& _Info);
	void LevelUpCollisionStart(const FrameAnimation_DESC& _Info);


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
	void JumpSkillAttackStart(const StateInfo& _Info);
	void DoubleJumpStart(const StateInfo& _Info);
	void DamagedStart(const StateInfo& _Info);
	void KnockBackStart(const StateInfo& _Info);
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
	void JumpSkillAttackUpdate(float _DeltaTime, const StateInfo& _Info);
	void DoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void DamagedUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnockBackUpdate(float _DeltaTime, const StateInfo& _Info);
	void DieUpdate(float _DeltaTime, const StateInfo& _Info);
};

