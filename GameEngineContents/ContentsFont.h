#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

enum class FontType
{
	Normal,
	Meso,
	Typing, 

	MAX,
};

class GameEngineFontRenderer;
class ContentsFont : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsFont();
	~ContentsFont();

	// delete Function
	ContentsFont(const ContentsFont& _Other) = delete;
	ContentsFont(ContentsFont&& _Other) noexcept = delete;
	ContentsFont& operator=(const ContentsFont& _Other) = delete;
	ContentsFont& operator=(ContentsFont&& _Other) noexcept = delete;

public:
	inline GameEngineFontRenderer* GetFontRenderer()
	{
		return FontRenderer_;
	}

	inline GameEngineFontRenderer* GetNormalFontRenderer()
	{
		return NormalFontRenderer_;
	}

	inline void SetNPCType(NPCType _NPCType)
	{
		NPCType_ = _NPCType;
	}

	inline void ResetType()
	{
		TypeCount_ = 0;
		TypingTimer_ = 0.f;
	}

	inline void ResetByteCount()
	{
		ByteCount_ = 0;
	}

	inline void ResetTimer()
	{
		TypingTimer_ = ZeroTimer_;
		IsTypingEnd_ = true;
	}

	inline void SetTextSize(float _TextSize)
	{
		NormalFontRenderer_->SetSize(_TextSize);
	}

	inline void SetFontType(FontType _FontType)
	{
		FontType_ = _FontType;
	}

	inline std::string GetText()
	{
		return Text_;
	}

	void TextRenderingUpdate();
	void TextRender(const std::string& _Text, int _Count, const std::string& _Font = "µ¸¿ò");
	void SetText(const std::string& _Text);
	void SetComma();

	bool IsTypingEnd_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineFontRenderer* FontRenderer_;
	GameEngineFontRenderer* NormalFontRenderer_;

private:
	int TypeCount_;
	int ByteCount_;

	float TypingTimer_;
	float ZeroTimer_;

	std::string Text_;
	std::string SubText_;

	NPCType NPCType_;
	FontType FontType_;
};

