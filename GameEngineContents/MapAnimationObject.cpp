#include "PreCompile.h"
#include "MapAnimationObject.h"

MapAnimationObject::MapAnimationObject() 
{
}

MapAnimationObject::~MapAnimationObject() 
{
}


void MapAnimationObject::CreateAnimation(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float4 _Pos, float4 _Scale)
{
	AnimationRenderer_->CreateFrameAnimationFolder(_Name, FrameAnimation_DESC(_FolderName, _PlaySpeed));
	AnimationRenderer_->GetTransform().SetLocalPosition(_Pos);
	AnimationRenderer_->GetTransform().SetLocalScale(_Scale);
	AnimationRenderer_->ChangeFrameAnimation(_Name);
}

void MapAnimationObject::Start()
{
	MapObject::Start();
}

void MapAnimationObject::Update(float _DeltaTime)
{
}
