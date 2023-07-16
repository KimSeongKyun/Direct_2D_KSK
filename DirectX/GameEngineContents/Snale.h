#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Monster.h"

// ���� :
enum class SnaleState
{
	Idle,
	Move
};

class Snale :public Monster
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
	std::string StateString;
	float4 SnaleSize = { 37.0f ,26.0f };
	float StackTime = 0.0f;
	float Speed = 40.0f;

public:
	void ChangeState(const std::string& _State);



};

