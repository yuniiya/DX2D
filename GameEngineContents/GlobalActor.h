#pragma once
#include "GameEngineCore/GameEngineActor.h"
#include "Enums.h"

class GameEngineCollision;
class GlobalActor : public GameEngineActor
{
public:
	// constrcuter destructer
	GlobalActor();
	~GlobalActor();

	// delete Function
	GlobalActor(const GlobalActor& _Other) = delete;
	GlobalActor(GlobalActor&& _Other) noexcept = delete;
	GlobalActor& operator=(const GlobalActor& _Other) = delete;
	GlobalActor& operator=(GlobalActor&& _Other) noexcept = delete;

protected:
	void Start() override {};
	void Update(float _DeltaTime) override;
	void End() override {};

protected:
	virtual bool PixelCollisionMapUpdate(GlobalActor* _Actor, int _LeftRightPos, int _BottomPos);
	void DirCheck(GameEngineTextureRenderer* _Renderer, ACTORDIR _Dir);

	inline void SetDir(ACTORDIR _Dir)
	{
		CurDir_ = _Dir;
	}

	inline ACTORDIR GetDir()
	{
		return CurDir_;
	}
	

protected:
	float4 DownPower_;
	ACTORDIR CurDir_;

	GameEngineTexture* MapTexture_;
private:

};

