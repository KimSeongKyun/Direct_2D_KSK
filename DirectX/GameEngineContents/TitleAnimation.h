#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TitleAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleAnimation();
	~TitleAnimation();

	// delete Function
	TitleAnimation(const TitleAnimation& _Other) = delete;
	TitleAnimation(TitleAnimation&& _Other) noexcept = delete;
	TitleAnimation& operator=(const TitleAnimation& _Other) = delete;
	TitleAnimation& operator=(TitleAnimation&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> TitleAniRender;
	std::shared_ptr<class GameEngineSpriteRenderer> Back;

	float WaittingTime = 0.0f;
};

