#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Ellinia0_map :public GameEngineActor
{
public:
	
public:
	// constrcuter destructer
	Ellinia0_map();
	~Ellinia0_map();

	// delete Function
	Ellinia0_map(const Ellinia0_map& _Other) = delete;
	Ellinia0_map(Ellinia0_map&& _Other) noexcept = delete;
	Ellinia0_map& operator=(const Ellinia0_map& _Other) = delete;
	Ellinia0_map& operator=(Ellinia0_map&& _Other) noexcept = delete;

	
	

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	float4 GetMapScale();

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround;
	std::shared_ptr<class GameEngineSpriteRenderer> Ground;
	
	
};

