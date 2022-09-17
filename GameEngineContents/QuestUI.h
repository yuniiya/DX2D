#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineFontRenderer;
class Mouse;
class ContentsFont;
class QuestUI : public GameEngineActor
{
public:
	// constrcuter destructer
	QuestUI();
	~QuestUI();

	// delete Function
	QuestUI(const QuestUI& _Other) = delete;
	QuestUI(QuestUI&& _Other) noexcept = delete;
	QuestUI& operator=(const QuestUI& _Other) = delete;
	QuestUI& operator=(QuestUI&& _Other) noexcept = delete;

public:
	inline void SetNPC(NPC* _NPC)
	{
		NPC_ = _NPC;
	}

	inline NPC* GetNPC()
	{
		return NPC_;
	}

	void SetNPCType(NPCType _NPCType);

	bool IsQuestOngoing_;
	bool IsQuestClear_;
	bool IsQuestEnd_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void CollisionCheck();
	void TextSetting(const std::string& _Text, NPCType _NPCType);
	void ResetDialog();
	void ButtonOn();
	void ButtonOff();
	void ChangeToNextDialog();

private:
	GameEngineFontRenderer* NPCNameFont_;

	GameEngineUIRenderer* Renderer_;
	GameEngineUIRenderer* UINPCRenderer_;
	GameEngineUIRenderer* ButtonYes_;
	GameEngineUIRenderer* ButtonNo_;

	GameEngineCollision* ButtonYesCol_;
	GameEngineCollision* ButtonNoCol_;
	GameEngineCollision* ExitCol;

	NPC* NPC_;
	NPCType NPCType_;
	ContentsFont* Font_;

	int DialogCount_;

private:
	class TextData {

		std::string NpcTextureName;
		std::string NpcName_;
		std::string Text_;
		float4 Color_;
	};

	std::map<NPCType, std::vector<std::string>> NpcTexts;

	std::vector<std::string> AriantDialogList_;
	std::vector<std::string> EntranceDialogList_;
	std::vector<std::string> CastleDialogList_;

};

