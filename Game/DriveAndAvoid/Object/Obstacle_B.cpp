#include"Obstacle_B.h"//障害物（積み木）
#include"DxLib.h"

Obstacle_B::Obstacle_B(int image) :image(image), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

Obstacle_B::~Obstacle_B()
{

}

//初期化処理
void Obstacle_B::Initialize()
{
	//出現させるx座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	box_size = Vector2D(50.0f, 50.0f);
	//速さの設定
	speed =8.0f;
}

void Obstacle_B::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Obstacle_B::Draw() const
{
	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 0.1, 0.0, image, TRUE);
}

void Obstacle_B::Finalize()
{

}

//敵のタイプを取得
//int Obstacle_B::GetType() const
//{
//	return type;//3?
//}

//位置情報を取得
Vector2D Obstacle_B::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Obstacle_B::GetBoxSize() const
{
	return box_size;
}