#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class MapBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	MapBackGround();
	~MapBackGround();

	// delete Function
	MapBackGround(const MapBackGround& _Other) = delete;
	MapBackGround(MapBackGround&& _Other) noexcept = delete;
	MapBackGround& operator=(const MapBackGround& _Other) = delete;
	MapBackGround& operator=(MapBackGround&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void End() override {};

private:

	GameEngineTextureRenderer* MapBackGroundRender_;
	GameEngineTextureRenderer* AriantSunLight_;
	GameEngineTextureRenderer* AriantCloud_;

public:
	inline GameEngineTextureRenderer* GetRenderer()
	{
		return	MapBackGroundRender_;
	}

	inline GameEngineTextureRenderer* GetSunLightRenderer()
	{
		return AriantSunLight_;
	}

	inline GameEngineTextureRenderer* GetAriantCloudRenderer()
	{
		return AriantCloud_;
	}
	inline void SetSunShineYPos(float _YPos)
	{
		SunShineYPos_ = _YPos;
	}

private:
	float SunShineYPos_;
	float Time_;
};

