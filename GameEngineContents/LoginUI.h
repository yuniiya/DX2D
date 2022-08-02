#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Mouse;
class LoginUI : public GameEngineActor
{
public:
	// constrcuter destructer
	LoginUI();
	~LoginUI();

	// delete Function
	LoginUI(const LoginUI& _Other) = delete;
	LoginUI(LoginUI&& _Other) noexcept = delete;
	LoginUI& operator=(const LoginUI& _Other) = delete;
	LoginUI& operator=(LoginUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	bool MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	void CollisionCheck();

	bool SoundPlay;
	bool AlreadyPlay;

private:
	GameEngineTextureRenderer* LoginBackUI_;
	GameEngineTextureRenderer* LoginUI_;
	GameEngineTextureRenderer* LogoUI_;

	GameEngineCollision* LoginCol_;
};

