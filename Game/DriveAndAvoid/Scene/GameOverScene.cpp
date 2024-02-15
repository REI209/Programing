#include "GameOverScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Object/common.h"

GameOverScene::GameOverScene() :background_image(NULL),gameoverbgm(0)
{
}

GameOverScene::~GameOverScene()
{
}

//初期化処理
void GameOverScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph(GAMEOVER_BACK_IMAGE);
	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/Images/game_over.pngがありません\n");
	}

	//音源の読み込み
	gameoverbgm = LoadSoundMem(GAMEOVER_BGM);
}

eSceneType GameOverScene::Update()
{
	
	PlaySoundMem(gameoverbgm, DX_PLAYTYPE_BACK, FALSE);
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
	DrawGraph(0, 0, background_image, TRUE);
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
