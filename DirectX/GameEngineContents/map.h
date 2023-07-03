#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Map  :public GameEngineActor
{
public:
	static Map* MainMap;
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void SetGround(const std::string& _Texture);
	void SetBackGround(const std::string& _Texture);
	void SetPortal();
	void SetColMap(const std::string& _ColMap);
	std::shared_ptr<class GameEngineTexture> GetColMap();

protected:

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround;
	std::shared_ptr<class GameEngineSpriteRenderer> Ground;
	std::vector<std::shared_ptr<class portal>> Portal;
	std::shared_ptr<class GameEngineTexture> ColMap;
};

