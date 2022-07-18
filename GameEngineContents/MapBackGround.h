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

private:
	void Start();
	void Render();
	void Update();

	GameEngineTextureRenderer* MapBackGroundRender_;

public:
	GameEngineTextureRenderer* GetRenderer()
	{
		return	MapBackGroundRender_;
	}
};

