#include "PreCompile.h"
#include "Cloud.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

Cloud::Cloud() 
	: Renderer_(nullptr)
	, Time_(0.f)
	, Speed_(0.f)
	, IsPlusMove_(false)
{
}

Cloud::~Cloud() 
{
}

void Cloud::CreateCloud(const std::string _Name, float4 _Pos, float _Speed, bool _IsPluseMove)
{
	Speed_ = _Speed;
	Renderer_->SetTexture(_Name);
	Renderer_->ScaleToTexture();
	Renderer_->GetTransform().SetLocalPosition({ _Pos });
}

void Cloud::Start()
{
	GetTransform().SetLocalPosition(float4{ 0, 0, (int)ZOrder::BACKGROUND });
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModeLinerMirror();
	Renderer_->renderOption.Temp0 = 1;

}

void Cloud::Update(float _DeltaTime)
{
	Time_ += _DeltaTime;
	Renderer_->GetTexturePosData().Pos = Time_ / Speed_;
	float4 Temp = Renderer_->GetTexturePosData().Pos;
}

