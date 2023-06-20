#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "TestObject.h"


void Player::StateInit() 
{
	FSM.CreateState(
		{
			.Name = "FreeMove",
			.Start = [this]()
		{
			// this->MainRenderer->ChangeAnimation();

			// int a = 0;
		},
			.Update = [this](float _DeltaTime)
		{


			// 한가지 상태를 뭘로 처리할거냐?
			// 클래스로 하면 클래스로
			// 함수포인터로 할수 있다.
			// 

			//GameEngineTextureSetter* Tex = MainRenderer->GetShaderResHelper().GetTextureSetter("DiffuseTex");
			//std::string Name = Tex->Res->GetNameToString();


			float RotSpeed = 10.0f;

			float Speed = 200.0f;

			if (true == GameEngineInput::IsPress("PlayerSpeedBoost"))
			{
				Speed = 500.0f;
			}

			if (true == GameEngineInput::IsDown("PlayerMoveLeft"))
			{
				GetTransform()->SetLocalNegativeScaleX();
			}
			else if (true == GameEngineInput::IsDown("PlayerMoveRight"))
			{
				GetTransform()->SetLocalPositiveScaleX();
			}

			if (true == GameEngineInput::IsPress("PlayerMoveLeft"))
			{
				GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("PlayerMoveRight"))
			{
				GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("PlayerMoveUp"))
			{
				GetTransform()->AddLocalPosition(float4::Up * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("PlayerMoveDown"))
			{
				GetTransform()->AddLocalPosition(float4::Down * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("PlayerMoveForward"))
			{
				GetTransform()->AddLocalPosition(GetTransform()->GetLocalForwardVector() * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("PlayerMoveBack"))
			{
				GetTransform()->AddLocalPosition(float4::Back * Speed * _DeltaTime);
			}

			if (true == GameEngineInput::IsPress("PlayerRotY+"))
			{
				GetTransform()->AddLocalRotation({ 0.0f, RotSpeed * _DeltaTime, 0.0f });
			}
			if (true == GameEngineInput::IsPress("PlayerRotY-"))
			{
				GetTransform()->AddLocalRotation({ 0.0f, -RotSpeed * _DeltaTime, 0.0f });
			}
			if (true == GameEngineInput::IsPress("PlayerRotZ+"))
			{
				GetTransform()->AddLocalRotation({ 0.0f, 0.0f, RotSpeed * _DeltaTime });
			}
			if (true == GameEngineInput::IsPress("PlayerRotZ-"))
			{
				GetTransform()->AddLocalRotation({ 0.0f, 0.0f, -RotSpeed * _DeltaTime });
			}
			if (true == GameEngineInput::IsPress("PlayerRotX+"))
			{
				GetTransform()->AddLocalRotation({ RotSpeed * _DeltaTime, 0.0f, 0.0f });
			}
			if (true == GameEngineInput::IsPress("PlayerRotX-"))
			{
				GetTransform()->AddLocalRotation({ -RotSpeed * _DeltaTime, 0.0f, 0.0f });
			}

			float ScaleSpeed = 10.0f;

			if (true == GameEngineInput::IsPress("PlayerScaleY+"))
			{
				GetTransform()->AddLocalScale({ 0.0f, ScaleSpeed * _DeltaTime, 0.0f });
			}
			if (true == GameEngineInput::IsPress("PlayerScaleY-"))
			{
				GetTransform()->AddLocalScale({ 0.0f, -ScaleSpeed * _DeltaTime, 0.0f });
			}
			if (true == GameEngineInput::IsPress("PlayerScaleZ+"))
			{
				GetTransform()->AddLocalScale({ 0.0f, 0.0f, ScaleSpeed * _DeltaTime });
			}
			if (true == GameEngineInput::IsPress("PlayerScaleZ-"))
			{
				GetTransform()->AddLocalScale({ 0.0f, 0.0f, -ScaleSpeed * _DeltaTime });
			}
			if (true == GameEngineInput::IsPress("PlayerScaleX+"))
			{
				GetTransform()->AddLocalScale({ ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
			}
			if (true == GameEngineInput::IsPress("PlayerScaleX-"))
			{
				GetTransform()->AddLocalScale({ -ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
			}

			//std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			//if (Collsion->CollisionAll(2000, ColTest), 0 != ColTest.size())
			//{
			//	for (std::shared_ptr<GameEngineCollision> Col : ColTest)
			//	{
			//		Col->GetActor()->Death();
			//	}
			//	// Col->GetActor()->Death();
			//}

			float4 Pos = GetTransform()->GetLocalPosition();

			Pos.z -= 100;

			GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);

		},
			.End = [this]()
		{
		},

		}
	);


	FSM.ChangeState("FreeMove");

}