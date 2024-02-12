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

//����������
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

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/car1pol.bmp");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw ("Resource/images/car1pol.bmp������܂���\n");
	}
}

//�X�V����
void Player::Update()
{
	//�X�^�~�i�̏���
	stamina -= speed;

	//�ړ�����
	Movement();

	if (is_active == true)
	{
		//��������
		Acceleration();
	}
	
	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}
}

//�`�揈��
void Player::Draw()
{
	//�v���C���[�摜�̕`��

	// �_�ŗp�̕ϐ��� 1 �𑫂�
	

	// �_�ŗp�̕ϐ��� 60 �ɂȂ��Ă����� 0 �ɂ���
	if (damage == 120)
	{
		damage = 0;
		is_active = true;
	}

	// �_�ŗp�̕ϐ��̒l�� 30 �����̂Ƃ������`�悷��
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

	// �����蔻��m�F�p
	DrawBoxAA(location.x - box_size.x, location.y - box_size.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, TRUE);
	DrawFormatString(0, 0, 0x000000, "%d",damage);

#endif // _DEBUG

}

//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//�����擾����
float Player::GetSpeed() const
{
	return this->speed;
}

//�R���擾����
float Player::GetStamina() const
{
	return this->stamina;
}

//�̗͎擾����
float Player::GetHp() const
{
	return this->hp;
}

//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
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

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//����������
void Player::Acceleration()
{
	// B�{�^����������Ă���ԁA��������
	if (InputControl::GetButton(XINPUT_BUTTON_B) && speed < 7.0f)
	{
		speed += 0.05f;
	}
	else if(speed > 1.0f)
	{
		// B�{�^���𗣂�����A�������������� 
		speed -= 0.05f;
	}
	else
	{
		// ��L�ȊO��1.0f�ŌŒ�
		speed = 1.0f;
	}
}

//�_���[�W���󂯂����̓_�ŏ���
void Player::DamageMove()
{

}