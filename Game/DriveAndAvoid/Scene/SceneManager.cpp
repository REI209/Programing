#include"SceneManager.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include"TitleScene.h"
#include"GameMainScene.h"
#include"ResultScene.h"
#include"HelpScene.h"
#include"RankingDispScene.h"
#include"RankingInputScene.h"

SceneManager::SceneManager() :current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{

}

//シーンマネージャー機能：初期化処理
void SceneManager::Initialize()
{
	//ウィンドウのタイトルを設定
	SetMainWindowText("Drive&Avoid");

	//ウィンドウモードで起動
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("ウィンドウモードで起動できませんでした\n");
	}

	//DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		throw("Dxライブラリが初期化できませんでした\n");
	}

	//描画先指定処理
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("描画先の指定ができませんでした\n");
	}

	//タイトルシーンから始める
	ChangeScene(eSceneType::E_TITLE);
}