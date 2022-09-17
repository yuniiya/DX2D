#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	void TextRenderingUpdate();
	void TextRender(const std::string& _Text, int _Count, const std::string& _Font = "����");
	void SetText(const std::string& _Text);

	bool IsTypingEnd_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineFontRenderer* FontRenderer_;

private:
	int TypeCount_;
	int LineChangeCount_;
	float TypingTimer_;
	float ZeroTimer_;
	int ChangeLine_;
	int ByteCount_;



	std::string Text_;
	std::string SubText_;

	NPCType NPCType_;
};

