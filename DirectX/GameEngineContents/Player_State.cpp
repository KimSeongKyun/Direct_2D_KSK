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
#include "Ellinia0_Level.h"
#include "ObjectEnum.h"




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

			PlayerGravity = true;
	
			GravityCheck(_DeltaTime);


			if (CurPlayerState != "Swing")
			{
				if (true == GameEngineInput::IsPress("MoveLeft"))
				{

					LRColCheck(_DeltaTime, float4::Left);
					GetTransform()->SetLocalPositiveScaleX();
				}

				if (true == GameEngineInput::IsPress("MoveRight"))
				{

					LRColCheck(_DeltaTime, float4::Right);
					GetTransform()->SetLocalNegativeScaleX();
				}

				if (true == GameEngineInput::IsPress("Jump"))
				{
					PlayerGravity = true;
					FSM.ChangeState("Jump");
				}

				if (true == GameEngineInput::IsDown("Up"))
				{
					RopeCheck();
				}


				if (false == GameEngineInput::IsPress("MoveLeft") &&
					false == GameEngineInput::IsPress("MoveRight") &&
					false == GameEngineInput::IsPress("Up") &&
					false == GameEngineInput::IsPress("Down") &&
					false == GameEngineInput::IsPress("Swing") &&
					false == GameEngineInput::IsPress("Jump"))
				{
					FSM.ChangeState("Idle");
				}
			}


			if (true == GameEngineInput::IsDown("Swing"))
			{
				RendererStateChange("Swing");
			}

			if (CurPlayerState == "Swing")
			{
				if (Body->IsAnimationEnd())
				{
					RendererStateChange("Idle");
				}
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
				RendererStateChange("Idle");
			},
			.Update = [this](float _DeltaTime)
			{				
				
				PlayerGravity = true;
				GravityCheck(_DeltaTime);

				if (true == GameEngineInput::IsPress("MoveLeft"))
				{
					GetTransform()->SetLocalPositiveScaleX();
					FSM.ChangeState("Move");
					
				}
				if (true == GameEngineInput::IsPress("MoveRight"))
				{
					GetTransform()->SetLocalNegativeScaleX();
					FSM.ChangeState("Move");
					
				}
				if (true == GameEngineInput::IsPress("Up"))
				{					
					RopeCheck();
				}

				if (true == GameEngineInput::IsPress("Down"))
				{
					return;
				}

				if (true == GameEngineInput::IsPress("Swing"))
				{
					RendererStateChange("Swing");
				}
				if (true == GameEngineInput::IsPress("Jump"))
				{
					PlayerGravity = true;
					FSM.ChangeState("Jump");
				}

				if (CurPlayerState == "Swing")
				{
					if (Body->IsAnimationEnd())
					{
						RendererStateChange("Idle");
						FSM.ChangeState("Idle");
					}
				}

				float4 Pos = GetTransform()->GetLocalPosition();

				Pos.z -= 100;
				GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
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
				PlayerGravity = true;

				GravityCheck(_DeltaTime);

				if (Body->IsAnimationEnd())
				{
					RendererStateChange("Idle");
					FSM.ChangeState("Idle");
				}

				float4 Pos = GetTransform()->GetLocalPosition();

				Pos.z -= 100;
				GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
			}
		}

	);

	FSM.CreateState(
		{
			.Name = "Jump",
			.Start = [this]()
			{
				RendererStateChange("Jump");
			},
			.Update = [this](float _DeltaTime)
			{
				if (PlayerGravity == true)
				{
					Gravity += 10 * _DeltaTime;
					if (Gravity > 9.0f)
					{
						Gravity = 9.0f;
					}

					float4 PlayerGravityValue = JumpPower + (float4::Down * Gravity);
					float4 CurPosition = GetTransform()->GetWorldPosition();
					GetTransform()->AddWorldPosition(JumpPower + (float4::Down * Gravity));					
					
					float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };
					float4 NextPosition = CurPosition + (JumpPower + (float4::Down * Gravity));							

					if (true == GameEngineInput::IsPress("MoveLeft"))
					{

						GetTransform()->SetLocalPositiveScaleX();
						GetTransform()->AddWorldPosition(float4::Left * Speed * _DeltaTime);						
						
						NextPosition += float4::Left * Speed * _DeltaTime;												
					}

					if (true == GameEngineInput::IsPress("MoveRight"))
					{
						GetTransform()->SetLocalNegativeScaleX();
						GetTransform()->AddWorldPosition(float4::Right * Speed * _DeltaTime);					
						
						NextPosition += float4::Right * Speed * _DeltaTime;
					}
					if (true == GameEngineInput::IsPress("Swing"))
					{
						RendererStateChange("Swing");
					}

					if (PlayerGravityValue.y <= 0)
					{
						
						if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
						{
							if(ColMap->GetPixel(ColMapDif.ix() + CurPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - CurPosition.iy()) != ColColor)
							{ 
								GetTransform()->SetWorldPosition(CurPosition);
								PlayerGravity = false;
								Gravity = 0.0f;
								JumpPower = { 0,4.5f ,0 };
								if (CurPlayerState != "Swing")
								{
									FSM.ChangeState("Move");
								}
								
							}
						}

					}

					if (true == GameEngineInput::IsDown("Up"))
					{
						RopeCheck();
					}
				}

				float4 Pos = GetTransform()->GetLocalPosition();

				Pos.z -= 100;
				GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);

				

				if (CurPlayerState == "Swing")
				{
					if (true == Body->IsAnimationEnd())
					{
						FSM.ChangeState("Idle");
					}
				}
			}
		}

	);
	 
	FSM.CreateState(
		{
			.Name = "Rope",
			.Start = [this]()
		{
			RendererStateChange("Rope");
		},
			.Update = [this](float _DeltaTime)
		{
			PlayerGravity = false;

			if (true == GameEngineInput::IsPress("Up"))
			{
				GetTransform()->AddWorldPosition(float4::Up* Speed* _DeltaTime);
			}
			if (true == GameEngineInput::IsPress("Down"))
			{
				GetTransform()->AddWorldPosition(float4::Down* Speed * _DeltaTime);
			}

			if (true == GameEngineInput::IsDown("Jump"))
			{
				JumpPower = { 0,2,0 };
				FSM.ChangeState("Jump");
			}

		}
		}
	);

	FSM.ChangeState("Idle");
}





