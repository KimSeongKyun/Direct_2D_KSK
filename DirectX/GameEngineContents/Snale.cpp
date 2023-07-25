#include "PrecompileHeader.h"
#include "Snale.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Monster.h"
#include "Player.h"
#include "ObjectEnum.h"


Snale::Snale()
{
}

Snale::~Snale()
{
}

void Snale::Start()
{
	ResourceRoad();


	Render0 = CreateComponent< GameEngineSpriteRenderer>();
	Render0->CreateAnimation({ .AnimationName = "SnaleDie", .SpriteName = "SnaleDie",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "SnaleHit", .SpriteName = "SnaleHit",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "SnaleIdle", .SpriteName = "SnaleIdle",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "SnaleMove", .SpriteName = "SnaleMove",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->ChangeAnimation("SnaleIdle");

	ColBody = CreateComponent<GameEngineCollision>();
	ColBody->GetTransform()->SetWorldScale(SnaleSize);
	ColBody->SetOrder(static_cast<int>(ObjectEnum::Monster));

	SetMonsterSize(SnaleSize);
	SetHP(100);
}

void Snale::Update(float _Delta)
{


	StackTime += _Delta;

	if (IsKnockBack() == false)
	{
		GravityCheck(_Delta);

		if (IsGravity() == false)
		{
			if (StackTime < 1.5f)
			{
				float4 CurPos = GetTransform()->GetWorldPosition();
				float4 ColMapDif = { GetColMap()->GetScale().hx(),GetColMap()->GetScale().hy() };

				if (StateString == "SnaleLeftMove")
				{
					float4 NextPosition = CurPos + (float4::Left * Speed * _Delta);
					GetTransform()->SetLocalPositiveScaleX();
					GetTransform()->AddWorldPosition(float4::Left * Speed * _Delta);

					if (GetColMap()->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)SnaleSize.hy() - NextPosition.iy(), GetWallColor()) == GetWallColor())
					{
						GetTransform()->SetWorldPosition(CurPos);

					}

				}

				if (StateString == "SnaleRightMove")
				{
					float4 NextPosition = CurPos + (float4::Right * Speed * _Delta);
					GetTransform()->SetLocalNegativeScaleX();
					GetTransform()->AddWorldPosition(float4::Right * Speed * _Delta);

					if (GetColMap()->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)GetMonsterSize().hy() - NextPosition.iy(), GetWallColor()) == GetWallColor())
					{
						GetTransform()->SetWorldPosition(CurPos);

					}
				}
			}
			if (IsGravity() == false && StackTime >= 1.5f)
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
	}

	if (IsKnockBack() == true)
	{
		
		ChangeState("SnaleHit");

		TickTime += _Delta;

		if (TickTime >= 1.0f)
		{
			ChangeState("SnaleIdle");
			ChangeKnockBack();
				
			StackTime = 1.5f;
			TickTime = 0.0f;
		}

		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		float4 SnalePos = GetTransform()->GetWorldPosition();

		float KnockBackDirection = SnalePos.x - PlayerPos.x;

		if (TickTime < 0.5f)
		{
			if (KnockBackDirection > 0.0f)
			{
				GetTransform()->SetLocalNegativeScaleX();
				GetTransform()->AddWorldPosition(float4::Right * Speed * _Delta);
			}

			if (KnockBackDirection <= 0.0f)
			{
				GetTransform()->SetLocalPositiveScaleX();
				GetTransform()->AddWorldPosition(float4::Left * Speed * _Delta);
			}
		}


	}


}

void Snale::Render(float _Delta)
{

}

void Snale::Damage(int _Damage)
{
	if(IsKnockBack() == false)
	{
		ChangeKnockBack();
	}
	

	HP -= _Damage;


	if (HP <= 0)
	{
		ChangeState("SnaleDie");

		Death();
	}
}

void Snale::SetHP(int _HP)
{
	HP = _HP;
}

void Snale::ChangeState(const std::string& _State)
{
	if (StateString == _State)
	{
		return;
	}

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

void Snale::ResourceRoad()
{
	if (nullptr == GameEngineSprite::Find("SnaleDie"))
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
}