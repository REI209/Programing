#include"Obstacle_A.h"//障害物（扇風機）
#include"DxLib.h"

ObstacleA::ObstacleA(int type, int handle) :type(type), image(handle), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

ObstacleA::~ObstacleA()
{

}

//初期化処理
void ObstacleA::Initialize()
{
	//出現させるx座標パターンを取得
	//float random_x = (float)(GetRand(1)*);
	//生成位置の設定
	//location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	//box_size = Vector2D(f, f);
	//速さの設定
	//speed=;
	//画像の読み込み
	//image = LoadGraph("Resource/images/.bmp");
	
}

void ObstacleA::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void ObstacleA::Draw() const
{
	//画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void ObstacleA::Finalize()
{

}

//位置情報を取得
Vector2D ObstacleA::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D ObstacleA::GetBoxSize() const
{
	return box_size;
}