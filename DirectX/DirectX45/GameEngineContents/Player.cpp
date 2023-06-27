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

	

	FSM.Update(_DeltaTime);
	// Pivot2->GetTransform()->AddLocalRotation({0.0f, 90.0f * _DeltaTime, 0.0f});
	//	SubRender->GetTransform()->SetWorldRotation(float4::Zero);
}

void Player::Start()
{
	if (false == GameEngineInput::IsKey("PlayerMoveLeft"))
	{
		GameEngineInput::CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("Up", VK_UP);
		GameEngineInput::CreateKey("Down", VK_DOWN);

		GameEngineInput::CreateKey("Swing", VK_LCONTROL);
		GameEngineInput::CreateKey("Jump", VK_LMENU);

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

	if (nullptr == GameEngineSprite::Find("ArmIdle"))
	{
		GameEngineDirectory NewDir;
		
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Player");
		NewDir.Move("Arm");
		// TestAnimation.png

		//GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArmDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArmIdle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArmJump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArmMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArmSwing0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArmSwing1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArmSwing2").GetFullPath());
	
		NewDir.MoveParent();

		

		NewDir.Move("Body");
		//GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodyDown").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodyRope").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodyClimb").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodyIdle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodyJump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodyMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodySwing0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodySwing1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BodySwing2").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("Head");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Back").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Front").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("LHand");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LHandJump").GetFullPath());
		NewDir.MoveParent();
		NewDir.Move("RHand");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RHandJump").GetFullPath());

		// std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
	}

	if (nullptr == Body)
	{
		

		Body = CreateComponent<GameEngineSpriteRenderer>();
		Body->CreateAnimation({ .AnimationName = "BodyMove", .SpriteName = "BodyMove", .ScaleToTexture = true  });
		Body->CreateAnimation({ .AnimationName = "BodySwing0", .SpriteName = "BodySwing0", .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "BodySwing1", .SpriteName = "BodySwing1", .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "BodySwing2", .SpriteName = "BodySwing2", .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "BodyIdle", .SpriteName = "BodyIdle",.FrameInter = 0.4f, .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "BodyJump", .SpriteName = "BodyJump", .ScaleToTexture = true });
		//Body->CreateAnimation({ .AnimationName = "BodyDown", .SpriteName = "BodyDown", .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "BodyRope", .SpriteName = "BodyRope", .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "BodyClimb", .SpriteName = "BodyClimb", .ScaleToTexture = true }); 
		Body->ChangeAnimation("BodyIdle");
		Body->SetAnimationUpdateEvent("BodyIdle", 0, [this]() {Body->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + IdleBody0); });
		Body->SetAnimationUpdateEvent("BodyIdle", 1, [this]() {Body->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + IdleBody1); });
		Body->SetAnimationUpdateEvent("BodyIdle", 2, [this]() {Body->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + IdleBody2); });
		Body->SetAnimationUpdateEvent("BodyIdle", 3, [this]() {Body->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + IdleBody3); });
		
		

		Arm = CreateComponent<GameEngineSpriteRenderer>();
		Arm->CreateAnimation({ .AnimationName = "ArmSwing0", .SpriteName = "ArmSwing0", .ScaleToTexture = true });
		Arm->CreateAnimation({ .AnimationName = "ArmSwing1", .SpriteName = "ArmSwing1", .ScaleToTexture = true });
		Arm->CreateAnimation({ .AnimationName = "ArmSwing2", .SpriteName = "ArmSwing2", .ScaleToTexture = true });
		Arm->CreateAnimation({ .AnimationName = "ArmIdle", .SpriteName = "ArmIdle",.FrameInter = 0.4f,.ScaleToTexture = true });
		Arm->CreateAnimation({ .AnimationName = "ArmJump", .SpriteName = "ArmJump", .ScaleToTexture = true });
		Arm->CreateAnimation({ .AnimationName = "ArmMove", .SpriteName = "ArmMove", .ScaleToTexture = true });
		Arm->ChangeAnimation("ArmIdle");
		Arm->SetAnimationUpdateEvent("ArmIdle", 0, [this]() {Arm->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + IdleArm0); });
		Arm->SetAnimationUpdateEvent("ArmIdle", 1, [this]() {Arm->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + IdleArm0); });
		Arm->SetAnimationUpdateEvent("ArmIdle", 2, [this]() {Arm->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + IdleArm0); });
		Arm->SetAnimationUpdateEvent("ArmIdle", 3, [this]() {Arm->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + IdleArm0); });
		//Arm->CreateAnimation({ .AnimationName = "ArmDown", .SpriteName = "ArmDown", .ScaleToTexture = true });

		Head = CreateComponent<GameEngineSpriteRenderer>();
		Head->CreateAnimation({ .AnimationName = "Front", .SpriteName = "Front", .ScaleToTexture = true });
		Head->CreateAnimation({ .AnimationName = "Back", .SpriteName = "Back", .ScaleToTexture = true });
		Head->ChangeAnimation("Front");
		Head->SetAnimationUpdateEvent("Front", 0, [this]() {Head->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + IdleHead); });

		LHand = CreateComponent<GameEngineSpriteRenderer>();
		LHand->CreateAnimation({ .AnimationName = "LHandJump", .SpriteName = "LHandJump", .ScaleToTexture = true });
		LHand->ChangeAnimation("LHandJump");
		LHand->Off();
		RHand = CreateComponent<GameEngineSpriteRenderer>();
		RHand->CreateAnimation({ .AnimationName = "RHandJump", .SpriteName = "RHandJump", .ScaleToTexture = true });
		RHand->ChangeAnimation("RHandJump");
		RHand->Off();


		/*Body->GetTransform()->AddLocalPosition({ -3.0f, -17.0f});
		Head->GetTransform()->AddLocalPosition({ { 0.0f, 14.0f } });
		Arm->GetTransform()->AddLocalPosition({ { 7.0f, -12.0f } });*/
		

		{
			Collsion = CreateComponent<GameEngineCollision>();
			Collsion->GetTransform()->SetLocalScale({ 10.0f, 100.0f, 100.0f });
			Collsion->SetOrder(3000);
		}

	}

	{
		//Pivot = CreateComponent<GameEngineComponent>();
		//Pivot->GetTransform()->SetLocalRotation({15.0f, 0.0f, 0.0f});

		//Pivot2 = CreateComponent<GameEngineComponent>();
		//// Pivot2->GetTransform()->SetLocalRotation({ 45.0f, 0.0f, 0.0f });

		//Pivot2->GetTransform()->SetParent(Pivot->GetTransform());

		//SubRender = CreateComponent<GameEngineSpriteRenderer>();
		//SubRender->GetTransform()->SetParent(Pivot2->GetTransform());
		//SubRender->GetTransform()->AddLocalScale({80.0f, 80.0f, 1.0f});
		//SubRender->GetTransform()->AddLocalPosition({200.0f, 0.0f, 0.0f});

	}

	// MainRenderer->SetScaleToTexture("Test.png");

	// 리소스 로드를 해야할 것이다.

	
}

