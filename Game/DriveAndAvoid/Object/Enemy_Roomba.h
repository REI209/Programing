#pragma once
#include "../Utility/Vector2D.h"
#include "../Scene/GameMainScene.h"

class GameMainScene;

class Enemy_Roomba
{
private:
	bool is_active;	//停止中かどうか
	int image;		//画像データ
	int roombabgm;
	Vector2D location;		//位置座標
	Vector2D box_size;		//当たり判定の大きさ

	float angle;

	float speed;		//速度
	float diff_x;	//プレイヤーとのx座標の差
	float hp;		//体力

	int count_t = 0;	//カウント用変数
	int hit_count;		//ヒットカウント

	int boom_image;
	bool draw_flg;

public:
	bool bonus_flg;

public:
	Enemy_Roomba();
	~Enemy_Roomba();

	void Initialize();
	void Update(GameMainScene* main,float time,float _diff_x);
	void Draw() const;
	void Finalize();

	void SetActive(bool flg);
	void DecreaseHp(float value);
	Vector2D GetLocation() const;
	Vector2D GetBoxSize() const;

	float TrackingPlayer(float _diff_x);

};

