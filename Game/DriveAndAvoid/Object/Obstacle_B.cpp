#include"Obstacle_B.h"//障害物（積み木）
#include"DxLib.h"

ObstacleB::ObstacleB(int type, int handle) :type(type), image(handle), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

ObstacleB::~ObstacleB()
{

}

//初期化処理
void ObstacleB::Initialize()
{
	//画像分割
	// int type=[3]
	// 
	//出現させるx座標パターンを取得
	//float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	//location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	//box_size = Vector2D(40f, 40f);
	//速さの設定
	//speed =;
}

void ObstacleB::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void ObstacleB::Draw() const
{
	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void ObstacleB::Finalize()
{

}

//敵のタイプを取得
int ObstacleB::GetType() const
{
	return type;//3?
}

//位置情報を取得
Vector2D ObstacleB::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D ObstacleB::GetBoxSize() const
{
	return box_size;
}