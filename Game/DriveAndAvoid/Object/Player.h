#pragma once

#include"../Utility/Vector2D.h"

class Player
{
private:
	bool is_active;      //有効状態か？
	int image;           //画像データ
	Vector2D location;   //位置座標
	Vector2D box_size;   //当たり判定の大きさ
	float angle;         //角度
	float speed;         //速さ
	float hp;            //体力
	float stamina;       //スタミナ
	int damage;          //点滅用変数
	float image_size;    //表示する画像の大きさ
	float ly;            //ダメージを受けた時のプレイヤーY座標の移動量

public:
	Player();
	~Player();

	void Initialize();   //初期化処理
	void Update();       //更新処理
	void Draw();         //描画処理
	void Finalize();     //終了時処理

public:
	void SetActive(bool flg);       //有効フラグ設定
	void DecreaseHp(float value);   //体力減少処理
	Vector2D GetLocation() const;   //位置座標取得
	Vector2D GetBoxSize() const;    //当たり判定の大きさ取得
	float GetSpeed() const;         //速さ取得処理
	float GetStamina() const;          //燃料取得
	float GetHp() const;            //体力取得
	bool GetActiveFlg() { return is_active; } //有効フラグ取得
	int GetDamageTime() { return damage;  }   //ダメージ時間取得 

private:
	void Movement();       //移動処理
	void Acceleration();   //加減速処理
};