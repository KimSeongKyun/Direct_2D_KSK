#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

// Ό³Έν :
enum class PlayerState
{
	Idle,
	LMove,
	Rope,
	Climb,
	Swing
};

enum class PlayerDirection
{
	Left,
	Right
};

class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> MainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> Head;
	std::shared_ptr<class GameEngineSpriteRenderer> Body;
	std::shared_ptr<class GameEngineSpriteRenderer> Arm;
	std::shared_ptr<class GameEngineSpriteRenderer> LHand;
	std::shared_ptr<class GameEngineSpriteRenderer> RHand;
	
	void RendererStateChange(const std::string _State);
	void TestCallBack();
	void SetColMap(const std::string_view& _ColMap) { ColMap = GameEngineTexture::Find(_ColMap);};


protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void LevelChangeStart() override;
	void StateInit();

	float4 TestColor;

private:
	float Angle = 0.0f;

	std::shared_ptr<class GameEngineCollision> ColRope;
	
	
	GameEngineFSM FSM;

	float Speed = 100.0f; 
	
	float4 PlayerSize = { 39.0f, 64.0f };

	float4 IdleBody0 = { -4.0f, -17.0f };
	float4 IdleBody1 = { -4.0f, -17.0f };
	float4 IdleBody2 = { -5.0f, -17.0f };
	float4 IdleBody3 = { -4.0f, -17.0f };

	float4 IdleArm0 = { 7.0f, -12.0f };
	

	float4 IdleHead = { 0.0f, 14.0f };

	std::string CurPlayerState = "Idle";
	float Gravity = 0.0f;
	float4 JumpPower = { 0, 4, 0 };
	bool PlayerGravity = false;
	std::shared_ptr<class GameEngineTexture> ColMap;
	GameEnginePixelColor ColColor = { (char)255, (char)0, (char)255,(char)255 };
	float4 PlayerHalfValue;
	
};

