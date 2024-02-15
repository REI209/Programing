#include"HelpScene.h"
#include"../Utility/InputControl.h"
#include"../Object/common.h"
#include"DxLib.h"
#include "../Object/common.h"

HelpScene::HelpScene() :background_image(NULL),bgm(0),ok_se(0)
{

}

HelpScene::~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph(HELP_BACK_IMAGE);

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/game_help.pngがありません\n");
	}
}

//更新処理
eSceneType HelpScene::Update()
{
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//描画処理
void HelpScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);
}

//終了宣言
void HelpScene::Finalize()
{
	//読み込んだ画像削除
	//DeleteGraph(background_image);

	DeleteSoundMem(bgm);
	//DeleteSoundMem(ok_se);
}

//現在のシーン情報を取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}