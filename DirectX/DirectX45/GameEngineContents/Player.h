#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

// Ό³Έν :
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
	std::shared_ptr<class GameEngineComponent> Pivot;
	std::shared_ptr<class GameEngineComponent> Pivot2;
	std::shared_ptr<class GameEngineSpriteRenderer> SubRender;
	GameEngineFSM FSM;

};

