#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL),
mileage(0), player(nullptr),
enemy(nullptr)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	//高得点値を読み込む
	ReadHighScore();

	//画像の読み込み
	back_ground = LoadGraph("Resouce/images/back.bpm");
	barrier_image = LoadGraph("Resouce/images/barrier.png");
	int result = LoadDivGraph("Resouce/images/car.bpm", 3, 3, 1, 63, 120,
		enemy_image);

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resouce/images/back.bpmがありません\n");
	}
	if (result == -1)
	{
		throw("Resouce/images/car.bpmがありません\n");
	}
	if (barrier_image == -1)
	{
		throw("Resouce/images/barrier.pngがありません\n");
	}

	//オブジェクトの生成
	player = new Player;
	enenmy = new Enemy * [10];

	//オブジェクトの初期化
	Player->Initialize();

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
}

//更新処理
eSceneType GameMainScene::Update()
{

}