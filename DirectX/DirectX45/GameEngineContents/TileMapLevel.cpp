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

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("FOGWAR.png").GetFullPath(), 3, 1);

	}

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Sound");

		GameEngineSound::Load(NewDir.GetPlusFileName("BGMTest.mp3").GetFullPath());

		BgmPlayer = GameEngineSound::Play("BGMTest.mp3");
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

	RollRender = TileMapPoint->CreateComponent<GameEngineSpriteRenderer>(10);
	RollRender->GetTransform()->SetParent(Pivot->GetTransform());
	RollRender->GetTransform()->SetLocalPosition({0, 200, 0});
	RollRender->GetTransform()->SetLocalScale({100, 100, 1});

	RollRender2 = TileMapPoint->CreateComponent<GameEngineSpriteRenderer>(10);
	RollRender2->GetTransform()->SetParent(RollRender->GetTransform());
	RollRender2->GetTransform()->SetLocalPosition({ 0, 1.5f, 0 });
	RollRender2->GetTransform()->SetLocalScale({ 1, 1, 1 });

	// RollRender2->GetTransform()->SetWorldPosition({ 100, 100, 0 });
	// RollRender2->GetTransform()->SetWorldScale({ 100, 100, 100 });
	

	//std::shared_ptr<GameEngineFontRenderer> FontRender = TileMapPoint->CreateComponent<GameEngineFontRenderer>(300);
	//FontRender->SetFont("휴먼둥근헤드라인");
	//FontRender->SetText("죄송합니다~~~~~");
	//FontRender->SetScale(100.0f);


	// Sp->GetTransform()->SetLocalScale({ 10.0f, 10, 1.0f });

	if (nullptr == GameEngineSprite::Find("PlayerRun"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PlayerRun").GetFullPath());
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Test\\TestAnimation.png").GetFullPath(), 3, 5);
	}

	//if (nullptr != Sp)
	//{
	//	// Sp = TileMapPoint->CreateComponent<GameEngineSpriteRenderer>();
	//	Sp->CreateAnimation({ .AnimationName = "Run", .SpriteName = "PlayerRun", .ScaleToTexture = true });
	//	Sp->CreateAnimation({ "Win", "TestAnimation.png", 0, 5, 0.1f, true, true });
	//	Sp->SetScaleRatio(5.0f);
	//	Sp->ChangeAnimation("Win");
	//	// Sp->ImageClipping(0.3f);
	//}

	std::shared_ptr<GameEngineActor> NewGame = CreateActor<GameEngineActor>();
	TileMap = NewGame->CreateComponent<GameEngineTileMapRenderer>();

	TileMap->CreateTileMap(10, 10, { 100, 50 }, { 100 * 1.2f, 50 * 1.2f}, TileMapMode::Iso);

	for (size_t y = 0; y < TileMap->GetCount().y; y++)
	{
		for (size_t x = 0; x < TileMap->GetCount().x; x++)
		{
			TileMap->SetTile(static_cast<int>(x), static_cast<int>(y), "FOGWAR.png", 0);
		}
	}

}

void TileMapLevel::Update(float _DeltaTime)
{
	static float Test = 0.0f;

	Test -= _DeltaTime * 180.0f;

	//Sp->ImageClippingY(Test, ClipYDir::Top);
	
	Pivot->GetTransform()->AddLocalRotation({0,0,_DeltaTime * 180.0f});

	RollRender->GetTransform()->SetWorldRotation({ 0, 0, Test });

	// RollRender->GetTransform()->SetWorldPosition({ 100, 100, 0 });

	if (true == GameEngineInput::IsDown("LevelChangeKey"))
	{
		BgmPlayer.Stop();
		// GameEngineCore::ChangeLevel("PlayLevel");
	}

	float Speed = 100.f;

	if (true == GameEngineInput::IsPress("TilePointLeft"))
	{
		TileMapPoint->GetTransform()->AddLocalPosition(float4::Left * _DeltaTime * Speed);
	}

	if (true == GameEngineInput::IsPress("TilePointRight"))
	{
		TileMapPoint->GetTransform()->AddLocalPosition(float4::Right * _DeltaTime * Speed);
	}

	if (true == GameEngineInput::IsPress("TilePointUp"))
	{
		TileMapPoint->GetTransform()->AddLocalPosition(float4::Up * _DeltaTime * Speed);
	}

	if (true == GameEngineInput::IsPress("TilePointDown"))
	{
		TileMapPoint->GetTransform()->AddLocalPosition(float4::Down * _DeltaTime * Speed);
	}

	if (true == GameEngineInput::IsDown("TilePointChange"))
	{
		TileMap->SetTile(TileMapPoint->GetTransform()->GetWorldPosition(), "FOGWAR.png", 2);
	}

}