#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <list>

// 설명 : 화면에 등장하는 모든것을 표현하기 위한 클래스
class GameEngineComponent;
class GameEngineActor :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor() = 0;

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline GameEngineLevel* GetLevel() { return ParentLevel; }

	template<typename Componenttype>
	Componenttype* CreateComponent()
	{
		GameEngineComponent* NewComponent = new Componenttype();
		NewComponent->ParentActor = this;
		NewComponent->Start();
		AllComList.push_back(NewComponent);
		return dynamic_cast<Componenttype*>(NewComponent);
	}

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	void ComponentUpdate(float _ScaleDeltaTime, float _DeltaTime);

	std::list<class GameEngineComponent*> AllComList;

	class GameEngineLevel* ParentLevel;

	void SetLevel(GameEngineLevel* _ParentLevel)
	{
		ParentLevel = _ParentLevel;
	}
};

