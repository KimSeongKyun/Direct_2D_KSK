#include "PrecompileHeader.h"
#include "PlayLevelUIActor.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineButton.h>
#include "Player.h"

PlayLevelUIActor::PlayLevelUIActor() 
{
}

PlayLevelUIActor::~PlayLevelUIActor() 
{
}

void PlayLevelUIActor::Start() 
{
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	{
		// HPBar
		std::shared_ptr<GameEngineUIRenderer> Render = CreateComponent<GameEngineUIRenderer>();
		Render->GetTransform()->SetLocalPosition({-500.0f, 300.0f});
		Render->GetTransform()->SetLocalScale({300.0f, 50.0f, 1.0f});
	}

	{
		// HPBar
		ButtonDeath = CreateComponent<GameEngineUIRenderer>();
		ButtonDeath->GetTransform()->SetLocalPosition({ 500.0f, 300.0f });
		ButtonDeath->GetTransform()->SetLocalScale({ 150.0f, 150.0f, 1.0f });
	}

	{
		std::shared_ptr<GameEngineButton> Button = GetLevel()->CreateActor<GameEngineButton>(520);
		Button->GetTransform()->SetLocalPosition({ -300, 200, 1 });
		Button->GetTransform()->SetLocalScale({100, 100, 1});

		Button->SetEvent([this]() 
			{
				// nullptr 까지 다해줘야 합니다.
				if (nullptr != ButtonDeath)
				{
					this->ButtonDeath->Death();
					ButtonDeath = nullptr;
				}
				// Player::MainPlayer->TestCallBack();
			});
	}


}

void PlayLevelUIActor::Update(float _Delta) 
{

}