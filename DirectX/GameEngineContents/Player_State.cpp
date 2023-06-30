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
			RendererStateChange("Move");
		},
			.Update = [this](float _DeltaTime)
		{
			
			

			if (false == GameEngineInput::IsPress("MoveLeft") &&
				false == GameEngineInput::IsPress("MoveRight") &&
				false == GameEngineInput::IsPress("Up") &&
				false == GameEngineInput::IsPress("Down") &&
				false == GameEngineInput::IsPress("Swing") &&
				false == GameEngineInput::IsPress("Jump"))
			{
				FSM.ChangeState("Idle");
			}

			if (true == GameEngineInput::IsPress("MoveLeft"))
			{
				GetTransform()->SetLocalPositiveScaleX();
				GetTransform()->AddWorldPosition(float4::Left * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("MoveRight"))
			{
				GetTransform()->SetLocalNegativeScaleX();
				GetTransform()->AddWorldPosition(float4::Right * Speed * _DeltaTime);
				
			}

			if (true == GameEngineInput::IsPress("Jump"))
			{
				FSM.ChangeState("Jump");

			}

			
			float4 Pos = GetTransform()->GetLocalPosition();

			Pos.z -= 100;

			//GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);

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
				

				RendererStateChange("Idle");
				if (true == GameEngineInput::IsDown("MoveLeft"))
				{
					FSM.ChangeState("Move");
					GetTransform()->SetLocalPositiveScaleX();
				}
				if (true == GameEngineInput::IsDown("MoveRight"))
				{
					FSM.ChangeState("Move");
					GetTransform()->SetLocalNegativeScaleX();
				}
				if (true == GameEngineInput::IsDown("Up"))
				{
					return;
				}
				if (true == GameEngineInput::IsDown("Down"))
				{
					return;
				}
				if (true == GameEngineInput::IsPress("Swing"))
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
				RendererStateChange("Swing");
			},
			.Update = [this](float _DeltaTime)
			{
				if (Body->IsAnimationEnd())
				{
					RendererStateChange("Idle");
					FSM.ChangeState("Idle");
				}
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

				RendererStateChange("Jump");
				Gravity += 10 * _DeltaTime;
				GetTransform()->AddWorldPosition(JumpPower + float4::Down* Gravity);


				if (true == GameEngineInput::IsPress("MoveLeft"))
				{
					GetTransform()->SetLocalPositiveScaleX();
					GetTransform()->AddWorldPosition(float4::Left * Speed * _DeltaTime);
				}
				if (true == GameEngineInput::IsPress("MoveRight"))
				{
					GetTransform()->SetLocalNegativeScaleX();
					GetTransform()->AddWorldPosition(float4::Right * Speed * _DeltaTime);

				}
				
				
				
					
			}
		}

	);
	
	FSM.ChangeState("Idle");
}





