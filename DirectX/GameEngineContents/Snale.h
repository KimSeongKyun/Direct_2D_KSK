#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
enum class SnaleState
{
	Idle,
	Move
};

class Snale :public GameEngineActor
{
public:
	// constrcuter destructer
	Snale();
	~Snale();

	// delete Function
	Snale(const Snale& _Other) = delete;
	Snale(Snale&& _Other) noexcept = delete;
	Snale& operator=(const Snale& _Other) = delete;
	Snale& operator=(Snale&& _Other) noexcept = delete;


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

