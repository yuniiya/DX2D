#include "PreCompile.h"
#include "GlobalActor.h"

GlobalActor::GlobalActor() 
	: MapTexture_(nullptr)
	, CurDir_(ACTORDIR::MAX)
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
		MsgBoxAssert("�浹���� �������� �ʾҽ��ϴ�");
	}

	float4 BottomColor = MapTexture_->GetPixelToFloat4(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix())
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos)));

	float4 LeftColor = MapTexture_->GetPixelToFloat4(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix()) - _LeftRightPos
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()))));

	float4 RightColor = MapTexture_->GetPixelToFloat4(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix()) + _LeftRightPos
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()))));

	float4 BottomLeftDownColor = MapTexture_->GetPixelToFloat4(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix()) - _LeftRightPos
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos - 20.f)));

	float4 BottomRightDownColor = MapTexture_->GetPixelToFloat4(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix()) + _LeftRightPos
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos - 20.f)));

	float4 BottomLeftUpColor = MapTexture_->GetPixelToFloat4(static_cast<float>(GetTransform().GetWorldPosition().ix() - _LeftRightPos)
		, static_cast<float>(-GetTransform().GetWorldPosition().iy()) + _BottomPos + 10.f);	// �ߺ��� ������

	float4 BottomRightUpColor = MapTexture_->GetPixelToFloat4(static_cast<float>(GetTransform().GetWorldPosition().ix() + _LeftRightPos)
		, static_cast<float>(-GetTransform().GetWorldPosition().iy()) + _BottomPos + 10.f);	// �ߺ��� ������

	float4 BottomUpColor = MapTexture_->GetPixelToFloat4(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix())
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos) + 2.f));

	float4 BottomDownColor = MapTexture_->GetPixelToFloat4(static_cast<float>(dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().ix())
		, -(static_cast<float>((dynamic_cast<GlobalActor*>(_Actor)->GetTransform().GetWorldPosition().iy()) + _BottomPos) - 70.f));


	// �� �� ���� ���� ���� ������ ��
	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		//if (true == BottomLeftUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		//	|| true == BottomRightUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
		if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
		{
			Pos = float4{ 0.f, 2.f, 0.f };
			GetTransform().SetWorldMove(Pos);
		}
	}


	// ��� => �����ش�
	if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })		// ���
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// ����
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// ����Ÿ
		|| true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// ����
	{

		// ��, ����, ���� => �÷��ش�
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
	else
	{
		DownPower_ = 0.0f;
	}

	// ���ִ� ���� ������ ���� ����� ��
	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))				// �� ���� ��
	{
		if (true == BottomLeftDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f }))		// �� ���� ��, �� �ؿ��� ���� ���
		{
			Pos = float4{ 2.f, 0.f, 0.f };
			GetTransform().SetWorldMove(Pos);

			//SetDir(ACTORDIR::RIGHT);
			CurDir_ = ACTORDIR::RIGHT;
		}
		else if (true == BottomRightDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f }))
		{
			Pos = float4{ -2.f, 0.f, 0.f };
			GetTransform().SetWorldMove(Pos);

			CurDir_ = ACTORDIR::LEFT;
		}
	}

	// �� �ܰ�
	if (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
	{
		Pos = float4{ 2.f, 0.f, 0.f };
		GetTransform().SetWorldMove(Pos);

		//SetDir(ACTORDIR::RIGHT);
		CurDir_ = ACTORDIR::RIGHT;
	}

	if (true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
	{
		Pos = float4{ -2.f, 0.f, 0.f };
		GetTransform().SetWorldMove(Pos);

		CurDir_ = ACTORDIR::LEFT;
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

