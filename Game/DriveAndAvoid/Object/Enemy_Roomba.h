#pragma once
#include "../Utility/Vector2D.h"

class Enemy_Roomba
{
private:
	bool is_active;	//停止中かどうか
	int image;		//画像データ
	
	int boom_image;
	bool draw_flg;

	int roombabgm;
	Vector2D location;		//位置座標
	Vector2D box_size;		//当たり判定の大きさ

	float angle;

	float speed;		//速度
	float diff_x;	//プレイヤーとのx座標の差
	float hp;		//体力

	int count_t = 0;	//カウント用変数
	int hit_count;

	bool is_boom; //爆発しているかどうか


public:
	Enemy_Roomba();
	~Enemy_Roomba();

	void Initialize();
	void Update(float time, float _diff_x) ;
	void Draw() const;
	void Finalize();

	bool GetActiveFlg() { return is_active; } //有効フラグ取得
	void SetActive(bool flg);
	void DecreaseHp(float value);
	float GetHp() const;            //体力取得

	Vector2D GetLocation() const;
	Vector2D GetBoxSize() const;

	float TrackingPlayer(float _diff_x);

	bool GetBoomFlg() { return is_boom; }
};

