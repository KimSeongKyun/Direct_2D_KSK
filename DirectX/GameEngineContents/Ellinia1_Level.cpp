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
#include "ContentsCore.h"

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
	ResourceRoad();
	CameraSetting();
	ActorSetting();	
}
void Ellinia1_Level::LevelChangeStart()
{
	ResourceRoad();
	CameraSetting();
	ActorSetting();

	GameEngineLevel::LevelChangeStart();
}

void Ellinia1_Level::LevelChangeEnd()
{

	GameEngineLevel::LevelChangeEnd();


}

void Ellinia1_Level::ResourceRoad()
{
	// 플레이어 리소스 로드
	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Player");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Swing0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Swing1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Swing2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Rope").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ladder").GetFullPath());
	}

	// 맵 로드
	if (nullptr == GameEngineSprite::Find("ElliniaMap1"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Map");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ElliniaMap1").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("MagicBoltBall"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Player");
		NewDir.Move("Skill");
		NewDir.Move("MagicBolt");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MagicBoltBall").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MagicBoltEffect").GetFullPath());
	}
}

void Ellinia1_Level::CameraSetting()
{
	GetMainCamera()->GetCamTarget()->DepthSettingOff();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0,-1000.0f });
}

void Ellinia1_Level::ActorSetting()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	{
		Map0 = CreateActor<Ellinia1_map>();
		Map0->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 1.0f });
	}

	{
		Player0 = CreateActor<Player>();
		Player0->GetTransform()->SetWorldPosition(ContentsCore::PlayerMovePos);
		Player0->SetColMap("ColEllinia0.png");
		Player0->SetCurMap("ColEllinia0.png");
	}

	//ContentsCore::MapScale = 

	{
		Snale0 = CreateActor<Snale>();
		Snale0->GetTransform()->SetWorldPosition({ 100.0f, -15.0f, 1.0f });
		Snale0->SetColMap("ColEllinia0.png");
		Snale0->SetHP(100);
	}

	{
		Portal0 = CreateActor<Portal>();
		Portal0->GetTransform()->SetWorldPosition({ 750.0f, -897.0f, 1.0f });
		Portal0->SetLevelName("Ellinia1_Level");
		Portal0->SetCoordinate({ 743.0f, -785.0f , 1.0f });
	}

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
