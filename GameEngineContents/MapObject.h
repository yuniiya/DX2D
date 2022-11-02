#pragma once
//#include <GameEngineCore/GameEngineActor.h>
#include "GlobalActor.h"

class GameEngineTextureRenderer;
class MapObject : public GlobalActor
{
public:
	// constrcuter destructer
	MapObject();
	~MapObject();

	// delete Function
	MapObject(const MapObject& _Other) = delete;
	MapObject(MapObject&& _Other) noexcept = delete;
	MapObject& operator=(const MapObject& _Other) = delete;
	MapObject& operator=(MapObject&& _Other) noexcept = delete;

public:
	inline GameEngineTextureRenderer* GetAnimationRenderer()
	{
		return AnimationRenderer_;
	}

	inline GameEngineTextureRenderer* GetXMoveRenderer()
	{
		return XMoveRenderer_;
	}

	inline void GetWindowScale()
	{
	//	WindowScale_ = GameEngineWindow::GetScale();
		WindowScale_ = { 1614.f, 1380.f };
	}

	void CreateXMoveAnimaition(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float _MoveSpeed_, float4 _Pos, float4 _Scale, ACTORDIR _Dir);
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void End() override {};

	GameEngineTextureRenderer* AnimationRenderer_;
private:

	GameEngineTextureRenderer* XMoveRenderer_;
	 
	float Time_;
	float MoveSpeed_;
	float4 TextureScale_;
	float4 WindowScale_;
	float4 TexturePos_;

	ACTORDIR CurDir_;
};

