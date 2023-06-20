#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "TestObject.h"
#include "MyContentSpriteRenderer.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	MainPlayer = this;
}

Player::~Player()
{
}


void Player::Update(float _DeltaTime)
{
	if (1.0f <= GetLiveTime())
	{
		SubRender->SetFlipX();
		ResetLiveTime();
	}

	FSM.Update(_DeltaTime);
	// Pivot2->GetTransform()->AddLocalRotation({0.0f, 90.0f * _DeltaTime, 0.0f});
//	SubRender->GetTransform()->SetWorldRotation(float4::Zero);
}

void Player::Start()
{
	if (false == GameEngineInput::IsKey("PlayerMoveLeft"))
	{
		GameEngineInput::CreateKey("PlayerMoveLeft", 'A');
		GameEngineInput::CreateKey("PlayerMoveRight", 'D');
		GameEngineInput::CreateKey("PlayerMoveUp", 'Q');
		GameEngineInput::CreateKey("PlayerMoveDown", 'E');
		GameEngineInput::CreateKey("PlayerMoveForward", 'W');
		GameEngineInput::CreateKey("PlayerMoveBack", 'S');

		GameEngineInput::CreateKey("PlayerScaleY+", 'Y');
		GameEngineInput::CreateKey("PlayerScaleY-", 'U');
		GameEngineInput::CreateKey("PlayerScaleZ+", 'H');
		GameEngineInput::CreateKey("PlayerScaleZ-", 'J');
		GameEngineInput::CreateKey("PlayerScaleX+", 'N');
		GameEngineInput::CreateKey("PlayerScaleX-", 'M');


		GameEngineInput::CreateKey("PlayerRotY+", VK_NUMPAD1);
		GameEngineInput::CreateKey("PlayerRotY-", VK_NUMPAD2);
		GameEngineInput::CreateKey("PlayerRotZ+", VK_NUMPAD4);
		GameEngineInput::CreateKey("PlayerRotZ-", VK_NUMPAD5);
		GameEngineInput::CreateKey("PlayerRotX+", VK_NUMPAD7);
		GameEngineInput::CreateKey("PlayerRotX-", VK_NUMPAD8);
		GameEngineInput::CreateKey("PlayerSpeedBoost", VK_LSHIFT);
	}


	StateInit();
}

// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
	// GetTransform()->AddLocalRotation({0.0f, 0.0f, 360.0f * _Delta});
};

void Player::LevelChangeStart() 
{

	if (nullptr == GameEngineSprite::Find("PlayerRun"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");

		// TestAnimation.png

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PlayerRun").GetFullPath());

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Test\\TestAnimation.png").GetFullPath(), 3, 5);

		// std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
	}

	if (nullptr == MainRenderer)
	{
		MainRenderer = CreateComponent<MyContentSpriteRenderer>();
		MainRenderer->CreateAnimation({ .AnimationName = "Run", .SpriteName = "PlayerRun", .ScaleToTexture = true });
		MainRenderer->CreateAnimation({ "Win", "TestAnimation.png", 0, 5, 0.1f, true, true });
		MainRenderer->SetAnimationStartEvent("Win", 0, [this]
			{
				int a = 0;

				//std::shared_ptr<TestObject> Actor = GetLevel()->CreateActor<TestObject>();
				//Actor->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
				//Actor->GetTransform()->SetLocalScale({100.0f, 100.0f, 1.0f});
			});

		MainRenderer->SetScaleRatio(5.0f);
		MainRenderer->ChangeAnimation("Win");

		{
			Collsion = CreateComponent<GameEngineCollision>();
			Collsion->GetTransform()->SetLocalScale({ 10.0f, 100.0f, 100.0f });
			Collsion->SetOrder(3000);
		}

	}

	{
		Pivot = CreateComponent<GameEngineComponent>();
		Pivot->GetTransform()->SetLocalRotation({15.0f, 0.0f, 0.0f});

		Pivot2 = CreateComponent<GameEngineComponent>();
		// Pivot2->GetTransform()->SetLocalRotation({ 45.0f, 0.0f, 0.0f });

		Pivot2->GetTransform()->SetParent(Pivot->GetTransform());

		SubRender = CreateComponent<GameEngineSpriteRenderer>();
		SubRender->GetTransform()->SetParent(Pivot2->GetTransform());
		SubRender->GetTransform()->AddLocalScale({80.0f, 80.0f, 1.0f});
		SubRender->GetTransform()->AddLocalPosition({200.0f, 0.0f, 0.0f});

	}

	// MainRenderer->SetScaleToTexture("Test.png");

	// 리소스 로드를 해야할 것이다.
}

void Player::TestCallBack()
{
	MsgTextBox("됩니다");
}