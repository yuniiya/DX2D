#pragma once
#include "MapObject.h"

// Ό³Έν :
class MapAnimationObject : public MapObject
{
public:
	// constrcuter destructer
	MapAnimationObject();
	~MapAnimationObject();

	// delete Function
	MapAnimationObject(const MapAnimationObject& _Other) = delete;
	MapAnimationObject(MapAnimationObject&& _Other) noexcept = delete;
	MapAnimationObject& operator=(const MapAnimationObject& _Other) = delete;
	MapAnimationObject& operator=(MapAnimationObject&& _Other) noexcept = delete;

public:
	void CreateAnimation(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float4 _Pos, float4 _Scale);

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void End() override {};


private:

};

