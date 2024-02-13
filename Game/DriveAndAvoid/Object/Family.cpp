#include "Family.h"
#include "DxLib.h"

Family::Family(int type,int image) : type(0),image(image), speed(0.0f), location(0.0f), box_size(0.0f)
{

}

Family::~Family()
{

}

void Family::Initialize()
{
	//出現させるx座標パターンを取得
	float random_x = (float)(GetRand(4) * 196 + 100);
	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	box_size = Vector2D(50.0f, 50.0f);
	//速さの設定
	speed = 1.0f;
}

void Family::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed);
}

void Family::Draw() const
{
	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 0.5, 0.0, image, TRUE);
}

void Family::Finalize()
{
	
}

int Family::GetType() const
{
	return type;
}

Vector2D Family::GetLocation() const
{
	return this->location;
}

Vector2D Family::GetBoxSize() const
{
	return this->box_size;
}
