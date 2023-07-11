#include "PrecompileHeader.h"
#include "Ellinia1_map.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>


Ellinia1_map::Ellinia1_map() 
{
}

Ellinia1_map::~Ellinia1_map() 
{
}

void Ellinia1_map::Start()
{
	if (nullptr == GameEngineSprite::Find("Ground"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Map");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ground").GetFullPath());
	}

	Ground = CreateComponent<GameEngineSpriteRenderer>();
	Ground->SetTexture("Ellinia1.png");
	Ground->SetScaleToTexture("Ellinia1.png");
	Ground->GetTransform()->SetWorldPosition({ 0, 0, -100.0f });
}
void Ellinia1_map::Update(float _Delta)
{

}
void Ellinia1_map::Render(float _Delta)
{

}