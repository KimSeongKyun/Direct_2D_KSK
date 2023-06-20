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
	
	void CreateAnimaionPlayer(const std::string _State);
	void TestCallBack();

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void LevelChangeStart() override;
	
	void StateInit();

	float4 TestColor;

private:
	float Angle = 0.0f;

	std::shared_ptr<class GameEngineCollision> Collsion;
	//std::shared_ptr<class GameEngineComponent> Pivot;
	//std::shared_ptr<class GameEngineComponent> Pivot2;
	//std::shared_ptr<class GameEngineSpriteRenderer> SubRender;
	GameEngineFSM FSM;

	float Speed = 100.0f;

};

