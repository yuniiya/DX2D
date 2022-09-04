#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

class GameEngineCollision;
class Mouse : public GameEngineActor
{
public:
	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

	void GetCurPos();

	inline float4 ReturnPos()
	{
		return CurPos_;
	}

	inline GameEngineCollision* GetMouseCol()
	{
		return MouseCol_;
	}

	inline GameEngineUIRenderer* GetMouseRenderer()
	{
		return MouseRenderer_;
	}

	inline GameEngineUIRenderer* GetMouseAnimationRenderer()
	{
		return MouseAnimationRenderer_;
	}

protected:
	bool MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	void CollisionCheck();

private:
	bool ClickSoundOn_;
	bool MouseOverSoundOn_;
	GameEngineCollision* MouseCol_;
	//GameEngineTextureRenderer* MouseRenderer_;
	//GameEngineTextureRenderer* MouseAnimationRenderer_;

	GameEngineUIRenderer* MouseRenderer_;
	GameEngineUIRenderer* MouseAnimationRenderer_;


	float4 CurPos_;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

};

