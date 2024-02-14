#include "GameOverScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Object/common.h"

GameOverScene::GameOverScene() :background_image(NULL)
{
}

GameOverScene::~GameOverScene()
{
}

//初期化処理
void GameOverScene::Initialize()
{
	//画像の読み込み

	//エラーチェック

	//音源の読み込み
	gameoverbgm = LoadSoundMem(GAMEOVER_BGM);
}

eSceneType GameOverScene::Update()
{
	//BGMを流す
	if (GetNowScene() == E_OVER)
	{
		PlaySoundMem(gameoverbgm, DX_PLAYTYPE_LOOP, FALSE);
	}
	//Bボタンが押されたら、リザルトへ
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_RESULT;
	}
	return GetNowScene();

}

void GameOverScene::Draw() const
{
	//背景画像の描画
	DrawString(20, 120, "GameOver", 0xffffff, 0);

}

//終了宣言
void GameOverScene::Finalize()
{
	//読み込んだ音源の削除
	DeleteSoundMem(gameoverbgm);
}

//現在のシーン情報を取得
eSceneType GameOverScene::GetNowScene() const
{
	return eSceneType::E_OVER;
}
