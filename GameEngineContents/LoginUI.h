#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Mouse;
class TextArea;
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

public:
	void ResetLoginUI();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	bool MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	void CollisionCheck();

	bool SoundPlay;

private:
	GameEngineTextureRenderer* LoginBackUI_;
	GameEngineTextureRenderer* LoginUI_;
	GameEngineTextureRenderer* LogoUI_;
	GameEngineTextureRenderer* MapleID_;
	GameEngineTextureRenderer* IDArea_;
	GameEngineTextureRenderer* PWArea;
	GameEngineUIRenderer* Notice0_;
	GameEngineUIRenderer* Notice1_;

	GameEngineCollision* LoginCol_;
	GameEngineCollision* IDAreaCol_;
	GameEngineCollision* PWAreaCol_;

	TextArea* IDText_;
	TextArea* PWText_;

	bool IsCorrectID_;
	bool IsCorrectPW_;

	bool IsNoticeEnd0_;
	bool IsNoticeEnd1_;

	bool IsChageLevel_;

	std::string UserID_;
	std::string UserPW_;

	float Time_;
};

