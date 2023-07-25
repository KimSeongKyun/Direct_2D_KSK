#include "PrecompileHeader.h"
#include "PlayerSkill.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ObjectEnum.h"
#include "Monster.h"

PlayerSkill::PlayerSkill() 
{
}

PlayerSkill::~PlayerSkill() 
{
}
void PlayerSkill::Start()
{
	
	ComponentSetting();

}
void PlayerSkill::Update(float _Delta)
{
	if (CurSkill == SkillList::MagicBolt)
	{
		MagicBoltUpdate(_Delta);
		MagicBoltColCheck();
	}

}
void PlayerSkill::Render(float _Delta)
{

}
void PlayerSkill::LevelChangeStart()
{
	ComponentSetting();

	
}

void PlayerSkill::SetSkillName(SkillList _Skill)
{
	CurSkill = _Skill;
}

void PlayerSkill::MagicBoltUpdate(float _Delta)
{
	TickTime += _Delta;

	if (TickTime < 0.5f)
	{
		if (DirectionSet == true)
		{
			DirectionSet = false;
			CurPlayerDirection = static_cast<int>(Player::CurDirection);
		}

		
		float4 PlayerPos1 = Player::PlayerPos;
		
		GetTransform()->SetLocalPosition(PlayerPos1);
	

		if (CurPlayerDirection == 0)
		{
			GetTransform()->SetLocalPositiveScaleX();
			SkillRenderer1->GetTransform()->SetLocalPosition(PlayerPos1 + float4::Left * 50.0f);
			ColSkill->GetTransform()->SetLocalPosition(PlayerPos1 + float4::Left * 50.0f);
		}
		if (CurPlayerDirection == 1)
		{
			GetTransform()->SetLocalNegativeScaleX();
			SkillRenderer1->GetTransform()->SetLocalPosition(PlayerPos1 + float4::Right * 50.0f);
			ColSkill->GetTransform()->SetLocalPosition(PlayerPos1 + float4::Right * 50.0f);
		}
	}

	if (TickTime >= 0.5f)
	{
		
		SkillRenderer1->On();
		ColSkill->On();
		
		if (CurPlayerDirection == 0)
		{
			SkillRenderer1->GetTransform()->AddWorldPosition(float4::Left * _Delta * Speed);
			ColSkill->GetTransform()->AddWorldPosition(float4::Left * _Delta * Speed);
		}
		if (CurPlayerDirection == 1)
		{
			SkillRenderer1->GetTransform()->AddWorldPosition(float4::Right * _Delta * Speed);
			ColSkill->GetTransform()->AddWorldPosition(float4::Right * _Delta * Speed);
		}

		if (SkillRenderer1->IsAnimationEnd() == true)
		{
			DirectionSet = true;
		}

	}
}

void PlayerSkill::MagicBoltColCheck()
{
	std::shared_ptr<GameEngineCollision> ColCheck = ColSkill->Collision(ObjectEnum::Monster, ColType::AABBBOX2D, ColType::AABBBOX2D);
	if (ColCheck != nullptr)
	{
		std::shared_ptr<Monster> HitMonster = ColCheck->GetActor()->DynamicThis<Monster>();
		HitMonster->Damage(10);
		ColSkill->Off();
		SkillRenderer1->Off();
		CurSkill = SkillList::None;
	}
}

void PlayerSkill::ComponentSetting()
{
	if (nullptr == SkillRenderer0)
	{
		SkillRenderer0 = CreateComponent<GameEngineSpriteRenderer>();
		SkillRenderer0->CreateAnimation({ .AnimationName = "MagicBoltEffect", .SpriteName = "MagicBoltEffect",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
		SkillRenderer0->GetTransform()->AddLocalPosition({ -50.0f, 0.0f ,0.0f });
		SkillRenderer0->ChangeAnimation("MagicBoltEffect");
		//SkillRenderer0->Off();

		SkillRenderer1 = CreateComponent<GameEngineSpriteRenderer>();
		SkillRenderer1->CreateAnimation({ .AnimationName = "MagicBoltBall", .SpriteName = "MagicBoltBall",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
		SkillRenderer1->ChangeAnimation("MagicBoltBall");
		SkillRenderer1->Off();
	}

	if (nullptr == ColSkill)
	{
		ColSkill = CreateComponent<GameEngineCollision>();
		ColSkill->GetTransform()->SetWorldScale(MagicBoltScale);
		ColSkill->Off();
	}
}