#include"Obstacle_C.h"//障害物（掃除機）
#include"DxLib.h"

Obstacle_C::Obstacle_C(int image) :image(image), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

Obstacle_C::~Obstacle_C()
{

}

//初期化処理
void Obstacle_C::Initialize()
{
	//出現させるx座標パターンを取得
	float random_y = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D( -50.0f, random_y);
	//当たり判定の設定
	box_size = Vector2D(30.0f, 30.0f);//後で調整
	//速さの設定
	speed =2.0f;
	//画像の読み込み
	image = LoadGraph("Resource/images/pet_robot_soujiki_cat.png");
}

void Obstacle_C::Update(float speed)
{

	//位置情報に移動量を加算する
	location += Vector2D(this->speed, 0.0f);
}

void Obstacle_C::Draw() const
{
	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 0.5, 0.0, image, TRUE);
}

void Obstacle_C::Finalize()
{

}

//位置情報を取得
Vector2D Obstacle_C::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Obstacle_C::GetBoxSize() const
{
	return box_size;
}