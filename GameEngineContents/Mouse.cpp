#include "PreCompile.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

Mouse::Mouse() 
	: MouseCol_(nullptr)
	, MouseRenderer_(nullptr)
	, SoundPlay_(true)
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
	GetCurPos();
	GetTransform().SetLocalPosition({ CurPos_.x,CurPos_.y });
	MouseCol_ = CreateComponent<GameEngineCollision>("MouseCol");

	MouseRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MouseRenderer_->SetTexture("Cursor_Idle.png");
	MouseRenderer_->GetTransform().SetLocalScale({ 24 * 1.2f, 28.f * 1.2f });
	//MouseRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	if (false == GameEngineInput::GetInst()->IsKey("LeftMouse"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftMouse", VK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey("RightMouse", VK_RBUTTON);
	}
}

void Mouse::Update(float _DeltaTime)
{
	GetCurPos();
	GetTransform().SetLocalPosition({ CurPos_.x,CurPos_.y });
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		MouseRenderer_->SetTexture("Cursor_Idle.png");
	}
}

