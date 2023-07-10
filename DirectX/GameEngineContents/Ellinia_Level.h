#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class Ellinia_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Ellinia_Level();
	~Ellinia_Level();

	// delete Function
	Ellinia_Level(const Ellinia_Level& _Other) = delete;
	Ellinia_Level(Ellinia_Level&& _Other) noexcept = delete;
	Ellinia_Level& operator=(const Ellinia_Level& _Other) = delete;
	Ellinia_Level& operator=(Ellinia_Level&& _Other) noexcept = delete;



protected:
	void Update(float _DeltaTime) override;
	void Start() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class Map> Map0 = nullptr;
	std::shared_ptr<class Monster> MonsterObject = nullptr;
	std::shared_ptr<class Portal> Portal0 = nullptr;
};

