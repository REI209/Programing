#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

Player::Player() :is_active(false), image{}, location(0.0f), box_size(0.0f), angle(0.0f),
speed(0.0f), hp(0.0f), stamina(0.0f),damage(0),image_size(0.0f),ly(0.0f), acceleration_flg(false), room_anim(0),time(0),
fam_flg(false)
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
	box_size = Vector2D(50.0f, 50.0f);
	angle = 0.0f;
	speed = 5.0f;
	hp = 230.0f;
	stamina = 50.0f;
	damage = 0;
	image_size = 0.5f;
	ly = 0.0f;
	fam_flg = false;
	room_anim = 0;
	acceleration_flg = false;
	time = 0;

	//�摜�̓ǂݍ���
	image[0] = LoadGraph("Resource/Images/player.PNG");
	image[1] = LoadGraph("Resource/Images/player_bom.PNG");


	//�G���[�`�F�b�N
	if (image[0] == -1)
	{
		throw ("Resource/images/player.png������܂���\n");
	}
	if (image[1] == -1)
	{
		throw ("Resource/images/player_bom.PNG������܂���\n");
	}
}

//�X�V����
void Player::Update()
{

	if (!is_active)
	{
		if (room_anim != 0)
		{
			RoombaAnim();
		}

		damage++;
		speed = 1.0f;

		if (damage > 60)
		{
			is_active = true;
			damage = 0;
		}
	}

	if (is_active)
	{

		//�ړ�����
		Movement();

		//��������
		Acceleration();
	}
	
	box_size = Vector2D(65.0f * image_size, 65.0f * image_size);

	if (hp <= 0.0f)
	{
		hp = 0.0f;
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
			DrawRotaGraphF(location.x, location.y, image_size, angle, image[0], TRUE);
		}
		if (damage > 20 && damage < 30)
		{
			//�v���C���[�摜�̕`��
			DrawRotaGraphF(location.x, location.y, image_size, angle, image[0], TRUE);
		}
		if (damage > 40 && damage < 50)
		{
			//�v���C���[�摜�̕`��
			DrawRotaGraphF(location.x, location.y, image_size, angle, image[0], TRUE);
		}
		
	}
	else if(is_active)
	{
		//�v���C���[�摜�̕`��
		DrawRotaGraphF(location.x, location.y, image_size, angle, image[0], TRUE);
	}
	else if (room_anim != 0)
	{
		//�v���C���[�摜�̕`��
		DrawRotaGraphF(location.x, location.y, 0.1, angle, image[1], TRUE);
	}

#ifdef _DEBUG

	// �����蔻��m�F�p
	/*DrawBoxAA(location.x - box_size.x, location.y - box_size.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, FALSE);
	DrawFormatString(0, 0, 0x000000, "%f",location.y);*/
	DrawFormatString(0, 50, 0xffffff, "%f", hp);


#endif // _DEBUG

}

//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image[0]);
	DeleteGraph(image[1]);

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
		move += Vector2D(-(3.0f / image_size), 0.0f);
		angle = -DX_PI_F / 30;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D((3.0f / image_size), 0.0f);
		angle = DX_PI_F / 30;
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1280.0f - box_size.x) || (location.y < box_size.y) || (location.y >= 720.0f - box_size.y))
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
	if (InputControl::GetButton(XINPUT_BUTTON_B) == true && stamina > 0.0f)
	{

		if (speed < 8.0f && stamina > 0.0f)
		{
			speed += 0.05f;
		}
		
		if (location.y > 100.0f && stamina > 0.0f)
		{
			ly += 0.05f;
			location.y += -ly;
		}

		if (stamina > 0.0f)
		{
			stamina -= 0.01f * speed;
		}

		if (acceleration_flg == false && stamina > 0.0f)
		{
			acceleration_flg = true;
		}

	}
	else if(stamina <= 0.0f)
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

		if (stamina > 0.0f)
		{
			if (acceleration_flg == true)
			{
				if (ly > 0)
				{
					time = 180;
					ly = 0;
					acceleration_flg = false;
				}
			}

			if (time > 0)
			{
				time--;
				if (location.y < 380.0f)
				{
					location.y += 2.0f;
				}
			}
		}

		if (stamina <= 50.0f)
		{
			stamina += 0.1f;
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

		if (stamina > 0.0f)
		{
			if (acceleration_flg == true)
			{
				if (ly > 0)
				{
					time = 180;
					ly = 0;
					acceleration_flg = false;
				}
			}

			if (time > 0)
			{
				time--;
				if (location.y < 380.0f)
				{
					location.y += 2.0f;
				}
			}
		}

		if (stamina <= 50.0f)
		{
			stamina += 0.1f;
		}
	}
}

void Player::RoombaAnim()
{

	if (room_anim < 60)
	{
		room_anim++;
	}
	else
	{
		room_anim = 0;
	}
	
}