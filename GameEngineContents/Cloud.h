#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class Cloud : public GameEngineActor
{
public:
	// constrcuter destructer
	Cloud();
	~Cloud();

	// delete Function
	Cloud(const Cloud& _Other) = delete;
	Cloud(Cloud&& _Other) noexcept = delete;
	Cloud& operator=(const Cloud& _Other) = delete;
	Cloud& operator=(Cloud&& _Other) noexcept = delete;

public:
	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	void CreateCloud(const std::string _Name, float4 _Pos, float _Speed, bool _IsPluseMove);

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer_;

	float Time_;
	float Speed_;
	bool IsPlusMove_;
};

