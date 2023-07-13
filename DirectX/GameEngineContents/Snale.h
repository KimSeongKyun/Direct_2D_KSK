#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
enum class SnaleState
{
	Idle,
	Move
};

class Snale :public GameEngineActor
{
public:
	// constrcuter destructer
	Snale();
	~Snale();

	// delete Function
	Snale(const Snale& _Other) = delete;
	Snale(Snale&& _Other) noexcept = delete;
	Snale& operator=(const Snale& _Other) = delete;
	Snale& operator=(Snale&& _Other) noexcept = delete;


protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineTexture> ColMap;
	std::shared_ptr<class GameEngineTexture> CurMap;
	
	float Speed = 40.0f;
	float StackTime = 0.0f;
	float Gravity = 0.0f;

	bool IsGravity = true;
	std::string StateString;

	float4 SnaleSize = { 37.0f ,26.0f };

	GameEnginePixelColor ColGroundColor = { (char)255, (char)0, (char)255,(char)255 };
	GameEnginePixelColor ColWallColor = { (char)0, (char)255, (char)255,(char)255 };

public:
	void ChangeState(const std::string& _State);
	void SetColMap(const std::string_view _ColMap) { ColMap = GameEngineTexture::Find(_ColMap); }
	void SetCurMap(const std::string_view& _ColMap) { CurMap = GameEngineTexture::Find(_ColMap); };


};

