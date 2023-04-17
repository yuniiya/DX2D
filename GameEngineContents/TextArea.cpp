#include "PreCompile.h"
#include "TextArea.h"
#include <GameEngineContents/KeyboardClass.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Enums.h"


bool TextArea::caretshow_ = false;

void TextArea::SetCurCaretState(bool _Flag)
{
	caretshow_ = _Flag;
}

void TextArea::TextAreaInit(const float4& _Value, int _Len)
{
	TextAreaCollision_ = CreateComponent<GameEngineCollision>();
	TextAreaCollision_->GetTransform().SetLocalScale({250.f, 30.f});
	MaxLen_ = _Len;
}

TextArea::TextArea()
	: TextInputOK_(false)
	//, curcaretpos_(0)
	//, prevcaretpos_(0)
	, TextAreaCollision_(nullptr)
	, MaxLen_(0)
{
}


TextArea::~TextArea()
{
}

void TextArea::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Chatting_Del"))
	{
		GameEngineInput::GetInst()->CreateKey("Chatting_Del", VK_BACK);
	}

	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::FONT });
	TextRenderer_ = CreateComponent<GameEngineFontRenderer>();
	TextRenderer_->SetSize(20);
	//TextRenderer_->SetScreenPostion({510.f, 300.f });
	TextRenderer_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	TextRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
}

void TextArea::Update(float _DeltaTime)
{
	SetTextColor(GameEngineWindow::GetHDC(), RGB(0, 0, 0));
	// ���콺�� �ؽ�Ʈ �Է�â �浹
	
	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse")
		&& true == TextAreaCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		TextInputOK_ = true;
		KeyboardClass::GetInst().DeleteCharBuffer();
		// ** ���� ���
			//// ĳ�� ����
			//if (false == caretshow_)
			//{
			//	caretshow_ = true;
			//	CreateCaret(GameEngineWindow::GetHWND(), NULL, 2, 14);
			//	ShowCaret(GameEngineWindow::GetHWND());
			//	SetCaretBlinkTime(50);
			//	SetCaretPos(640,360);
			//}
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			if (true == TextInputOK_)
			{
				// Input On
				TextInputOK_ = false;

				// ** ���� ���
				//// ĳ�� ����
				//if (true == caretshow_)
				//{
				//	caretshow_ = false;

				//	// ĳ�� �ݳ�
				//	SetCaretBlinkTime(20);
				//	HideCaret(GameEngineWindow::GetHWND());
				//	DestroyCaret();
				//}
			}
		}

		if (true == TextInputOK_)
		{
			if (false == KeyboardClass::GetInst().CharBufferIsEmpty())
			{
				while (!KeyboardClass::GetInst().CharBufferIsEmpty())
				{
					std::string SetStr = "";
					unsigned char ReadChar = KeyboardClass::GetInst().ReadChar();
					SetStr += ReadChar;

					AddText(SetStr);
				}
			}		
		}
		
	}

	// �Է����� ä�� ���ڿ� ���������� ����
	if (true == GameEngineInput::GetInst()->IsDown("Chatting_Del"))
	{
		// ä�� �Է�â Ȱ��ȭ �ÿ��� �Ʒ� ó������
		if (true == TextInputOK_)
		{
			if (!InputText_.empty())
			{
				InputText_.pop_back();
				//curcaretpos_ = static_cast<int>(lstrlen(InputText_.c_str()));
				SIZE CurTextSize;
				GetTextExtentPoint(GameEngineWindow::GetHDC(), InputText_.c_str(), lstrlen(InputText_.c_str()), &CurTextSize);
				//SetCaretPos(GetTransform().GetLocalPosition().ix() - 56 + CurTextSize.cx, GetTransform().GetLocalPosition().iy() - 6);// ** ���� ���
			}
		}
	}
	
	else
	{
		
	}


	if (!InputText_.empty())
	{
		IsTextOn_ = true;
		TextRenderer_->On();
		SetBkMode(GameEngineWindow::GetHDC(), TRANSPARENT);
		// �Է� ���� �ؽ�Ʈ�� �ִٸ� ���
		if (TextType_ == LoginTextType::PW)
		{
			TempText = "";

			for (int i = 0; i < InputText_.size(); i++)
			{
				TempText += "��";
			}
			TextRenderer_->SetText(TempText);
		}
		else
		{
			TextRenderer_->SetText(InputText_);
		}

		if (true == caretshow_)
		{
			//curcaretpos_ = static_cast<int>(lstrlen(InputText_.c_str()));
			SIZE CurTextSize;
			GetTextExtentPoint(GameEngineWindow::GetHDC(), InputText_.c_str(), lstrlen(InputText_.c_str()), &CurTextSize);
			//SetCaretPos(GetTransform().GetLocalPosition().ix() - 56 + CurTextSize.cx, GetTransform().GetLocalPosition().iy() - 6);// ** ���� ���
		}
	}
	else
	{
		// �Է¹޾ƿ� �ؽ�Ʈ�� ���� (���۰� ����ִ�)
		IsTextOn_ = false;
		TextRenderer_->Off();
	}
}

void TextArea::AddText(const std::string& _Text)
{
	// ä�� �ִ���ڼ� �Ѿ�� �ԷºҰ�
	std::string CurText = InputText_;
	CurText += _Text;
	if (MaxLen_ <= lstrlen(CurText.c_str()))
	{
		// �ԷºҰ�
		return;
	}

	InputText_ += _Text;
}