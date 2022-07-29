#pragma once
#include "GameEngineCore/CoreMinimal.h"

class GameEngineCollision;
class Portal : public GameEngineActor
{
public:
	// constrcuter destructer
	Portal();
	~Portal();

	// delete Function
	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

public:
	GameEngineTextureRenderer* GetPortalRenderer()
	{
		return PortalRenderer_;
	}

private:
	GameEngineTextureRenderer* PortalRenderer_;
	GameEngineCollision* PortalCollision_;

};

