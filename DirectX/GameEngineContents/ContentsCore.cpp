#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "Ellinia0_Level.h"
#include "Ellinia1_Level.h"
#include "TitleLevel.h"
#include "PinkBeanLevel.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

//float4 ContentsCore::PlayerMovePos = { 743.0f, -785.0f , 1.0f };
float4 ContentsCore::PlayerMovePos = { 0.0f, -0.0f , 0.0f };

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}


void ContentsCore::GameStart() 
{


	//new int();

	GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");
	ContentsResourcesCreate();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<Ellinia0_Level>();
	GameEngineCore::CreateLevel< Ellinia1_Level>();
	GameEngineCore::CreateLevel< PinkBeanLevel>();
	GameEngineCore::ChangeLevel("PinkBeanLevel");
}

void ContentsCore::GameEnd() 
{

}