#include "PrecompileHeader.h"
#include "Ariel.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

Ariel::Ariel() 
{
}

Ariel::~Ariel() 
{
}

void Ariel::Start()
{
	ComponentSetting();
}

void Ariel::Update(float _Delta)
{
	RenderDifCheck();

	SkillTime += _Delta;

	if (SkillTime >= 8.0f)
	{
		Genesis();
		SkillTime = 0.0f;
	}
	
	if (SkillOn == true && ArielGenesis[1]->IsAnimationEnd() == true)
	{
		int a = 0;
	}
	

}
void Ariel::Render(float _Delta)
{

}

void Ariel::ComponentSetting()
{
	ArielRender = CreateComponent <GameEngineSpriteRenderer>();
	ArielRender->CreateAnimation({ .AnimationName = "ArielStand", .SpriteName = "ArielStand",.FrameInter = 0.15f, .Loop = false,.ScaleToTexture = true });
	ArielRender->CreateAnimation({ .AnimationName = "ArielDie", .SpriteName = "ArielDie",.FrameInter = 0.15f, .Loop = false,.ScaleToTexture = true });
	ArielRender->CreateAnimation({ .AnimationName = "ArielSkill1", .SpriteName = "ArielSkill1",.FrameInter = 0.15f, .Loop = false,.ScaleToTexture = true });
	ArielRender->CreateAnimation({ .AnimationName = "ArielSkill2", .SpriteName = "ArielSkill2",.FrameInter = 0.15f, .Loop = false,.ScaleToTexture = true });
	ArielRender->CreateAnimation({ .AnimationName = "ArielAttack1Effect", .SpriteName = "ArielAttack1Effect",.FrameInter = 0.15f, .Loop = false,.ScaleToTexture = true });
	ArielRender->CreateAnimation({ .AnimationName = "ArielAttack2Effect", .SpriteName = "ArielAttack2Effect",.FrameInter = 0.15f, .Loop = false,.ScaleToTexture = true });
	ArielRender->CreateAnimation({ .AnimationName = "ArielAttack1Hit", .SpriteName = "ArielAttack1Hit",.FrameInter = 0.15f,.Loop = false, .ScaleToTexture = true });
	ArielRender->CreateAnimation({ .AnimationName = "ArielAttack2Hit", .SpriteName = "ArielAttack2Hit",.FrameInter = 0.15f,.Loop = false, .ScaleToTexture = true });
	ArielRender->ChangeAnimation("ArielStand");

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineSpriteRenderer> SkillRenderer = CreateComponent<GameEngineSpriteRenderer>();
		SkillRenderer->CreateAnimation({ .AnimationName = "ArielAttack1Hit", .SpriteName = "ArielAttack1Hit",.FrameInter = 0.15f,.Loop = false, .ScaleToTexture = true });
		SkillRenderer->CreateAnimation({ .AnimationName = "ArielAttack2Hit", .SpriteName = "ArielAttack2Hit",.FrameInter = 0.15f,.Loop = false, .ScaleToTexture = true });
		SkillRenderer->GetTransform()->AddLocalPosition({ 0.0f, 90.0f });
		SkillRenderer->Off();
		ArielGenesis.push_back(SkillRenderer);
	}
	
	
}

void Ariel::Damage(int _Damge)
{

}
void Ariel::SetHP(int _HP)
{

}

void Ariel::ChangeState(std::string _State)
{
	ArielState = _State;

	if (ArielState == "ArielDie")
	{
		ArielRender->GetTransform()->AddLocalPosition({ 0.0f, -12.0f });
		ArielDif = { 0.0f, -12.0f };
	}

	if (ArielState == "ArielSkill1")
	{
		ArielRender->GetTransform()->AddLocalPosition({ 0.0f, 0.0f });
		ArielDif = { 0.0f, 0.0f };
	}

	if (ArielState == "ArielSkill2")
	{
		ArielRender->GetTransform()->AddLocalPosition({ 0.0f, 21.0f });
		ArielDif = { 0.0f, 21.0f };
	}

	if (ArielState == "ArielAttack1Effect")
	{
		ArielRender->GetTransform()->AddLocalPosition({ 0.0f, 0.0f });
		ArielDif = { 0.0f, 0.0f };
	}

	if (ArielState == "ArielAttack2Effect")
	{
		ArielRender->GetTransform()->AddLocalPosition({ 9.0f, -12.0f });
		ArielDif = { 9.0f, -12.0f };
	}

	ArielRender->ChangeAnimation(ArielState);

	
}

void Ariel::RenderDifCheck()
{
	if (ArielRender->IsAnimationEnd() == true)
	{
		if (ArielState != "ArielStand")
		{
			ArielRender->GetTransform()->AddLocalPosition(-ArielDif);
		}
	}
}

void Ariel::Genesis()
{
	SkillOn = true;

	for (size_t i = 0; i < 5; i++)
	{
		int RandomNum = GameEngineRandom::MainRandom.RandomInt(-385, 385);
		ArielGenesis[i]->On();
		ArielGenesis[i]->ChangeAnimation("ArielAttack1Hit");
		ArielGenesis[i]->GetTransform()->SetLocalPosition({ 0.0f, 90.0f,0.1f });
		ArielGenesis[i]->GetTransform()->AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });
	}

	ArielRender->ChangeAnimation("ArielAttack1Effect");
	ArielRender->SetAnimationUpdateEvent("ArielAttack1Effect", 15, {})
}