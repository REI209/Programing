#pragma once
#include"DxLib.h"

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include "../Object/Enemy_Roomba.h"
//#include "../Object/Obstacle_A.h"
#include "../Object/Obstacle_B.h"
//#include "../Object/Obstacle_C.h"
class GameMainScene :public SceneBase
{
private:
	int time;	//経過時間
	int counter;		//現在時間

	int high_score;       //ハイスコア
	int back_ground;      //背景画像
	int barrier_image;    //バリア画像
	int mileage;          //走行距離
	int enemy_image[3];   //敵画像
	int enemy_count[3];   //通り過ぎた敵カウント
	Player* player;       //プレイヤー
	//Enemy** enemy;        //敵

	Enemy_Roomba* enemy_roomba;	//ルンバ
	int roomba_image;	//ルンバの画像

	Obstacle_B** obstacle_b;//積み木
	int obstacle_b_image;//積み木画像

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//ハイスコア読み込み処理
	void ReadHighScore();
	//当たり判定
	bool IsHitCheck(Player* p, Enemy* e);
};