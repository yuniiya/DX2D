#include "PreCompile.h"
#include "TitleLevel.h"
#include "Mouse.h"
#include "Fade.h"
#include "TitleLogo.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	TitleLogo* Logo = CreateActor<TitleLogo>(GAMEOBJGROUP::UI);
}

void TitleLevel::Update(float _DeltaTime)
{
}

void TitleLevel::End()
{

}
