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

	inline GameEngineTextureRenderer* GetUVMoveRenderer()
	{
		return UVMoveRenderer_;
	}

	void CreateAnimation(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float4 _Pos, float4 _Scale);
	void CreateFish(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float _Speed, float4 _Pos, float4 _Scale);
	void CreateTexture(const std::string _Name, float4 _Pos, float _Speed, bool _IsPluseMove);
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* AnimationRenderer_;
	GameEngineTextureRenderer* UVMoveRenderer_;
	 
	float Time_;
	float Speed_;
	float XPos_;
};

