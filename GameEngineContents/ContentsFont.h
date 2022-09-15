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

	void TextRender(const std::string& _Text, int _Count, const std::string& _Font = "µ¸¿ò");
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineFontRenderer* FontRenderer_;

	int TypeCount_;
	float TypingTimer_;

	bool IsTypingEnd_;

	std::string Text_;
	std::string SubText_;
};

