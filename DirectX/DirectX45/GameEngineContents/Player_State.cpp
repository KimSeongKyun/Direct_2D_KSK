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



void Player::StateInit() 
{
	FSM.CreateState(
		{
			.Name = "Move",
			.Start = [this]()
		{
			
		},
			.Update = [this](float _DeltaTime)
		{

			if (false == GameEngineInput::IsDown("MoveLeft") ||
				false == GameEngineInput::IsDown("MoveRight") ||
				false == GameEngineInput::IsDown("Up") ||
				false == GameEngineInput::IsDown("Down") ||
				false == GameEngineInput::IsDown("Swing") ||
				false == GameEngineInput::IsDown("Jump"))
			{
				FSM.ChangeState("Idle");
			}

			if (true == GameEngineInput::IsDown("MoveLeft"))
			{
				GetTransform()->SetLocalNegativeScaleX();
			}
			if (true == GameEngineInput::IsDown("MoveRight"))
			{
				GetTransform()->SetLocalPositiveScaleX();
			}

			if (true == GameEngineInput::IsPress("MoveLeft"))
			{
				GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("MoveRight"))
			{
				GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
			}
		
			if (true == GameEngineInput::IsUp("MoveLeft"))
			{
				FSM.ChangeState("Idle");
			}
			if (true == GameEngineInput::IsUp("MoveRight"))
			{
				FSM.ChangeState("Idle");
			}
			float4 Pos = GetTransform()->GetLocalPosition();

			Pos.z -= 100;

			GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);

		},
			.End = [this]()
		{
		},

		}
	);


	FSM.CreateState(
		{
			.Name = "Idle",
			.Start = [this]()
			{

			},
			.Update = [this](float _DeltaTime)
			{
				if (true == GameEngineInput::IsDown("MoveLeft"))
				{
					FSM.ChangeState("Move");
					GetTransform()->SetLocalNegativeScaleX();
				}
				if (true == GameEngineInput::IsDown("MoveRight"))
				{
					FSM.ChangeState("Move");
					GetTransform()->SetLocalPositiveScaleX();
				}
				if (true == GameEngineInput::IsDown("Up"))
				{
					return;
				}
				if (true == GameEngineInput::IsDown("Down"))
				{
					return;
				}
				if (true == GameEngineInput::IsDown("Swing"))
				{
					FSM.ChangeState("Swing");
				}
				if (true == GameEngineInput::IsDown("Jump"))
				{
					FSM.ChangeState("Jump");
				}
			}
		}

	);

	FSM.CreateState(
		{
			.Name = "Swing",
			.Start = [this]()
			{

			},
			.Update = [this](float _DeltaTime)
			{
				FSM.ChangeState("Idle");
			}
		}

	);

	FSM.CreateState(
		{
			.Name = "Jump",
			.Start = [this]()
			{

			},
			.Update = [this](float _DeltaTime)
			{
				FSM.ChangeState("Idle");
			}
		}

	);
	
	FSM.ChangeState("Idle");
}

