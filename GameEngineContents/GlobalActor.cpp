#include "PreCompile.h"
#include "GlobalActor.h"

GlobalActor::GlobalActor() 
	: MapTexture_(nullptr)
{
}

GlobalActor::~GlobalActor() 
{
}

void GlobalActor::Update(float _DeltaTime)
{

}

bool GlobalActor::PixelCollisionMapUpdate(GlobalActor* _Actor)
{
	MapTexture_ = GetLevel<GlobalLevel>()->GetCollisionMap()->GetCurTexture();

	if (nullptr == MapTexture_)
	{
		MsgBoxAssert("충돌맵이 설정되지 않았습니다");
	}

	float4 Color = MapTexture_->GetPixel((float)dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix(), -(float)(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + 39.f);

	if (false == Color.CompareInt4D(float4{1.f, 1.f, 1.f, 0.f}))
	{
		int a = 0;
	}

	return true;
}

void GlobalActor::DirCheck(GameEngineTextureRenderer* _Renderer, ACTORDIR _Dir)
{
	if (ACTORDIR::LEFT == _Dir)
	{
		_Renderer->GetTransform().PixLocalPositiveX();
	}
	if (ACTORDIR::RIGHT == _Dir)
	{
		_Renderer->GetTransform().PixLocalNegativeX();
	}
}

