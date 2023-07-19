#include "PrecompileHeader.h"
#include "PlayerSkill.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"

PlayerSkill::PlayerSkill() 
{
}

PlayerSkill::~PlayerSkill() 
{
}
void PlayerSkill::Start()
{
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

	if (nullptr == SkillRenderer0)
	{
		SkillRenderer0 = CreateComponent<GameEngineSpriteRenderer>();
		SkillRenderer0->CreateAnimation({ .AnimationName = "MagicBoltEffect", .SpriteName = "MagicBoltEffect",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
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

	}
}
void PlayerSkill::Update(float _Delta)
{
	if (SkillName == "MagicBolt")
	{
		MagicBoltUpdate(_Delta);
	}

}
void PlayerSkill::Render(float _Delta)
{

}
void PlayerSkill::LevelChangeStart()
{
	if (nullptr == GameEngineSprite::Find("Skill"))
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

	if (nullptr == SkillRenderer0)
	{
		SkillRenderer0 = CreateComponent<GameEngineSpriteRenderer>();
		SkillRenderer0->CreateAnimation({ .AnimationName = "MagicBoltEffect", .SpriteName = "MagicBoltEffect",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true});
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
	}
}

void PlayerSkill::SetSkillName(std::string_view _Name)
{
	SkillName = _Name;
}

void PlayerSkill::MagicBoltUpdate(float _Delta)
{
	TickTime += _Delta;

	if (TickTime < 0.5f)
	{
		float4 PlayerPos1 = Player::PlayerPos;
		GetTransform()->SetWorldPosition(PlayerPos1);
		SkillRenderer1->GetTransform()->SetWorldPosition(PlayerPos1);
		ColSkill->GetTransform()->SetWorldPosition(PlayerPos1);
	}

	if (TickTime >= 0.5f)
	{
		SkillRenderer1->On();
		SkillRenderer1->GetTransform()->AddWorldPosition(float4::Left * _Delta * Speed);
		ColSkill->GetTransform()->AddWorldPosition(float4::Left * _Delta * Speed);
	}
}
