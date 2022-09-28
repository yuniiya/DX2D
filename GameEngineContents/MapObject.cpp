#include "PreCompile.h"
#include "MapObject.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

MapObject::MapObject()
	: AnimationRenderer_(nullptr)
	, XMoveRenderer_(nullptr)
	, UVMoveRenderer_(nullptr)
	, UVSpeed_(0.f)
	, Time_(0.f)
	, WindowScale_(0.f)
	, TextureScale_(0.f)
	, MoveSpeed_(0.f)
{
}

MapObject::~MapObject()
{
}

void MapObject::CreateAnimation(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float4 _Pos, float4 _Scale)
{
//	AnimationRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	AnimationRenderer_->CreateFrameAnimationFolder(_Name, FrameAnimation_DESC(_FolderName, _PlaySpeed));
	AnimationRenderer_->GetTransform().SetLocalPosition(_Pos);
	AnimationRenderer_->GetTransform().SetLocalScale(_Scale);
	AnimationRenderer_->ChangeFrameAnimation(_Name);
}

void MapObject::CreateXMoveAnimaition(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float _MoveSpeed_, float4 _Pos, float4 _Scale, ACTORDIR _Dir)
{
	TextureScale_ = _Scale;
	if (_Dir == ACTORDIR::LEFT)
	{
		MoveSpeed_ = -_MoveSpeed_;
	}
	else
	{
		MoveSpeed_ = _MoveSpeed_;
	}

	XMoveRenderer_->CreateFrameAnimationFolder(_Name, FrameAnimation_DESC(_FolderName, _PlaySpeed));
	XMoveRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	XMoveRenderer_->GetTransform().SetLocalPosition(_Pos);
	XMoveRenderer_->GetTransform().SetLocalScale(_Scale);
	XMoveRenderer_->ChangeFrameAnimation(_Name);
}

void MapObject::CreateUVMoveTexture(const std::string _Name, float4 _Pos, float _UVSpeed)
{
	UVSpeed_ = _UVSpeed;
	UVMoveRenderer_->SetTexture(_Name);
	UVMoveRenderer_->ScaleToTexture();
	UVMoveRenderer_->GetTransform().SetLocalPosition({ _Pos });
}

void MapObject::Start()
{
	GetTransform().SetLocalPosition(float4{ 0, 0, (int)ZOrder::BACKGROUND });
	GetWindowScale();

	UVMoveRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	UVMoveRenderer_->SetSamplingModeLinerMirror();
	UVMoveRenderer_->renderOption.Temp0 = 1;

	AnimationRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	XMoveRenderer_ = CreateComponent<GameEngineTextureRenderer>();
}

void MapObject::Update(float _DeltaTime)
{
	if (true == UVMoveRenderer_->IsUpdate())
	{
		Time_ += _DeltaTime;
		UVMoveRenderer_->GetTimeData().Time = Time_ / UVSpeed_;
	}

	if (true == XMoveRenderer_->IsUpdate())
	{
		// 왼쪽으로 나갔으면
		if (TextureScale_.x <= abs(0.f - TextureScale_.x))
		{
			// 오른쪽으로 보낸다
			XMoveRenderer_->GetTransform().SetLocalPosition(WindowScale_.x + TextureScale_.x);
		}
		else
		{
			// 나가기 전까지는 이동
			XMoveRenderer_->GetTransform().SetLocalMove(MoveSpeed_ * _DeltaTime);
		}
	}

}

