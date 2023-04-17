#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

enum class LoginTextType
{
	ID,
	PW,

	MAX,
};

class GameEngineFontRenderer;
class GameEngineCollision;
class TextArea : public GameEngineActor
{
private:
	static bool caretshow_;

public:
	static void SetCurCaretState(bool _Flag);
	void TextAreaInit(const float4& _Value, int _Len);
private:
	bool TextInputOK_;
	std::string InputText_;
	int MaxLen_;
	//int curcaretpos_;				// ** »èÁ¦ ¿ä¸Á
	//int prevcaretpos_;
	std::string TempText;

	LoginTextType TextType_;
private:
	GameEngineCollision* TextAreaCollision_;	
	GameEngineFontRenderer* TextRenderer_;

public:
	//construcuter destructer
	TextArea();
	~TextArea();

	//delete Function
	TextArea(const TextArea& _Other) = delete;
	TextArea(TextArea&& _Other) noexcept = delete;
	TextArea& operator=(const TextArea& _Other) = delete;
	TextArea& operator=(TextArea&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _DeltaTime) override;

	inline GameEngineFontRenderer* GetTextRenderer()
	{
		return TextRenderer_;
	}

	inline void SetTextPosition(float4 _ScreenPos)
	{
		TextRenderer_->SetScreenPostion(_ScreenPos);
	}

	inline std::string GetText()
	{
		return InputText_;
	}

	inline void SetLoginTextType(LoginTextType _TextType)
	{
		TextType_ = _TextType;
	}

	inline void ReSetText()
	{
		if (!InputText_.empty())
		{
			InputText_.clear();
		}
	}

	bool IsTextOn_;
public:
	void AddText(const std::string& _Text);
};

