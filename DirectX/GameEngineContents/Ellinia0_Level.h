#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class Ellinia0_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Ellinia0_Level();
	~Ellinia0_Level();

	// delete Function
	Ellinia0_Level(const Ellinia0_Level& _Other) = delete;
	Ellinia0_Level(Ellinia0_Level&& _Other) noexcept = delete;
	Ellinia0_Level& operator=(const Ellinia0_Level& _Other) = delete;
	Ellinia0_Level& operator=(Ellinia0_Level&& _Other) noexcept = delete;



protected:
	void Update(float _DeltaTime) override;
	void Start() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class Ellinia0_map> Map0 = nullptr;
	std::shared_ptr<class Snale> MonsterObject = nullptr;
	std::shared_ptr<class Portal> Portal0 = nullptr;
	std::shared_ptr<class Texture> Map1 = nullptr;
};

