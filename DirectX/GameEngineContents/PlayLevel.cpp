#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include "PlayLevelUIActor.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineButton.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "FadeEffect.h"
#include "Map.h"
#include "Monster.h"
#include "Portal.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>



PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}



void PlayLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChangeKey"))
	{
		IsDebugSwitch();
	}


}

void PlayLevel::Start()
{
	
	GetMainCamera()->GetCamTarget()->DepthSettingOff();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 900,-1000.0f});
	
	Map0 = CreateActor<Map>();
	Map0->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 1.0f });
	Player0 = CreateActor<Player>();
	Player0->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 1.0f });
	Player0->SetColMap("ColEllinia1.png");
	

	MonsterObject = CreateActor<Monster>();
	MonsterObject->GetTransform()->SetWorldPosition({ 100.0f, -15.0f, 1.0f });

	Portal0 = CreateActor<Portal>();
	Portal0->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 1.0f });
	Portal0->SetLevelName("TitleLevel");
	
	
}
void PlayLevel::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
	
}

void PlayLevel::LevelChangeEnd() 
{
	GameEngineLevel::LevelChangeEnd();
	
}

