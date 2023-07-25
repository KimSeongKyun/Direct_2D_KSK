#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Ellinia1_map :public GameEngineActor
{
public:
	// constrcuter destructer
	Ellinia1_map();
	~Ellinia1_map();

	// delete Function
	Ellinia1_map(const Ellinia1_map& _Other) = delete;
	Ellinia1_map(Ellinia1_map&& _Other) noexcept = delete;
	Ellinia1_map& operator=(const Ellinia1_map& _Other) = delete;
	Ellinia1_map& operator=(Ellinia1_map&& _Other) noexcept = delete;

	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	

protected:

private:
	void ComponentSetting();

	std::shared_ptr<class GameEngineSpriteRenderer> BackGround;
	std::shared_ptr<class GameEngineSpriteRenderer> Ground;
	



};
