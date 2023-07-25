#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PinkBeanMap :public GameEngineActor
{
public:
	// constrcuter destructer
	PinkBeanMap();
	~PinkBeanMap();

	// delete Function
	PinkBeanMap(const PinkBeanMap& _Other) = delete;
	PinkBeanMap(PinkBeanMap&& _Other) noexcept = delete;
	PinkBeanMap& operator=(const PinkBeanMap& _Other) = delete;
	PinkBeanMap& operator=(PinkBeanMap&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	void ComponentSetting();
	
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround;
	std::shared_ptr<class GameEngineSpriteRenderer> Ground;

	
};

