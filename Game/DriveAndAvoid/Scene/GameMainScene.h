#pragma once
#include"DxLib.h"

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include "../Object/Enemy_Roomba.h"
#include "../Object/Obstacle_A.h"
#include "../Object/Obstacle_B.h"
#include "../Object/Obstacle_C.h"
#include "../Object/Family.h"
class GameMainScene :public SceneBase
{
private:
	int time;	//経過時間
	int counter;		//現在時間
	int count_down;

	int high_score;       //ハイスコア
	int back_ground;      //背景画像
	int barrier_image;    //バリア画像
	int mileage;          //走行距離
	int enemy_image[3];   //敵画像
	int enemy_count[3];   //通り過ぎた敵カウント
	int mainbgm;          //ゲームメインBGM
	int roombabgm;        //ルンバ爆発BGM
	Player* player;       //プレイヤー
	//Enemy** enemy;        //敵

	Enemy_Roomba* enemy_roomba;	//ルンバ
	int roomba_image;	//ルンバの画像
	float diff_x;		//プレイヤーとの差

	Obstacle_A** obstacle_a;//扇風機
	int obstacle_a_image;//扇風機画像


	Obstacle_B** obstacle_b;//積み木
	int obstacle_b_image;//積み木画像


	Obstacle_C** obstacle_c;//掃除機
	int obstacle_c_image;//掃除機画像

	Family** family; //仲間
	int family_image[2]; //仲間画像
	int family_cnt[2]; //集めた仲間の数

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
	//プレイヤーと敵(ルンバ)の当たり判定
	bool IsHitCheck(Player* p, Enemy_Roomba* e);
	//プレイヤーと障害物の当たり判定
	template <class T>
	bool IsObjectHitCheck_P(Player* p, T* object);
	//敵(ルンバ)障害物の当たり判定
	template <class T>
	bool IsObjecHitCheck_E(Enemy_Roomba* e, T* object);
	//障害物同士の当たり判定
	template <class T>
	bool IsObjecHitCheck_O(T* object1, T* object2);
};


