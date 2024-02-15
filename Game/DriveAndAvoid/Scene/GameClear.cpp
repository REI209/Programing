#include "GameClear.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Object/common.h"

GameClear::GameClear():background_image(0),clearbgm(0)
{
}

GameClear::~GameClear()
{
}

void GameClear::Initialize()
{
}

eSceneType GameClear::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_RESULT;
	}
	return GetNowScene();
}

void GameClear::Draw() const
{
	DrawString(0, 0, "Gasme Clear", 0xffffff);
}

void GameClear::Finalize()
{
}

eSceneType GameClear::GetNowScene() const
{
	return eSceneType::E_CLEAR;
}