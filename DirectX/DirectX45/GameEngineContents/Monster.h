#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
enum class SnaleState
{
	Idle,
	Move
};

class Monster :public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;


protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	void ChangeState(const std::string& _State);
	float Speed = 40.0f;
	float StackTime = 0.0f;
	std::string StateString;


};

