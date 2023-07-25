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
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineActor.h>

#include "KSKSpriteRenderer.h"

#include "ObjectEnum.h"
#include "Monster.h"
#include "PlayerSkill.h"

Player* Player::MainPlayer = nullptr;
float4 Player::PlayerPos = { 0.0f, 0.0f, 0.0f };
PlayerDirection Player::CurDirection = PlayerDirection::Left;

Player::Player()
{
	MainPlayer = this;
}

Player::~Player()
{
}

void Player::Start()
{
	StateInit();
}

void Player::Update(float _DeltaTime)
{
	PlayerPos = GetTransform()->GetWorldPosition();
	float4 CurCameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 CameraScale = GameEngineWindow::GetScreenSize();
	float4 MapScale = CurMap->GetScale();
	float LeftEnd = -MapScale.hx() + CameraScale.hx();
	float RightEnd = MapScale.hx() - CameraScale.hx();
	float UpEnd = MapScale.hy() - CameraScale.hy();
	float DownEnd = -MapScale.hy() + CameraScale.hy();

	FSM.Update(_DeltaTime);

	float4 NextCameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();

	if (RightEnd < NextCameraPos.x || NextCameraPos.x < LeftEnd )
	{
		NextCameraPos = { CurCameraPos.x, NextCameraPos.y, NextCameraPos.z };
		GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(NextCameraPos);
	}

	if (UpEnd < NextCameraPos.y || NextCameraPos.y < DownEnd)
	{
		NextCameraPos = { NextCameraPos.x,  CurCameraPos.y, NextCameraPos.z };
		GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(NextCameraPos);
	}

	if (GameEngineInput::IsDown("QSkill"))
	{
		MagicBolt();
	}
	

	if (SkillOn == true)
	{
		SkillTime += _DeltaTime;

		if (SkillTime >= MaxSkillTime != 0.0f)
		{
			Skill0->Death();
			Skill0 = nullptr;
			SkillTime = 0.0f;
			SkillOn = false;
		}
	}
		
}



// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
	// GetTransform()->AddLocalRotation({0.0f, 0.0f, 360.0f * _Delta});
};

void Player::LevelChangeStart()
{
	if (false == GameEngineInput::IsKey("MoveLeft"))
	{
		GameEngineInput::CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("Up", VK_UP);
		GameEngineInput::CreateKey("Down", VK_DOWN);

		GameEngineInput::CreateKey("Swing", 'Z');
		GameEngineInput::CreateKey("Jump", 'X');
		GameEngineInput::CreateKey("QSkill", 'Q');
	}

	PlayerHalfValue = { GetTransform()->GetWorldScale().hx(), GetTransform()->GetWorldScale().hy() };

	ComponentSetting();
}
void Player::RendererStateChange(const std::string _State)
{
	if (CurPlayerState == _State)
	{
		return;
	}
	CurPlayerState = _State;
	
	

	if (_State == "Swing")
	{	
		int SwingNum = GameEngineRandom::MainRandom.RandomInt(0, 2);

		if (SwingNum == 0)
		{
			Body->ChangeAnimation(_State + "0");
		}

		if (SwingNum == 1)
		{
			Body->ChangeAnimation(_State + "1");
		}

		if (SwingNum == 2)
		{
			Body->ChangeAnimation(_State + "2");
		}
	}
	if (_State != "Swing")
	{
		Body->ChangeAnimation(_State);
	}
}

void Player::TestCallBack()
{
	MsgTextBox("됩니다");
}

void Player::SetCurMapScale(float4 _MapScale)
{
	CurMapScale = _MapScale;
}

void Player::GravityCheck(float _DeltaTime)
{
	if(PlayerGravity == true)
	{
		Gravity += 10 * _DeltaTime;

		if (Gravity > 5.0f)
		{
			Gravity = 5.0f;
		}

		float4 CurPosition = GetTransform()->GetWorldPosition();
		GetTransform()->AddWorldPosition(float4::Down * Gravity);

		float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };
		float4 NextPosition = CurPosition + (float4::Down * Gravity);

		if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
		{
			GetTransform()->SetWorldPosition(CurPosition);
			PlayerGravity = false;
			Gravity = 0.0f;
		}
	}
}

