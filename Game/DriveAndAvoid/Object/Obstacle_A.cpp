#include"Obstacle_A.h"//障害物（扇風機）
#include"DxLib.h"

Obstacle_A::Obstacle_A(int type,int image) :image(image),type(type),speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

Obstacle_A::~Obstacle_A()
{

}

//初期化処理
void Obstacle_A::Initialize()
{
	//出現させるx座標パターンを取得
	float random_x = (float)(GetRand(1) * (245 * 5) + 35);
	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	////当たり判定の設定
	box_size = Vector2D(73.0f, 87.0f);
	//速さの設定
	speed=5.0f;
	//画像の読み込み
	image = LoadGraph("Resource/images/kaden_senpuki.png");
}

void Obstacle_A::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Obstacle_A::Draw() const
{
	switch(type)
	{
	case 0:
		break;
	case 1:
		break;
	}
	//画像の描画
	DrawRotaGraphF(location.x, location.y, 0.3, 0.0, image, TRUE);

#ifdef _DEBUG

	// 当たり判定確認用
	DrawBoxAA(location.x - box_size.x, location.y - box_size.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, FALSE);

#endif // _DEBUG
}

void Obstacle_A::Finalize()
{

}

//位置情報を取得
Vector2D Obstacle_A::GetLocation() const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Obstacle_A::GetBoxSize() const
{
	return box_size;
}