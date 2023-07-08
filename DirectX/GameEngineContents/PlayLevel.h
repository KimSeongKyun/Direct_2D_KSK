#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;
	

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
	std::shared_ptr<class GameEngineSpriteRenderer> RenderTest = nullptr;
	std::shared_ptr<class Map> Map0 = nullptr;
	std::shared_ptr<class Monster> MonsterObject = nullptr;
	std::shared_ptr<class Portal> Portal0 = nullptr;


};