void  Player::LRColCheck(float _DeltaTime, float4 _LeftOrRight)
{
	float4 CurPosition = GetTransform()->GetWorldPosition();
	float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };

	GetTransform()->AddWorldPosition(_LeftOrRight * Speed * _DeltaTime);

	float4 NextPosition = CurPosition + _LeftOrRight * Speed * _DeltaTime;
	if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
	{
		for (float i = 1.0f; i <= 5.0f; i += _DeltaTime)
		{
			NextPosition += float4::Up * i;
			if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() - i + (int)PlayerSize.hy() - NextPosition.iy()) != ColColor)
			{
				GetTransform()->SetWorldPosition(NextPosition);
				break;
			}

			if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() - i + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
			{
				if (i == 5.0f)
				{
					GetTransform()->SetWorldPosition(CurPosition);
				}
				continue;
			}
		}
	}
}

void Player::RopeCheck()
{
	std::shared_ptr<GameEngineCollision> isColRope = ColRope->Collision(static_cast<int>(ObjectEnum::Rope), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (isColRope != nullptr)
	{
		float4 PlayerPos = GetTransform()->GetWorldPosition();
		float4 RopePos = ColRope->GetTransform()->GetWorldPosition();
		GetTransform()->SetWorldPosition({ RopePos.x, PlayerPos.y,PlayerPos.z });

		FSM.ChangeState("Rope");
	}
}

void Player::Attack()
{
	std::shared_ptr<GameEngineCollision> Attack = ColAttack->Collision(static_cast<int>(ObjectEnum::Monster), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Attack == nullptr)
	{
		return;
	}

	if (Attack != nullptr)
	{
		std::shared_ptr<Monster> ColMonster = Attack->GetActor()->DynamicThis<Monster>();

		ColMonster->Damage(10);
	}
}
void Player::MagicBolt()
{
	if (Skill0 == nullptr)
	{
		Skill0 = GetLevel()->CreateActor<PlayerSkill>();
		Skill0->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		Skill0->SetSkillName(SkillList::MagicBolt);
		RendererStateChange("Swing");
		MaxSkillTime = 1.0f;
		SkillOn = true;
	}
}

void Player::ComponentSetting()
{
	if (nullptr == Body)
	{
		Body = CreateComponent< GameEngineSpriteRenderer>();
		Body->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Idle",.FrameInter = 0.2f, .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "Move", .SpriteName = "Move",.FrameInter = 0.2f, .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "Jump",.FrameInter = 0.2f, .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "Swing0", .SpriteName = "Swing0",.FrameInter = 0.2f, .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "Swing1", .SpriteName = "Swing1",.FrameInter = 0.2f, .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "Swing2", .SpriteName = "Swing2",.FrameInter = 0.2f, .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "Rope", .SpriteName = "Rope",.FrameInter = 0.2f, .ScaleToTexture = true });
		Body->CreateAnimation({ .AnimationName = "Ladder", .SpriteName = "Ladder",.FrameInter = 0.2f, .ScaleToTexture = true });
		Body->ChangeAnimation("Idle");

		{
			ColRope = CreateComponent<GameEngineCollision>();
			ColRope->GetTransform()->SetLocalScale({ 20.0f, 64.0f, 100.0f });
			ColRope->SetOrder(static_cast<int>(ObjectEnum::Player));
		}

		{
			ColAttack = CreateComponent<GameEngineCollision>();
			ColAttack->GetTransform()->SetLocalScale(PlayerSize);
			ColAttack->GetTransform()->AddLocalPosition({ -PlayerSize.x, 0.0f });
			ColAttack->SetOrder(static_cast<int>(ObjectEnum::Player));
		}
	}
}