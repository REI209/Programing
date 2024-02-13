#include "Enemy_Roomba.h"
#include "DxLib.h"

Enemy_Roomba::Enemy_Roomba() :is_stan(false), image(NULL), location(0.0f), box_size(0.0f), speed(0.0f), hp(0.0f)
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
	box_size = Vector2D(50.0f, 50.0f);
	speed = 2.0f;
	hp = 10000;

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
	//障害物にあたったら動きを2秒停止させる
	if (is_stan)
	{
		int count_t = 0;
		count_t++;
		speed = 1.0f;

		if (count_t	> 120)
		{
			is_stan = true;
		}
		return;
	}

	//プレイヤーの中心座標のx座標を取得し、自分のの中心座標との差を出す
	//もし一定以上差が開いたら、カウント開始
	//カウント開始後一定時間たって、プレイヤーの中心座標のx座標との差の分、0になるまで加算して

}

void Enemy_Roomba::Draw() const
{
	//画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Enemy_Roomba::Finalize()
{
}

Vector2D Enemy_Roomba::GetLocation() const
{
	return location;
}

Vector2D Enemy_Roomba::GetBoxSize() const
{
	return box_size;
}
