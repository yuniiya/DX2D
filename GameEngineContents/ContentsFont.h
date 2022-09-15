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
	void SetNPCDialog(NPCType _NPCType);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineFontRenderer* FontRenderer_;

	std::vector<std::string> AriantDialogList_;
	std::vector<std::string> EntranceDialogList_;
	std::vector<std::string> CastleDialogList_;

private:
	int TypeCount_;
	float TypingTimer_;

	bool IsTypingEnd_;
	bool IsLineChange_;

	std::string Text_;
	std::string SubText_;

	NPCType NPCType_;
};

