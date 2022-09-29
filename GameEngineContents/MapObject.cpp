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

void MapObject::CreateXMoveAnimaition(const std::string _Name, const std::string _FolderName, float _PlaySpeed, float _MoveSpeed_, float4 _Pos, float4 _Scale, ACTORDIR _Dir)
{
	TexturePos_ = _Pos;
	TextureScale_ = _Scale;
	CurDir_ = _Dir;
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
	DirCheck(XMoveRenderer_, _Dir);
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

	if (CurDir_ == ACTORDIR::RIGHT)
	{
		// ���������� ��������
		if (XMoveRenderer_->GetTransform().GetLocalPosition().x >= WindowScale_.x + TextureScale_.x)
		{
			// �������� ������
			XMoveRenderer_->GetTransform().SetLocalPosition({ -TextureScale_.x, TexturePos_.y });
		}
		else
		{
			// ������ �������� �̵�
			XMoveRenderer_->GetTransform().SetLocalMove({ MoveSpeed_, 0.f * _DeltaTime });
		}
	}

	if (CurDir_ == ACTORDIR::LEFT)
	{
		// �������� ��������
		if (XMoveRenderer_->GetTransform().GetLocalPosition().x <= -TextureScale_.x)
		{
			// ���������� ������
			XMoveRenderer_->GetTransform().SetLocalPosition({ WindowScale_.x + TextureScale_.x, TexturePos_.y });
		}
		else
		{
			// ������ �������� �̵�
			XMoveRenderer_->GetTransform().SetLocalMove({ MoveSpeed_, 0.f * _DeltaTime });
		}
	}
}
