#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f),
speed(0.0f), hp(0.0f), stamina(0.0f),damage(0)
{

}

Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(20.0f, 20.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 1000;
	stamina = 20000;
	damage = 0;

	//画像の読み込み
	image = LoadGraph("Resource/images/car1pol.bmp");

	//エラーチェック
	if (image == -1)
	{
		throw ("Resource/images/car1pol.bmpがありません\n");
	}
}

//更新処理
void Player::Update()
{
	//スタミナの処理
	stamina -= speed;

	//移動処理
	Movement();

	if (is_active == true)
	{
		//加減処理
		Acceleration();
	}
	
	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画

	// 点滅用の変数に 1 を足す
	

	// 点滅用の変数が 60 になっていたら 0 にする
	if (damage == 120)
	{
		damage = 0;
		is_active = true;
	}

	// 点滅用の変数の値が 30 未満のときだけ描画する
	if (is_active == false)
	{
		if (++damage < 10)
		{
			DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
		}
		if (damage > 70)
		{
			DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
		}
		
	}
	else if(is_active == true)
	{
		DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
	}

#ifdef _DEBUG

	// 当たり判定確認用
	DrawBoxAA(location.x - box_size.x, location.y - box_size.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, TRUE);
	DrawFormatString(0, 0, 0x000000, "%d",damage);

#endif // _DEBUG

}

//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed() const
{
	return this->speed;
}

//燃料取得処理
float Player::GetStamina() const
{
	return this->stamina;
}

//体力取得処理
float Player::GetHp() const
{
	return this->hp;
}

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//十字移動処理
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-1.0f, 0.0f);
		angle = -DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(1.0f, 0.0f);
		angle = DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -1.0f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 1.0f);
	}
	location += move;

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//加減速処理
void Player::Acceleration()
{
	// Bボタンが押されている間、加速する
	if (InputControl::GetButton(XINPUT_BUTTON_B) && speed < 7.0f)
	{
		speed += 0.05f;
	}
	else if(speed > 1.0f)
	{
		// Bボタンを離したら、少しずつ減速する 
		speed -= 0.05f;
	}
	else
	{
		// 上記以外は1.0fで固定
		speed = 1.0f;
	}
}

//ダメージを受けた時の点滅処理
void Player::DamageMove()
{

}