#include "PreCompile.h"
#include "MapBackGround.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

MapBackGround::MapBackGround() 
	: Time_(0.f)
{
}

MapBackGround::~MapBackGround() 
{
}

void MapBackGround::Start()
{
	MapBackGroundRender_ = CreateComponent<GameEngineTextureRenderer>();
	MapBackGroundRender_->SetPivot(PIVOTMODE::LEFTTOP);

	AriantSunLight_ = CreateComponent<GameEngineTextureRenderer>();
	AriantSunLight_->SetTexture("Ariant_SunLight.png");
	AriantSunLight_->ScaleToTexture();
	AriantSunLight_->Off();

	AriantCloud_ = CreateComponent<GameEngineTextureRenderer>();
	AriantCloud_->SetTexture("Desert_Cloud2.png");
	AriantCloud_->ScaleToTexture();
	AriantCloud_->SetSamplingModeLinerMirror();
	AriantCloud_->renderOption.Temp0 = 1;
	AriantCloud_->Off();
}

void MapBackGround::Update(float _DeltaTime)
{
	if (true == AriantSunLight_->IsUpdate())
	{
		AriantSunLight_->GetTransform().SetLocalPosition({ GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition().x, SunShineYPos_});
	}
	if (true == AriantCloud_->IsUpdate())
	{
		Time_ += _DeltaTime;
		AriantCloud_->GetTimeData().Time = Time_ / 40.f;
		AriantCloud_->GetTransform().SetLocalPosition({ GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition().x, AriantCloudPos_ });
	}

}

