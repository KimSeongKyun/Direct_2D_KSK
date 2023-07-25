#include "PrecompileHeader.h"
#include "PinkBeanMap.h"


#include <GameEngineCore/GameEngineSpriteRenderer.h>

PinkBeanMap::PinkBeanMap() 
{
}

PinkBeanMap::~PinkBeanMap() 
{
}

void PinkBeanMap::Start()
{
	ComponentSetting();
}
void PinkBeanMap::Update(float _Delta)
{

}
void PinkBeanMap::Render(float _Delta)
{

}



void PinkBeanMap::ComponentSetting()
{
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetTexture("PinkBeanBackGround.png");
	BackGround->SetScaleToTexture("PinkBeanBackGround.png");
	BackGround->GetTransform()->SetWorldPosition({ 0, 0, -1000.0f });
	Ground = CreateComponent<GameEngineSpriteRenderer>();
	Ground->SetTexture("PinkBeanMap.png");
	Ground->SetScaleToTexture("PinkBeanMap.png");
	Ground->GetTransform()->SetWorldPosition({ 0, 0, -100.0f });
}