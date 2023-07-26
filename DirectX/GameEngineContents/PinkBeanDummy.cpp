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
			PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -ResourceDif.x, -ResourceDif.y });
			PinkBeanState = "Stand";

			if (StateNumber == 12)
			{
				StateNumber = 0;
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
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -16.0f,-5.0f });
		ResourceDif = { -16.0f,-5.0f };
	}

	if (CurState == "PinkBeanSkill2")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -48.0f,0.0f });
		ResourceDif = { -48.0f,0.0f };
	}

	if (CurState == "PinkBeanSkill3")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -30.0f, -8.0f });
		ResourceDif = { -30.0f, -8.0f };
	}

	if (CurState == "PinkBeanSkill4")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -3.0f, 2.0f });
		ResourceDif = { -3.0f, 2.0f };
	}

	if (CurState == "PinkBeanSkill5")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -1.0f, 26.0f });
		ResourceDif = { -1.0f, 26.0f };
	}

	if (CurState == "PinkBeanSkill6")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -5.0f, 7.0f });
		ResourceDif = { -5.0f, 7.0f };
	}

	if (CurState == "PinkBeanSkill7")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -34.0f, 21.0f });
		ResourceDif = { -34.0f, 21.0f };
	}

	if (CurState == "PinkBeanSkill8")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -20.0f, -5.0f });
		ResourceDif = { -20.0f, -5.0f };
	}

	if (CurState == "PinkBeanSkill9")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -20.0f, -5.0f });
		ResourceDif = { -20.0f, -5.0f };
	}

	if (CurState == "PinkBeanSkill10")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -35.0f, 21.0f });
		ResourceDif = { -35.0f, 21.0f };
	}
	
	if (CurState == "PinkBeanSkill11")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -30.0f, -8.0f });
		ResourceDif = { -30.0f, -8.0f };
	}
	if (CurState == "PinkBeanSkill12")
	{
		PinkBeanDummyRender->GetTransform()->AddLocalPosition({ -5.0f, 7.0f });
		ResourceDif = { -5.0f, 7.0f };
	}

	PinkBeanDummyRender->ChangeAnimation(CurState);

}