void Player::CreateAnimaionPlayer(const std::string _State)
{
	if (_State == "Idle")
	{
		Head->ChangeAnimation("Head" + _State);
		Body->ChangeAnimation("Body" + _State);
		Arm->ChangeAnimation("LArm" + _State);
		LHand->Off();
		RHand->Off();
	}
	if (_State == "Move")
	{
		Head->ChangeAnimation("Head" + _State);
		Body->ChangeAnimation("Body" + _State);
		Arm->ChangeAnimation("LArm" + _State);
		LHand->Off();
		RHand->Off();
	}
	if (_State == "Jump")
	{
		Head->ChangeAnimation("Head" + _State);
		Body->ChangeAnimation("Body" + _State);
		Arm->ChangeAnimation("LArm" + _State);
		LHand->ChangeAnimation("LHand" + _State);
		RHand->ChangeAnimation("RHand" + _State);

	}
	if (_State == "Rope")
	{
		Head->ChangeAnimation("Head" + _State);
		Body->ChangeAnimation("Body" + _State);
		Arm->Off();
		LHand->Off();
		RHand->Off();
	}
	if (_State == "Swing")
	{
		Head->ChangeAnimation("Head" + _State);
		Body->ChangeAnimation("Body" + _State);
		Arm->ChangeAnimation("LArm" + _State);
		LHand->Off();
		RHand->Off();
	}
	if (_State == "Climb")
	{

		Head->ChangeAnimation("Head" + _State);
		Body->ChangeAnimation("Body" + _State);
		Arm->Off();
		LHand->Off();
		RHand->Off();
	}
}

void Player::TestCallBack()
{
	MsgTextBox("됩니다");
}



