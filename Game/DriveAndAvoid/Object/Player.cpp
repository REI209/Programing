#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f),
speed(0.0f), hp(0.0f), stamina(0.0f),damage(0),image_size(0.0f),sp(0.0f)
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
	box_size = Vector2D(40.0f, 40.0f);
	angle = 0.0f;
	speed = 5.0f;
	hp = 1000;
	stamina = 20000;
	damage = 0;
	image_size = 1.0f;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/player.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw ("Resource/images/player.png������܂���\n");
	}
}

//�X�V����
void Player::Update()
{

	if (!is_active)
	{
		damage++;
		speed = 1.0f;

		if (damage > 60)
		{
			is_active = true;
			damage = 0;
		}
	}

	//�X�^�~�i�̏���
	stamina -= speed;

	if (stamina <= 0.1f)
	{
		stamina = 0.0f;
	}

	if (is_active)
	{
		//�ړ�����
		Movement();

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
	// �_�ŗp�̕ϐ��̒l�� 30 �����̂Ƃ������`�悷��
	if (!is_active)
	{
		if (damage < 10)
		{
			//�v���C���[�摜�̕`��
			DrawRotaGraphF(location.x, location.y, image_size, angle, image, TRUE);
		}
		if (damage > 20 && damage < 30)
		{
			//�v���C���[�摜�̕`��
			DrawRotaGraphF(location.x, location.y, image_size, angle, image, TRUE);
		}
		if (damage > 40 && damage < 50)
		{
			//�v���C���[�摜�̕`��
			DrawRotaGraphF(location.x, location.y, image_size, angle, image, TRUE);
		}
		
	}
	else if(is_active)
	{
		//�v���C���[�摜�̕`��
		DrawRotaGraphF(location.x, location.y, image_size, angle, image, TRUE);
	}

#ifdef _DEBUG

	// �����蔻��m�F�p
	DrawBoxAA(location.x - box_size.x, location.y - box_size.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, FALSE);
	DrawFormatString(0, 0, 0x000000, "%f",location.y);
	DrawFormatString(0, 50, 0x000000, "%f", sp);


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
		move += Vector2D(-3.0f, 0.0f);
		angle = -DX_PI_F / 30;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(3.0f, 0.0f);
		angle = DX_PI_F / 30;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -3.0f);
	}
	/*if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 3.0f);
	}*/
	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1280.0f - 340.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}

	if (location.y < 100.0f)
	{
		location.y = 100.0f;
	}
}

//����������
void Player::Acceleration()
{
	// B�{�^����������Ă���ԁA��������
	if (InputControl::GetButton(XINPUT_BUTTON_B))
	{
		if (speed < 8.0f)
		{
			speed += 0.05f;
		}
		
		if (location.y > 100.0f)
		{
			sp += 0.05f;
			location.y += -sp;
		}
	}
	else
	{
		if (speed > 5.0f)
		{
			// B�{�^���𗣂�����A�������������� 
			speed -= 0.05f;
		}
		else
		{
			// ��L�ȊO��1.0f�ŌŒ�
			speed = 5.0f;
		}

		

		if (sp > 0)
		{
			sp = 0;
		}
	}
}