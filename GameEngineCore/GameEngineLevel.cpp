#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineCamera.h"

GameEngineLevel::GameEngineLevel() 
	: MainCamera(nullptr)
	, UIMainCamera(nullptr)
{
}

GameEngineLevel::~GameEngineLevel() 
{
	for (const std::pair<int, std::list<GameEngineActor*>>& Group : AllActors)
	{
		for (GameEngineActor* Actor : Group.second)
		{
			if (nullptr == Actor)
			{
				continue;
			}

			Actor->ReleaseHierarchy();
		}
	}
}


void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	for (const std::pair<int, std::list<GameEngineActor*>>& Group : AllActors)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		for (GameEngineActor* const Actor : Group.second)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->AllUpdate(ScaleTime, _DeltaTime);
		}
	}

}

void GameEngineLevel::PushRenderer(GameEngineRenderer* _Renderer)
{
	MainCamera->PushRenderer(_Renderer);
}

void GameEngineLevel::PushCamera(GameEngineCamera* _Camera)
{
	MainCamera = _Camera;
}

GameEngineTransform& GameEngineLevel::GetMainCameraActorTransform()
{
	return MainCamera->GetActor()->GetTransform();
}

void GameEngineLevel::Render(float _DelataTime)
{
	GameEngineDevice::RenderStart();

	// 이 사이에서 무언가를 해야 합니다.
	MainCamera->Render(_DelataTime);

	GameEngineDevice::RenderEnd();
}

void GameEngineLevel::Release(float _DelataTime)
{
	for (GameEngineUpdateObject* Object : DeleteObject)
	{
		Object->ReleaseHierarchy();
	}

	DeleteObject.clear();

	MainCamera->Release(_DelataTime);

	// std::list<GameEngineActor*> 루트 액터 부모가 없는 액터들만 여기에 들어올수 있다.
	// a c
	// b
	// 
	// b->setParent(a);

	std::map<int, std::list<GameEngineActor*>>::iterator StartGroupIter = AllActors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator EndGroupIter = AllActors.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineActor*>& Group = StartGroupIter->second;

		std::list<GameEngineActor*>::iterator GroupStart = Group.begin();
		std::list<GameEngineActor*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			(*GroupStart)->ReleaseObject(DeleteObject);

			if (true == (*GroupStart)->IsDeath())
			{
				// AllActors[StartGroupIter->first].remove((*GroupStart));

				// DeleteObject.push_back((*GroupStart));
				GroupStart = Group.erase(GroupStart);
			}
			else 
			{
				++GroupStart;
			}
			
		}
	}

}

void GameEngineLevel::LevelUpdate(float _DeltaTime)
{
	AddAccTime(_DeltaTime);
	Update(_DeltaTime);
	ActorUpdate(_DeltaTime);
	Render(_DeltaTime);
	Release(_DeltaTime);
}

// 레벨을 이동하는 액터
// 루트인애가 지우려고 여기로 온다고 생각할 겁니다.
void GameEngineLevel::RemoveActor(GameEngineActor* _Actor)
{
	if (AllActors.end() == AllActors.find(_Actor->GetOrder()))
	{
		MsgBoxAssert("이액터를 루트가 아닙니다 삭제할수 없습니다.");
	}

	AllActors[_Actor->GetOrder()].remove(_Actor);
}