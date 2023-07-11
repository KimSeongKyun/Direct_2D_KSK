#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

// Ό³Έν :
enum class PlayerState
{
	Idle,
	LMove,
	Rope,
	Climb,
	Swing
};

enum class PlayerDirection
{
	Left,
	Right
};

class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void LevelChangeStart() override;
	void StateInit();


private:
	GameEngineFSM FSM;

	float Angle = 0.0f;
	float Speed = 100.0f; 
	float Gravity = 0.0f;
	
	bool PlayerGravity = false;
	
	float4 PlayerSize = { 39.0f, 82.0f };
	float4 PlayerHalfValue;
	float4 JumpPower = { 0, 4, 0 };
	float4 CurMapScale;

	std::string CurPlayerState = "Idle";
	
	GameEnginePixelColor ColColor = { (char)255, (char)0, (char)255,(char)255 };
	
	std::shared_ptr<class GameEngineTexture> ColMap;
	std::shared_ptr<class GameEngineTexture> CurMap;
	std::shared_ptr<class GameEngineSpriteRenderer> MainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> Body;
	std::shared_ptr<class GameEngineCollision> ColRope;
	

public:
	void RendererStateChange(const std::string _State);
	void TestCallBack();
	void SetColMap(const std::string_view& _ColMap) { ColMap = GameEngineTexture::Find(_ColMap); };
	void SetCurMap(const std::string_view& _ColMap) { CurMap = GameEngineTexture::Find(_ColMap); };
	void SetCurMapScale(float4 _MapScale);
	//void CameraUpdate(float _DeltaTime);
	std::shared_ptr<class GameEngineTexture> GetColMap() { return ColMap; };
	

	void GravityCheck(float _DeltaTime);
	void LRColCheck(float _DeltaTime, float4 _LeftOrRight);
};

