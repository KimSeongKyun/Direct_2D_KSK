#include "PrecompileHeader.h"
#include "Snale.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineBase/GameEngineRandom.h>

Snale::Snale()
{
}

Snale::~Snale()
{
}

void Snale::Start()
{
	if (nullptr == GameEngineSprite::Find("SnaleDIe"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		NewDir.Move("Snale");
	
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SnaleDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SnaleHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SnaleIdle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SnaleMove").GetFullPath());
	}

	Render0 = CreateComponent< GameEngineSpriteRenderer>();
	Render0->CreateAnimation({ .AnimationName = "SnaleDie", .SpriteName = "SnaleDie",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "SnaleHit", .SpriteName = "SnaleHit",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "SnaleIdle", .SpriteName = "SnaleIdle",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "SnaleMove", .SpriteName = "SnaleMove",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->ChangeAnimation("SnaleIdle");
}

void Snale::Update(float _Delta)
{
	StackTime += _Delta;
	if (StackTime < 1.5f)
	{
		if (StateString == "SnaleLeftMove")
		{
			GetTransform()->SetLocalPositiveScaleX();
			GetTransform()->AddWorldPosition(float4::Left * Speed * _Delta);
		}

		if (StateString == "SnaleRightMove")
		{
			GetTransform()->SetLocalNegativeScaleX();
			GetTransform()->AddWorldPosition(float4::Right * Speed * _Delta);
		}
	}
	if (StackTime >= 1.5f)
	{
		int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 2);

		if (RandomNum == 0)
		{
			ChangeState("SnaleIdle");
		}

		if (RandomNum == 1)
		{
			ChangeState("SnaleLeftMove");
		}


		if (RandomNum == 2)
		{
			ChangeState("SnaleRightMove");
		}

		StackTime = 0.0f;
	}



}

void Snale::Render(float _Delta)
{

}

void Snale::ChangeState(const std::string& _State)
{
	if (_State == "SnaleLeftMove" || _State == "SnaleRightMove")
	{
		Render0->ChangeAnimation("SnaleMove");
	}
	else
	{
		Render0->ChangeAnimation(_State);
	}
	StateString = _State;
}