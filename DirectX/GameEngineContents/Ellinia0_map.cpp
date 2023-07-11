#include "PrecompileHeader.h"
#include "Ellinia0_map.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>



Ellinia0_map::Ellinia0_map()
{
}

Ellinia0_map::~Ellinia0_map()
{
}

void Ellinia0_map::Start()
{
	if (nullptr == GameEngineSprite::Find("Ground"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Map");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ground").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BackGround").GetFullPath());
	}

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetTexture("ElliniaBackGround.png");
	BackGround->SetScaleToTexture("ElliniaBackGround.png");
	BackGround->GetTransform()->SetWorldPosition({ 0, 0, -1000.0f });
	Ground = CreateComponent<GameEngineSpriteRenderer>();
	Ground->SetTexture("Ellinia0.png");
	Ground->SetScaleToTexture("Ellinia0.png");
	Ground->GetTransform()->SetWorldPosition({ 0, 0, -100.0f });
	
	
}

void Ellinia0_map::Update(float _Delta)
{

}
void Ellinia0_map::Render(float _Delta)
{

}






