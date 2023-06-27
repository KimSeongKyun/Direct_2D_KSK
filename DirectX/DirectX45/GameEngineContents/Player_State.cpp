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
			
			

			if (false == GameEngineInput::IsPress("MoveLeft") &&
				false == GameEngineInput::IsPress("MoveRight") &&
				false == GameEngineInput::IsPress("Up") &&
				false == GameEngineInput::IsPress("Down") &&
				false == GameEngineInput::IsPress("Swing") &&
				false == GameEngineInput::IsPress("Jump"))
			{
				FSM.ChangeState("Idle");
			}

		
			if (true == GameEngineInput::IsDown("MoveLeft"))
			{
				GetTransform()->SetLocalPositiveScaleX();
			}
			if (true == GameEngineInput::IsDown("MoveRight"))
			{
				GetTransform()->SetLocalNegativeScaleX();
			}

			if (true == GameEngineInput::IsPress("MoveLeft"))
			{
				GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("MoveRight"))
			{
				GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
				float4 aaa = GetTransform()->GetLocalScale();
				int a = 0;
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
				
				
				/*if (Body->GetCurrentFrame() == 0)
				{
					Body->GetTransform()->SetLocalPosition(PlayerPos + IdleBody0);
				}
				if (Body->GetCurrentFrame() == 1)
				{
					Body->GetTransform()->SetLocalPosition(PlayerPos + IdleBody1);
					float4 Bodyloacation = Body->GetTransform()->GetLocalPosition();
				}
				if (Body->GetCurrentFrame() == 2)
				{
					Body->GetTransform()->SetLocalPosition(PlayerPos + IdleBody2);
				}
				if (Body->GetCurrentFrame() == 3)
				{
					Body->GetTransform()->SetLocalPosition(PlayerPos + IdleBody3);
				}*/
				
				

				/*float4 HeadScale = Head->GetTransform()->GetLocalScale();
				Head->GetTransform()->SetLocalPosition({ HeadScale.hx(), -HeadScale.hy() });
				Head->GetTransform()->AddLocalPosition({ -19.0f, 17.0f });*/

				



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





