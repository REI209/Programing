#pragma once
#include"DxLib.h"

#include"../Object/Player.h"
#include"SceneBase.h"
#include<math.h>


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

	int bonus_image;		//ボーナス画像
	float bonus_size;			//サイズ変更


	int main_sound;       //ゲームメインサウンド
	int gameover_sound;   //ゲームオーバーサウンド
	int enemy_count[3];   //通り過ぎた敵カウント
	int mainbgm;          //ゲームメインBGM
	class Player* player;       //プレイヤー

	class Enemy_Roomba* enemy_roomba;	//ルンバ
	int roomba_image;	//ルンバの画像
	float diff_x;		//プレイヤーとの差

	class Obstacle_A** obstacle_a;//扇風機
	int obstacle_a_image;//扇風機画像


	class Obstacle_B** obstacle_b;//積み木
	int obstacle_b_image[3];//積み木画像


	class Obstacle_C** obstacle_c;//掃除機
	int obstacle_c_image;//掃除機画像

	class Family** family; //仲間
	int family_image[2]; //仲間画像
	int family_cnt[2]; //集めた仲間の数

	class Wind** wind;  //風
	int wind_image[2]; //風画像

public:
	bool bonus_flg;

public:
	GameMainScene* main;

	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	bool GetBonusFlg(bool flg) { return bonus_flg = flg; }


private:
	//ハイスコア読み込み処理
	void ReadHighScore();
	//プレイヤーと敵(ルンバ)の当たり判定
	bool IsHitCheck(Player* p, class Enemy_Roomba* e);
	
	//当たり判定
	template <class T, class U>
	bool IsObjecHitCheck_O(T* object1, U* object2)
	{
		//情報がなければ、当たり判定を無視する
		if (object1 == nullptr)
		{
			return false;
		}

		//敵情報の差分を取得
		Vector2D diff_location = object1->GetLocation() - object2->GetLocation();

		//当たり判定サイズの大きさ取得
		Vector2D box_ex = object1->GetBoxSize() + object2->GetBoxSize();

		//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
	}
};


