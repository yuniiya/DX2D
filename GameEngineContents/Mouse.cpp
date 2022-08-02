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
	, ClickSoundOn_(false)
	, MouseAnimationRenderer_(nullptr)
	, MouseOverSoundOn_(false)
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

	MouseAnimationRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MouseAnimationRenderer_->CreateFrameAnimationFolder("Cursor_MouseOver", FrameAnimation_DESC("Cursor_MouseOver", 0.55f));
	MouseAnimationRenderer_->GetTransform().SetLocalScale({ 30.f * 1.1f, 30.f * 1.1f });
	MouseAnimationRenderer_->ChangeFrameAnimation("Cursor_MouseOver");
	MouseAnimationRenderer_->Off();


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
		ClickSoundOn_ = true;
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
	if (true == ClickSoundOn_)
	{
		GameEngineSound::SoundPlayOneShot("BtMouseClick.mp3");
		ClickSoundOn_ = false;
	}

	CollisionCheck();
}

bool Mouse::MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void Mouse::CollisionCheck()
{
	if (true == MouseCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::UI, CollisionType::CT_OBB2D,
		std::bind(&Mouse::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2))
		&& true == MouseOverSoundOn_)
	{
		MouseAnimationRenderer_->On();
		MouseRenderer_->Off();

		GameEngineSound::SoundPlayOneShot("BtMouseOver.mp3");
		MouseOverSoundOn_ = false;
	}
	else
	{
		MouseAnimationRenderer_->Off();
		MouseRenderer_->On();
	}

	if (false == MouseCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::UI, CollisionType::CT_OBB2D,
		std::bind(&Mouse::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)))
	{
		MouseOverSoundOn_ = true;
	}
}