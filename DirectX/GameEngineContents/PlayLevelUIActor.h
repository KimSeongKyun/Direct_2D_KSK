#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
class PlayLevelUIActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayLevelUIActor();
	~PlayLevelUIActor();

	// delete Function
	PlayLevelUIActor(const PlayLevelUIActor& _Other) = delete;
	PlayLevelUIActor(PlayLevelUIActor&& _Other) noexcept = delete;
	PlayLevelUIActor& operator=(const PlayLevelUIActor& _Other) = delete;
	PlayLevelUIActor& operator=(PlayLevelUIActor&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> ButtonDeath;
};

