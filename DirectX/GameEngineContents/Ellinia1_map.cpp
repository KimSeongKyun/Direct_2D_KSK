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
	
}
void Ellinia1_map::Update(float _Delta)
{

}
void Ellinia1_map::Render(float _Delta)
{

}

void Ellinia1_map::ComponentSetting()
{
	Ground = CreateComponent<GameEngineSpriteRenderer>();
	Ground->SetTexture("Ellinia1.png");
	Ground->SetScaleToTexture("Ellinia1.png");
	Ground->GetTransform()->SetWorldPosition({ 0, 0, -100.0f });
}