#include "PrecompileHeader.h"
#include "Ellinia0_Level.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineActor.h>


#include "ContentsCore.h"
#include "Ellinia0_map.h"
#include "Player.h"
#include "Portal.h"
#include "Snale.h"
#include "Status.h"
#include "QuickSlot.h"


Ellinia0_Level::Ellinia0_Level()
{
}

Ellinia0_Level::~Ellinia0_Level()
{
}

void Ellinia0_Level::Start()
{
	if (nullptr == GameEngineSprite::Find("Ellinia0"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Map");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ground").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BackGround").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ColMap").GetFullPath());
	}

	GetMainCamera()->GetCamTarget()->DepthSettingOff();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0,-1000.0f });

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	{
		Map0 = CreateActor<Ellinia0_map>();
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
		MonsterObject = CreateActor<Snale>();
		MonsterObject->GetTransform()->SetWorldPosition({ 100.0f, -15.0f, 1.0f });
		MonsterObject->SetColMap("ColEllinia0.png");
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

void Ellinia0_Level::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("LevelChangeKey"))
	{
		GameEngineCore::ChangeLevel("Ellinia1_Level");
	}

	float4 aaaa = Player0->GetTransform()->GetWorldPosition();
	float4 bbb = GetMainCamera()->GetTransform()->GetWorldPosition();
}



void Ellinia0_Level::LevelChangeStart()
{
	
	
	GameEngineLevel::LevelChangeStart();
}
void Ellinia0_Level::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();
}