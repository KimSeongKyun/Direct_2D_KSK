#include "PrecompileHeader.h"
#include "TileMapLevel.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>


TileMapLevel::TileMapLevel() 
{
}

TileMapLevel::~TileMapLevel() 
{
}


void TileMapLevel::Start() 
{
	if (false == GameEngineInput::IsKey("TilePointLeft"))
	{
		GameEngineInput::CreateKey("TilePointLeft", 'A');
		GameEngineInput::CreateKey("TilePointRight", 'D');
		GameEngineInput::CreateKey("TilePointUp", 'W');
		GameEngineInput::CreateKey("TilePointDown", 'S');
		GameEngineInput::CreateKey("TilePointChange", 'E');
	}

	GameEngineFont::Load("휴먼둥근헤드라인");

	if (nullptr == GameEngineSprite::Find("TileMap"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");

		// TestAnimation.png

		

	}

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Sound");

		GameEngineSound::Load(NewDir.GetPlusFileName("BGMTest.mp3").GetFullPath());

		//BgmPlayer = GameEngineSound::Play("BGMTest.mp3");
	}


	if (false == GameEngineInput::IsKey("LevelChangeKey"))
	{
		GameEngineInput::CreateKey("LevelChangeKey", 'I');
	}

	GetMainCamera()->GetCamTarget()->DepthSettingOff();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	TileMapPoint = CreateActor<GameEngineActor>();
	// 캐릭터를 랜더링 하기 위한 녀석.
	Sp = TileMapPoint->CreateComponent<GameEngineSpriteRenderer>(10);
	Sp->GetTransform()->SetLocalScale({100.0f, 100.0f, 1.0f});

	Pivot = TileMapPoint->CreateComponent<GameEngineComponent>();

	Pivot->GetTransform()->SetLocalRotation({60, 0.0f, 0.0f});

	// Pivot2 = TileMapPoint->CreateComponent<GameEngineComponent>();

	//RollRender = TileMapPoint->CreateComponent<GameEngineSpriteRenderer>(10);
	//RollRender->GetTransform()->SetParent(Pivot->GetTransform());
	//RollRender->GetTransform()->SetLocalPosition({0, 200, 0});
	//RollRender->GetTransform()->SetLocalScale({100, 100, 1});



}

void TileMapLevel::Update(float _DeltaTime)
{


}