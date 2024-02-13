#include "Enemy_Roomba.h"
#include "Player.h"
#include "DxLib.h"

Enemy_Roomba::Enemy_Roomba() :is_stan(false), image(NULL), location(0.0f), box_size(0.0f),
speed(0.0f), diff_x(0.0f), hp(0.0f)
{

}

Enemy_Roomba::~Enemy_Roomba()
{
}

//初期化処理
void Enemy_Roomba::Initialize()
{
	is_stan = false;
	location = Vector2D(250.0f, 440.0f);
	box_size = Vector2D(25.0f, 25.0f);
	speed = 0.2f;		//速度
	hp = 10000;			//体力

	//画像の読み込み
	image = LoadGraph("Resource/images/roomba.bmp");
	//エラーチェック
	if (image == -1)
	{
		throw("Resource/image/roomba.bmpがありません\n");
	}
}

void Enemy_Roomba::Update(float time)
{
	//プレイヤーの中心座標のx座標を取得し、自分のの中心座標との差を出す
//もし一定以上差が開いたら、カウント開始
//カウント開始後一定時間たって、プレイヤーの中心座標のx座標との差の分、0になるまで加算して
	
	switch ((int)time)
	{
	case 45:
		break;

	case 30:
		break;

	case 15:
		break;
	}


	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed);


	//障害物にあたったら動きを2秒停止させる
	if (is_stan)
	{
		int count_t = 0;
		count_t++;
		speed = 2.0f;

		if (count_t	> 120)
		{
			is_stan = true;
		}
		return;
	}


}

void Enemy_Roomba::Draw() const
{
	//画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	DrawBoxAA(location.x - box_size.x, location.y - box_size.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, FALSE);
}

void Enemy_Roomba::Finalize()
{
}

Vector2D Enemy_Roomba::GetLocation() const
{
	return this->location;
}

Vector2D Enemy_Roomba::GetBoxSize() const
{
	return this->box_size;
}
