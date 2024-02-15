#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include "../Object/common.h"
TitleScene::TitleScene() :background_image(NULL),cursor_image(NULL), menu_cursor(0),titlebgm(0)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/Title.png");
	cursor_image = LoadGraph("Resource/images/cursor.png");
	//音源の読み込み
	titlebgm = LoadSoundMem(TITLE_BGM);

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
}

//更新処理
eSceneType TitleScene::Update()
{
	//BGMを流す
	if (GetNowScene() == E_TITLE)
	{
		PlaySoundMem(titlebgm, DX_PLAYTYPE_LOOP, FALSE);
	}
	
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//一番下に到達したら、一番上にする
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
	}

	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//一番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
	}

	//カーソル決定(決定した画面に遷移する)
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_HELP;
		case 2:
			return eSceneType::E_END;
		default:
			break;	
		}
	}
	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	//タイトル画面の描画
	DrawGraph(0, 0, background_image, FALSE);

	//カーソル画面の描画
	DrawGraph(320, 305 + menu_cursor * 100, cursor_image,TRUE);
}

//終了時宣言
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(cursor_image);
	DeleteSoundMem(titlebgm);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}