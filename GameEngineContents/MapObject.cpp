#include "PreCompile.h"
#include "MapObject.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

MapObject::MapObject()
	: AnimationRenderer_(nullptr)
	, UVMoveRenderer_(nullptr)
	, Speed_(0.f)
	, Time_(0.f)
{
}

MapObject::~MapObject()
{
}

void MapObject::CreateAnimation(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float4 _Pos, float4 _Scale)
{
	AnimationRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	AnimationRenderer_->CreateFrameAnimationFolder(_Name, FrameAnimation_DESC(_FolderName, _PlaySpeed));
	AnimationRenderer_->GetTransform().SetLocalPosition(_Pos);
	AnimationRenderer_->GetTransform().SetLocalScale(_Scale);
	AnimationRenderer_->ChangeFrameAnimation(_Name);
}

void MapObject::CreateFish(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float _Speed, float4 _Pos, float4 _Scale)
{
	Speed_ = _Speed;

	UVMoveRenderer_->CreateFrameAnimationFolder(_Name, FrameAnimation_DESC(_FolderName, _PlaySpeed));
	UVMoveRenderer_->GetTransform().SetLocalPosition(_Pos);
	UVMoveRenderer_->GetTransform().SetLocalScale(_Scale);
	UVMoveRenderer_->ChangeFrameAnimation(_Name);
}

void MapObject::CreateTexture(const std::string _Name, float4 _Pos, float _Speed, bool _IsPluseMove)
{
	Speed_ = _Speed;
	UVMoveRenderer_->SetTexture(_Name);
	UVMoveRenderer_->ScaleToTexture();
	UVMoveRenderer_->GetTransform().SetLocalPosition({ _Pos });
}

void MapObject::Start()
{
	GetTransform().SetLocalPosition(float4{ 0, 0, (int)ZOrder::BACKGROUND });

	UVMoveRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	UVMoveRenderer_->SetSamplingModeLinerMirror();
	UVMoveRenderer_->renderOption.Temp0 = 1;

	AnimationRenderer_ = CreateComponent<GameEngineTextureRenderer>();
}

void MapObject::Update(float _DeltaTime)
{
	if (true == UVMoveRenderer_->IsUpdate())
	{
		Time_ += _DeltaTime;
		UVMoveRenderer_->GetTimeData().Time = Time_ / Speed_;
	}

}

