#include "PrecompileHeader.h"
#include "map.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
	if (nullptr == GameEngineSprite::Find("Ellinia"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Map");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ground").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BackGround").GetFullPath());
	}
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetTexture("ElliniaBackGround.png");
	BackGround->SetScaleToTexture("ElliniaBackGround.png");
	BackGround->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	Ground = CreateComponent<GameEngineSpriteRenderer>();
	Ground->SetTexture("Ellinia0.png");
	Ground->SetScaleToTexture("Ellinia0.png");
	Ground->GetTransform()->SetLocalPosition({ 0, 0, -100.0f });
	
}

void Map::Update(float _Delta)
{

}
void Map::Render(float _Delta)
{

}

void Map::SetGround(const std::string& _Texture)
{
	Ground->SetTexture(_Texture + ".png");
	Ground->SetScaleToTexture(_Texture);


}
void Map::SetBackGround(const std::string& _Texture)
{
	BackGround->SetTexture(_Texture + "BackGround.png");
	BackGround->SetScaleToTexture(_Texture + "BackGround.png");
}
void Map::SetPortal()
{

}