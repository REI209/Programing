#include "GameClear.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Object/common.h"

GameClear::GameClear():background_image(0),clearbgm(0),ok_se(0)
{
}

GameClear::~GameClear()
{
}

void GameClear::Initialize()
{
	background_image = LoadGraph(GAMECLEAR_BACK_IMAGE);
	if (background_image == -1)
	{
		throw("Resource/Images/game_clear.pngがありません\n");
	}


}

eSceneType GameClear::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
		return eSceneType::E_RESULT;
	}
	return GetNowScene();
}

void GameClear::Draw() const
{
	DrawGraph(0, 0, background_image, TRUE);
	DrawString(0, 0, "Gasme Clear", 0xffffff);
}

void GameClear::Finalize()
{
}

eSceneType GameClear::GetNowScene() const
{
	return eSceneType::E_CLEAR;
}