#include "PrecompileHeader.h"
#include "Ellinia1_Level.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineButton.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "FadeEffect.h"
#include "Ellinia1_map.h"
#include "Snale.h"
#include "Portal.h"
#include "Player.h"
#include "Status.h"
#include "QuickSlot.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>



Ellinia1_Level::Ellinia1_Level()
{
}

Ellinia1_Level::~Ellinia1_Level()
{
}



void Ellinia1_Level::Update(float _DeltaTime)
{
	/*if (true == GameEngineInput::IsDown("LevelChangeKey"))
	{
		IsDebugSwitch();
	}*/

	if (GameEngineInput::IsDown("LevelChangeKey"))
	{
		GameEngineCore::ChangeLevel("Ellinia0_Level");
	}

}

void Ellinia1_Level::Start()
{


	GetMainCamera()->GetCamTarget()->DepthSettingOff();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f});
	
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	Map0 = CreateActor<Ellinia1_map>();
	Map0->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 1.0f });


	Player0 = CreateActor<Player>();
	Player0->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 1.0f });
	Player0->SetColMap("ColEllinia1.png");
	Player0->SetCurMap("Ellinia1.png");
	
	MonsterObject = CreateActor<Snale>();
	MonsterObject->GetTransform()->SetWorldPosition({ 100.0f, -15.0f, 1.0f });
	MonsterObject->SetColMap("ColEllinia1.png");

	Portal0 = CreateActor<Portal>();
	Portal0->GetTransform()->SetWorldPosition({ 0.0f, -48.0f, 1.0f });
	Portal0->SetLevelName("TitleLevel");

	{

		float4 StatusUISize = { 204, 60 };
		float4 StatusUIPos = { 0.0f , -ScreenSize.hy() + StatusUISize.hy() };

		StatusRender = CreateActor<Status>();
		StatusRender->GetTransform()->SetWorldPosition(StatusUIPos);
	}
	{
		float4 QuickSlotSize = { 562.0f, 73.0f, 1.0f };
		float4 QuickSlotPos = { ScreenSize.hx() - QuickSlotSize.hx(), -ScreenSize.hy() + QuickSlotSize.hy() };

		StaQuickSlottusRender = CreateActor<QuickSlot>();
		StaQuickSlottusRender->GetTransform()->SetWorldPosition({ 0,0,0 });
		StaQuickSlottusRender->GetTransform()->SetWorldPosition(QuickSlotPos);
	}
	
	
}
void Ellinia1_Level::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
}

void Ellinia1_Level::LevelChangeEnd()
{

	GameEngineLevel::LevelChangeEnd();


}

