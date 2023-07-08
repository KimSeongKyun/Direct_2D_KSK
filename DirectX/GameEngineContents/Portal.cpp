#include "PrecompileHeader.h"
#include "Portal.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ObjectEnum.h"


Portal::Portal() 
{
}

Portal::~Portal() 
{
}

void Portal::Start()
{
	if (nullptr == GameEngineSprite::Find("Portal0.png"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");


		// TestAnimation.png
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}
	{
		Render0 = CreateComponent<GameEngineSpriteRenderer>();
		Render0->CreateAnimation({ .AnimationName = "Portal", .SpriteName = "Portal", .ScaleToTexture = true });
		Render0->ChangeAnimation("Portal");
	}

	{
		float4 PortalScale = Render0->GetTransform()->GetWorldScale();
		ColToPlayer = CreateComponent<GameEngineCollision>();
		ColToPlayer->SetOrder(static_cast<int>(ObjectEnum::Portal));
		ColToPlayer->GetTransform()->SetWorldScale({ PortalScale.x, 2.0f, 1.0f });
		ColToPlayer->GetTransform()->AddWorldPosition({ 0, - PortalScale.hy() + 2 });
	}

}

void Portal::Update(float _Delta)
{
	if (GameEngineInput::IsDown("Up"))
	{
		if (ColToPlayer->Collision(static_cast<int>(ObjectEnum::Player),ColType::AABBBOX2D,ColType::AABBBOX2D) != nullptr)
		{
			GameEngineCore::ChangeLevel(LevelName);
		}
	}

}

void Portal::Render(float _Delta)
{

}

void Portal::SetLevelName(const std::string_view& _LevelName)
{
	LevelName = _LevelName;
}