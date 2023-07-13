#include "PrecompileHeader.h"
#include "Status.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineButton.h>
#include "Player.h"

Status::Status()
{
}

Status::~Status()
{
}

void Status::Start()
{
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	if (nullptr == GameEngineSprite::Find("Status"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("UI");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Status").GetFullPath());
		{
			BackHP = CreateComponent<GameEngineUIRenderer>();
			BackHP->SetTexture("AniGauge.png");
			BackHP->SetScaleToTexture("AniGauge.png");
			BackHP->GetTransform()->SetLocalPosition({ 10.0f, -2.0f, 1.0f });
		}

		{
			BackMP = CreateComponent<GameEngineUIRenderer>();
			BackMP->SetTexture("AniGauge.png");
			BackMP->SetScaleToTexture("HPBar.png");
			BackMP->GetTransform()->SetLocalPosition({ 10.0f, -17.0f, 1.0f });
		}

		{
			//34
			HPBar = CreateComponent<GameEngineUIRenderer>();
			HPBar->SetTexture("HPBar.png");
			HPBar->SetScaleToTexture("HPBar.png");
			HPBar->GetTransform()->SetLocalPosition({ 10.0f, -2.0f, 1.0f });
		}

		{
			//51
			MPBar = CreateComponent<GameEngineUIRenderer>();
			MPBar->SetTexture("MPBar.png");
			MPBar->SetScaleToTexture("MPBar.png");
			MPBar->GetTransform()->SetLocalPosition({ 10.0f, -17.0f, 1.0f });
		}

		{
			// Status 백그라운드
			StatusBack = CreateComponent<GameEngineUIRenderer>();
			StatusBack->SetTexture("StatusLayer.png");
			StatusBack->SetScaleToTexture("StatusLayer.png");	
		}

		

		

	}
	//{
	//	// HPBar
	//	ButtonDeath = CreateComponent<GameEngineUIRenderer>();
	//	ButtonDeath->GetTransform()->SetLocalPosition({ 500.0f, 300.0f });
	//	ButtonDeath->GetTransform()->SetLocalScale({ 150.0f, 150.0f, 1.0f });
	//}

	//{
	//	std::shared_ptr<GameEngineButton> Button = GetLevel()->CreateActor<GameEngineButton>(520);
	//	Button->GetTransform()->SetLocalPosition({ -300, 200, 1 });
	//	Button->GetTransform()->SetLocalScale({100, 100, 1});

	//	Button->SetEvent([this]() 
	//		{
	//			// nullptr 까지 다해줘야 합니다.
	//			if (nullptr != ButtonDeath)
	//			{
	//				this->ButtonDeath->Death();
	//				ButtonDeath = nullptr;
	//			}
	//			// Player::MainPlayer->TestCallBack();
	//		});
	//}


}

void Status::Update(float _Delta)
{

}