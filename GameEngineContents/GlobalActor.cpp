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

bool GlobalActor::PixelCollisionMapUpdate(GlobalActor* _Actor, float _LeftRightPos, float _BottomPos)
{
	float4 Pos = 0.0f;

	MapTexture_ = GetLevel<GlobalLevel>()->GetCollisionMap()->GetCurTexture();

	if (nullptr == MapTexture_)
	{
		MsgBoxAssert("충돌맵이 설정되지 않았습니다");
	}

	float4 BottomColor = MapTexture_->GetPixel(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix())
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos)));

	float4 LeftColor = MapTexture_->GetPixel(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix()) - _LeftRightPos
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()))));

	float4 RightColor = MapTexture_->GetPixel(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix()) + _LeftRightPos
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()))));

	float4 BottomLeftColor = MapTexture_->GetPixel(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix()) - _LeftRightPos
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos)));

	float4 BottomRightColor = MapTexture_->GetPixel(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix()) + _LeftRightPos
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos)));

	float4 BottomLeftUpColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix() - _LeftRightPos)
		, static_cast<float>(-GetTransform().GetWorldPosition().iy()) + 10.f);	// 발보다 조금위

	float4 BottomRightUpColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix() + _LeftRightPos)
		, static_cast<float>(-GetTransform().GetWorldPosition().iy()) + 10.f);	// 발보다 조금위

	float4 BottomUpColor = MapTexture_->GetPixel(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix())
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos) + 10.f));

	float4 BottomDownColor = MapTexture_->GetPixel(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix())
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos) - 70.f));


	// 허공 => 내려준다
	if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })		// 흰색
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// 투명
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// 마젠타
		|| true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// 레드
	{

		// 땅, 레더, 로프 => 올려준다
		if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
			|| true == BottomColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f })
			|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f }))
		{
			Pos = float4{ 0.f, 2.f, 0.f };
			GetTransform().SetWorldMove(Pos);
		}
		else
		{
			DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 10.f;
			GetTransform().SetWorldMove(DownPower_);
		}

	}

	if (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f })
		|| true == BottomLeftColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })			// 떠있는 지형 위에서 옆이 허공일 경우
		|| true == BottomLeftColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f }))
	{
		Pos = float4{ 2.f, 0.f, 0.f };
		GetTransform().SetWorldMove(Pos);

		//SetDir(ACTORDIR::RIGHT);
		CurDir_ = ACTORDIR::RIGHT;
	}

	if (true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f })
		|| true == BottomRightColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })
		|| true == BottomRightColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f }))
	{
		Pos = float4{ -2.f, 0.f, 0.f };
		GetTransform().SetWorldMove(Pos);

		CurDir_ = ACTORDIR::LEFT;
	}


	//// 허공 => 내려준다
	//if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })		// 흰색
	//	|| true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// 투명
	//	|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// 마젠타
	//	|| true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// 레드
	//{

	//	// 땅, 레더, 로프 => 올려준다
	//	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
	//		|| true == BottomColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f })
	//		|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f }))
	//	{
	//		Pos = float4{ 0.f, 2.f, 0.f };
	//		GetTransform().SetWorldMove(Pos);
	//	}
	//	else
	//	{
	//		DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 10.f;		// 땅, 레더, 로프가 아닐 경우
	//		GetTransform().SetWorldMove(DownPower_);
	//	}

	//}


	//if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	//{
	//	/*		if (true == BottomLeftUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
	//				|| true == BottomRightUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))	*/
	//	if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	//	{
	//		Pos = float4{ 0.f, 2.f, 0.f };
	//		GetTransform().SetWorldMove(Pos);
	//	}
	//}

	//if (MONSTERSTATE::MOVE == dynamic_cast<Monster*>(_Actor)->GetCurState())
	//{
	//	if (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f })
	//		|| true == BottomLeftColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })			// 떠있는 지형 위에서 옆이 허공일 경우
	//		|| true == BottomLeftColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f }))
	//	{
	//		if (true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))			// 떠있는 지형 위에서 옆이 허공이고, 조금 밑이 지형일 경우 
	//		{
	//			DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 2.f;
	//			GetTransform().SetWorldMove(DownPower_);
	//		}
	//		else
	//		{
	//			Pos = float4{ 2.f, 0.f, 0.f };
	//			GetTransform().SetWorldMove(Pos);

	//			CurDir_ = ACTORDIR::RIGHT;
	//		}
	//	}

	//	if (true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f })
	//		|| true == BottomRightColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })
	//		|| true == BottomRightColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f }))
	//	{
	//		if (true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	//		{
	//			DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 10.f;
	//			GetTransform().SetWorldMove(DownPower_);
	//		}
	//		else
	//		{
	//			Pos = float4{ -2.f, 0.f, 0.f };
	//			GetTransform().SetWorldMove(Pos);

	//			CurDir_ = ACTORDIR::LEFT;
	//		}
	///*		Pos = float4{ -2.f, 0.f, 0.f };
	//		GetTransform().SetWorldMove(Pos);

	//		CurDir_ = ACTORDIR::LEFT;*/
	//	}
	//}




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

