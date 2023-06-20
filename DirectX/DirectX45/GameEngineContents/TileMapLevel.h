#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class TileMapLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TileMapLevel();
	~TileMapLevel();

	// delete Function
	TileMapLevel(const TileMapLevel& _Other) = delete;
	TileMapLevel(TileMapLevel&& _Other) noexcept = delete;
	TileMapLevel& operator=(const TileMapLevel& _Other) = delete;
	TileMapLevel& operator=(TileMapLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer BgmPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineActor> TileMapPoint;
	std::shared_ptr<GameEngineTileMapRenderer> TileMap;
	std::shared_ptr<GameEngineSpriteRenderer> Sp;
	std::shared_ptr<GameEngineComponent> Pivot;
	std::shared_ptr<GameEngineComponent> Pivot2;
	std::shared_ptr<GameEngineRenderer> RollRender;
	std::shared_ptr<GameEngineRenderer> RollRender2;
};

