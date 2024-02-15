#pragma once
#include"DxLib.h"
#include"SceneBase.h"

class GameMainScene;

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
	
	class Player* player;       //プレイヤー
	//Enemy** enemy;        //敵

	class Enemy_Roomba* enemy_roomba;	//ルンバ
	int roomba_image;	//ルンバの画像
	float diff_x;		//プレイヤーとの差
	
	int hit_count;
	
	int bonus_image;
	float bonus_size;
	bool bonus_flg;

	//Obstacle_A** obstacle_a;//扇風機
	//int obstacle_a_image;//扇風機画像


	class Obstacle_B** obstacle_b;//積み木
	int obstacle_b_image[3];//積み木画像


	class Obstacle_C** obstacle_c;//掃除機
	int obstacle_c_image;//掃除機画像

	class Family** family; //仲間
	int family_image[2]; //仲間画像
	int family_cnt[2]; //集めた仲間の数

	int se[4];

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


