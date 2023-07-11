#include "PrecompileHeader.h"
#include "TitleAnimation.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderer.h>


TitleAnimation::TitleAnimation() 
{
}

TitleAnimation::~TitleAnimation() 
{
}

void TitleAnimation::Start()
{
	if (nullptr == GameEngineSprite::Find("Wizet0.png"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Title");


		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TitleBack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Wizet").GetFullPath());
	}

	
	Back = CreateComponent<GameEngineSpriteRenderer>();
	Back->SetTexture("TitleBack.png");
	Back->SetScaleToTexture("TitleBack.png");

	TitleAniRender = CreateComponent<GameEngineSpriteRenderer>();
	TitleAniRender->CreateAnimation({ .AnimationName = "Wizet", .SpriteName = "Wizet",.Loop = false ,.ScaleToTexture = true });
	TitleAniRender->ChangeAnimation("Wizet");
	TitleAniRender->GetTransform()->AddLocalPosition(float4::Up * 60.0f);
	//.FrameInter = 0.2f,
}
void TitleAnimation::Update(float _Delta)
{
	

	if (true == TitleAniRender->IsAnimationEnd())
	{
		WaittingTime += _Delta;

		if (WaittingTime >= 2.0f)
		{
			GameEngineCore::ChangeLevel("Ellinia0_Level");
		}
	}

	if (GameEngineInput::IsAnyKey())
	{
		GameEngineCore::ChangeLevel("Ellinia0_Level");
	}

	
	
}
void TitleAnimation::Render(float _Delta)
{

}