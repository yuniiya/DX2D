#include "PreCompile.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCameraActor.h>

Mouse::Mouse() 
	: MouseCol_(nullptr)
	, MouseRenderer_(nullptr)
	, SoundPlay_(false)
{
}

Mouse::~Mouse() 
{
}

void Mouse::GetCurPos()
{
	CurPos_.x = GetLevel()->GetMainCamera()->GetMouseWorldPosition().x;
	CurPos_.y = GetLevel()->GetMainCamera()->GetMouseWorldPosition().y;
	std::string CurLevel = GetLevel()->GetNameCopy();
}

void Mouse::Start()
{
	GetCurPos();
	GetTransform().SetLocalPosition({ CurPos_.x,CurPos_.y });

	MouseCol_ = CreateComponent<GameEngineCollision>("MouseCol");
	MouseCol_->GetTransform().SetLocalPosition({ CurPos_.x,CurPos_.y });
	MouseCol_->GetTransform().SetLocalScale({ 24.f, 28.f });
	MouseCol_->ChangeOrder(GAMEOBJGROUP::MOUSE);

	MouseRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MouseRenderer_->SetTexture("Cursor_Idle.png");
	MouseRenderer_->GetTransform().SetLocalScale({ 24.f * 1.2f, 28.f * 1.2f });

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

	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
	{
		SoundPlay_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		MouseRenderer_->SetTexture("Cursor_Click.png");
		MouseRenderer_->GetTransform().SetLocalScale({ 25.f * 1.2f, 23.f * 1.2f });
	}
	else
	{
		MouseRenderer_->SetTexture("Cursor_Idle.png");
		MouseRenderer_->GetTransform().SetLocalScale({ 24.f * 1.2f, 28.f * 1.2f });
	}
	if (true == SoundPlay_)
	{
		GameEngineSound::SoundPlayOneShot("BtMouseClick.mp3");
		SoundPlay_ = false;
	}
}

