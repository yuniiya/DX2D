#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class GameEngineCollision;
class Skill : public GameEngineActor
{
public:
	// constrcuter destructer
	Skill();
	~Skill();

	// delete Function
	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;

	inline GameEngineTextureRenderer* GetJiARenderer()
	{
		return JiA_Renderer_;
	}

	inline GameEngineTextureRenderer* GetJiBRenderer()
	{
		return JiB_Renderer_;
	}

	inline GameEngineTextureRenderer* GetJiCRenderer()
	{
		return JiC_Renderer_;
	}

	inline GameEngineCollision* GetCollision()
	{
		return JiSkillCollision_;
	}

	bool IsEnd_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void JiCFrameEnd(const FrameAnimation_DESC& _Info);
	void SkillEnd(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* JiA_Renderer_;
	GameEngineTextureRenderer* JiB_Renderer_;
	GameEngineTextureRenderer* JiC_Renderer_;

	GameEngineCollision* JiSkillCollision_;
};

