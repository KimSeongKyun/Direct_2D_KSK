#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "Ellinia0_Level.h"
#include "Ellinia1_Level.h"
#include "TitleLevel.h"

#include <GameEngineCore/GameEngineCoreWindow.h>



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
	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::GameEnd() 
{

}