#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
class Ellinia1_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Ellinia1_Level();
	~Ellinia1_Level();

	// delete Function
	Ellinia1_Level(const Ellinia1_Level& _Other) = delete;
	Ellinia1_Level(Ellinia1_Level&& _Other) noexcept = delete;
	Ellinia1_Level& operator=(const Ellinia1_Level& _Other) = delete;
	Ellinia1_Level& operator=(Ellinia1_Level&& _Other) noexcept = delete;
	

	std::shared_ptr<class GameEngineVideo> Video;
	std::shared_ptr<class TestObject> Object3;
	std::shared_ptr<class FadeEffect> FEffect;
	

protected:
	void Update(float _DeltaTime) override;
	void Start() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
	

private:
	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class Ellinia1_map> Map0 = nullptr;
	std::shared_ptr<class Snale> MonsterObject = nullptr;
	std::shared_ptr<class Portal> Portal0 = nullptr;
	std::shared_ptr<class Status> StatusRender = nullptr;
	std::shared_ptr<class QuickSlot> StaQuickSlottusRender = nullptr;
};

