#pragma once
#include "../Utility/Vector2D.h"

class Enemy_Roomba
{
private:
	bool is_stan;	//停止中かどうか
	int image;		//画像データ
	Vector2D location;		//位置座標
	Vector2D box_size;		//当たり判定の大きさ
	float speed;	//速度
	float hp;		//体力

public:
	Enemy_Roomba();
	~Enemy_Roomba();

	void Initialize();
	void Update(float time);
	void Draw() const;
	void Finalize();

	Vector2D GetLocation() const;
	Vector2D GetBoxSize() const;


};

