#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class MapObject : public GameEngineActor
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

	inline GameEngineTextureRenderer* GetUVMoveRenderer()
	{
		return UVMoveRenderer_;
	}

	inline void GetWindowScale()
	{
		WindowScale_ = GameEngineWindow::GetScale();
	}

	void CreateAnimation(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float4 _Pos, float4 _Scale);
	void CreateXMoveAnimaition(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float _MoveSpeed_, float4 _Pos, float4 _Scale, ACTORDIR _Dir);
	void CreateUVMoveTexture(const std::string _Name, float4 _Pos, float _UVSpeed);
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* AnimationRenderer_;
	GameEngineTextureRenderer* XMoveRenderer_;
	GameEngineTextureRenderer* UVMoveRenderer_;
	 
	float Time_;
	float UVSpeed_;
	float MoveSpeed_;
	float XPos_;
	float4 TextureScale_;
	float4 WindowScale_;

	ACTORDIR CurDir_;
};

