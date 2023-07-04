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
#include "Map.h"
#include "PlayLevel.h"
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

			

			if (PlayerGravity == true)
			{
				Gravity += 10 * _DeltaTime;

				if (Gravity > 5.0f)
				{
					Gravity = 5.0f;
				}
				float4 CurPosition = GetTransform()->GetWorldPosition();
				float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };
				
				
				GetTransform()->AddWorldPosition(float4::Down * Gravity);
				float4 NextPosition = CurPosition + (float4::Down * Gravity);

				if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
				{
					GetTransform()->SetWorldPosition(CurPosition);
					PlayerGravity = false;
					Gravity = 0.0f;
				}
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

			if (true == GameEngineInput::IsPress("MoveLeft"))
			{

				float4 CurPosition = GetTransform()->GetWorldPosition();
				float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };
				
				GetTransform()->SetLocalPositiveScaleX();
				GetTransform()->AddWorldPosition(float4::Left * Speed * _DeltaTime);
				float4 NextPosition = CurPosition + float4::Left * Speed * _DeltaTime;

				if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
				{
					for (float i = 1.0f; i <= 5.0f; i += _DeltaTime)
					{
						NextPosition += float4::Up * i;
						if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() - i + (int)PlayerSize.hy() - NextPosition.iy()) != ColColor)
						{
							GetTransform()->SetWorldPosition(NextPosition);
							break;
						}

						if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() - i + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
						{
							if (i == 5.0f)
							{
								GetTransform()->SetWorldPosition(CurPosition);
							}
							continue;
						}
					}
				}
			}

			if (true == GameEngineInput::IsPress("MoveRight"))
			{
				float4 CurPosition = GetTransform()->GetWorldPosition();
				float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };
			
				GetTransform()->SetLocalNegativeScaleX();
				GetTransform()->AddWorldPosition(float4::Right * Speed * _DeltaTime);

				float4 NextPosition = CurPosition + float4::Right * Speed * _DeltaTime;
				if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
				{
					for (float i = 1.0f; i <= 5.0f; i +=  _DeltaTime)
					{
						NextPosition += float4::Up * i;
						if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() - i + (int)PlayerSize.hy() - NextPosition.iy()) != ColColor)
						{
							GetTransform()->SetWorldPosition(NextPosition);
							break;
						}

						if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() - i + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
						{
							if (i == 5.0f)
							{
								GetTransform()->SetWorldPosition(CurPosition);
							}
							continue;
						}
					}
				}
			}

			if (true == GameEngineInput::IsPress("Jump"))
			{
				PlayerGravity = true;
				FSM.ChangeState("Jump");
			}

			if (true == GameEngineInput::IsDown("Up"))
			{
				std::shared_ptr<GameEngineCollision> isColRope = ColRope->Collision(static_cast<int>(ObjectEnum::Rope), ColType::AABBBOX2D, ColType::AABBBOX2D);

				if (isColRope != nullptr)
				{
					float4 PlayerPos = GetTransform()->GetWorldPosition();
					float4 RopePos = ColRope->GetTransform()->GetWorldPosition();
					GetTransform()->SetWorldPosition({ RopePos.x, PlayerPos.y,PlayerPos.z });

					FSM.ChangeState("Rope");
				}
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
				PlayerGravity = true;

				if (PlayerGravity == true)
				{
					Gravity += 10 * _DeltaTime;

					if (Gravity > 5.0f)
					{
						Gravity = 5.0f;
					}

					float4 CurPosition = GetTransform()->GetWorldPosition();
					GetTransform()->AddWorldPosition(float4::Down * Gravity);

					float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };
					float4 NextPosition = CurPosition + (float4::Down * Gravity);

					if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
					{
						GetTransform()->SetWorldPosition(CurPosition);
						PlayerGravity = false;
						Gravity = 0.0f;
					}
				}
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
					
					std::shared_ptr<GameEngineCollision> isColRope = ColRope->Collision(static_cast<int>(ObjectEnum::Rope), ColType::AABBBOX2D, ColType::AABBBOX2D);

					if (isColRope != nullptr)
					{
						float4 PlayerPos = GetTransform()->GetWorldPosition();
						float4 RopePos = ColRope->GetTransform()->GetWorldPosition();
						GetTransform()->SetWorldPosition({ RopePos.x, PlayerPos.y,PlayerPos.z });
						FSM.ChangeState("Rope");
					}

					
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
					PlayerGravity = true;
					FSM.ChangeState("Jump");
				}
				float4 Pos = GetTransform()->GetLocalPosition();

				Pos.z -= 100;
				//GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
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
				float4 Pos = GetTransform()->GetLocalPosition();

				Pos.z -= 100;
				//GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
			}
		}

	);

	FSM.CreateState(
		{
			.Name = "Jump",
			.Start = [this]()
			{
				int a = 0;
			},
			.Update = [this](float _DeltaTime)
			{
				if (PlayerGravity == true)
				{
					RendererStateChange("Jump");

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

					if (PlayerGravityValue.x <= 0)
					{

						if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - NextPosition.iy()) == ColColor)
						{
							if(ColMap->GetPixel(ColMapDif.ix() + CurPosition.ix(), ColMapDif.iy() + (int)PlayerSize.hy() - CurPosition.iy()) != ColColor)
							{ 
								GetTransform()->SetWorldPosition(CurPosition);
								PlayerGravity = false;
								Gravity = 0.0f;
								FSM.ChangeState("Move");
							}
						}

					}

					if (true == GameEngineInput::IsDown("Up"))
					{
						std::shared_ptr<GameEngineCollision> isColRope = ColRope->Collision(static_cast<int>(ObjectEnum::Rope), ColType::AABBBOX2D, ColType::AABBBOX2D);

						if (isColRope != nullptr)
						{
							float4 PlayerPos = GetTransform()->GetWorldPosition();
							float4 RopePos = ColRope->GetTransform()->GetWorldPosition();
							GetTransform()->SetWorldPosition({ RopePos.x, PlayerPos.y,PlayerPos.z });

							FSM.ChangeState("Rope");
						}

					}
				}

				float4 Pos = GetTransform()->GetLocalPosition();

				Pos.z -= 100;
				//GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
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

			if (true == GameEngineInput::IsDown("Up"))
			{
				GetTransform()->AddWorldPosition(float4::Up* Speed* _DeltaTime);
			}
			if (true == GameEngineInput::IsDown("Down"))
			{
				GetTransform()->AddWorldPosition(float4::Down* Speed * _DeltaTime);
			}

			if (true == GameEngineInput::IsDown("Jump"))
			{
				FSM.ChangeState("Jump");
			}

		}
		}
	);

	FSM.ChangeState("Idle");
}





