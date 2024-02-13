#include"ObstacleC.h"//障害物（掃除機）
#include"DxLib.h"

ObstacleC::ObstacleC(int type, int handle) :type(type), image(handle), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

ObstacleC::~ObstacleC()
{

}

//初期化処理
void ObstacleC::Initialize()
{
	//出現させるx座標パターンを取得
	//float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	//location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	//box_size = Vector2D(f, f);
	//速さの設定
	//speed =;
	//画像の読み込み
	//image = LoadGraph("Resource/images/.bmp");
}

void ObstacleC::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void ObstacleC::Draw() const
{
	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void ObstacleC::Finalize()
{

}

//位置情報を取得
Vector2D ObstacleC::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D ObstacleC::GetBoxSize() const
{
	return box_size;
}