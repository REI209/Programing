#include "GameOverScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

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
}

eSceneType GameOverScene::Update()
{

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
	//読み込んだ画像の削除
}

//現在のシーン情報を取得
eSceneType GameOverScene::GetNowScene() const
{
	return eSceneType::E_OVER;
}
