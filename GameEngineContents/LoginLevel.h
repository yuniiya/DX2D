#pragma once
#include "GlobalLevel.h"

// Ό³Έν :
class LoginLevel : public GlobalLevel
{
public:
	// constrcuter destructer
	LoginLevel();
	~LoginLevel();

	// delete Function
	LoginLevel(const LoginLevel& _Other) = delete;
	LoginLevel(LoginLevel&& _Other) noexcept = delete;
	LoginLevel& operator=(const LoginLevel& _Other) = delete;
	LoginLevel& operator=(LoginLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void GetCameraPos()
	{
		CurPos_.x = GetMainCameraActorTransform().GetLocalPosition().x;
		CurPos_.y = GetMainCameraActorTransform().GetLocalPosition().y;
	}

	void LevelStartEvent() override;

private:
	float4 CurPos_;
};

