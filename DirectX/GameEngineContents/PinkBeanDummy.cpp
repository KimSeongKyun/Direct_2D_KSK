#include "PrecompileHeader.h"
#include "PinkBeanDummy.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

PinkBeanDummy::PinkBeanDummy() 
{
}

PinkBeanDummy::~PinkBeanDummy() 
{
}

void PinkBeanDummy::Start()
{
	ComponetSetting();
}

void PinkBeanDummy::Update(float _Delta)
{
	if (PinkBeanDummyRender->IsAnimationEnd() == true)
	{
		if (PinkBeanState == "Stand")
		{
			++StateNumber;
			ChangeState(StateNumber);
			return;
		}

		if (PinkBeanState != "Stand")
		{
			PinkBeanDummyRender->ChangeAnimation("PinkBeanStand0");
			PinkBeanState = "Stand";

			if (StateNumber == 13)
			{
				StateNumber = 1;
			}
		}
	}
}

void PinkBeanDummy::Render(float _Delta)
{

}


void PinkBeanDummy::ComponetSetting()
{
	if (PinkBeanDummyRender == nullptr)
	{
		PinkBeanDummyRender = CreateComponent<GameEngineSpriteRenderer>();
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill1", .SpriteName = "PinkBeanSkill1",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill2", .SpriteName = "PinkBeanSkill2",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill3", .SpriteName = "PinkBeanSkill3",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill4", .SpriteName = "PinkBeanSkill4",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill5", .SpriteName = "PinkBeanSkill5",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill6", .SpriteName = "PinkBeanSkill6",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill7", .SpriteName = "PinkBeanSkill7",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill8", .SpriteName = "PinkBeanSkill8",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill9", .SpriteName = "PinkBeanSkill9",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill10", .SpriteName = "PinkBeanSkill10",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill11", .SpriteName = "PinkBeanSkill11",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill12", .SpriteName = "PinkBeanSkill12",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanSkill13", .SpriteName = "PinkBeanSkill13",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->CreateAnimation({ .AnimationName = "PinkBeanStand0", .SpriteName = "PinkBeanStand0",.FrameInter = 0.15f, .ScaleToTexture = true });
		PinkBeanDummyRender->ChangeAnimation("PinkBeanStand0");
	}
}

void PinkBeanDummy::ChangeState(int _StateNum)
{
	std::string CurState = "PinkBeanSkill";
	CurState += std::to_string(_StateNum);
	PinkBeanState = CurState;

	if (CurState == "PinkBeanSkill1")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -15.0f,-5.0f });
	}

	PinkBeanDummyRender->ChangeAnimation(CurState);

}