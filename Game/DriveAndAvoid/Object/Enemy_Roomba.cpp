#include "Enemy_Roomba.h"
#include "common.h"
#include "DxLib.h"

Enemy_Roomba::Enemy_Roomba() :is_active(false), image(NULL), boom_image(NULL), hit_count(0), draw_flg(false),
location(0.0f), box_size(0.0f), angle(0.0f), speed(0.0f), diff_x(0.0f), hp(0.0f)
{

}

Enemy_Roomba::~Enemy_Roomba()
{
}

//����������
void Enemy_Roomba::Initialize()
{
	is_active = true;
	location = Vector2D(480.0f, 600.0f);
	box_size = Vector2D(60.0f, 60.0f);
	speed = -0.08f;		//���x
	angle = 0.0f;
	hp = 250;			//�̗�

	//�摜�̓ǂݍ���
	image = LoadGraph(ENEMY_ROOMBA_IMAGE);
	boom_image = LoadGraph(ENEMY_ROOMBA_BOOM_IMAGE);

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/Images/roomba.png������܂���\n");
	}
	if (boom_image == -1)
	{
		throw("Resource/Images/bakuhatsu.png������܂���\n");
	}
}

void Enemy_Roomba::Update(float time,float _diff_x)
{
	//��Q���ɂ��������瓮����1�b��~������
	if (!is_active)
	{
		count_t++;

		speed = -0.02f;
		angle += 0.3f;

		if (count_t > 60)
		{
			is_active = true;
			count_t = 0;
			angle = 0.0f;
		}
	}
	
	if(is_active)
	{
		//���W�̉��Z
		location += Vector2D(TrackingPlayer(_diff_x), this->speed);

		//�c�莞�Ԃɂ���đ��x��ς���
		switch ((int)time)
		{
		case 45:
			speed = -0.1f;
			break;

		case 30:
			speed = -0.28f;
			break;

		case 15:
			speed = -0.32f;
			break;

		default:
			speed = -0.08f;
			break;
		}
	}


	if (hp < 0)
	{
		speed = 0.0f;
		count_t++;
		draw_flg = true;

		if (count_t > 120)
		{
			draw_flg = false;
			count_t = 0;
		}
	}
}

void Enemy_Roomba::Draw() const
{
	if (!nullptr)
	{
		//�摜�̕`��
		if (!draw_flg)
		{
			DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);
		}

		if (draw_flg)
		{
			DrawRotaGraphF(location.x, location.y, 0.5, 0.0, boom_image, TRUE);
		}
	}
}

void Enemy_Roomba::Finalize()
{
}

//�v���C���[�̒ǔ�
float Enemy_Roomba::TrackingPlayer(float _diff_x)
{
	diff_x = _diff_x;
	float move_x = 0.0f;

	if (diff_x < -1.0f || diff_x > 1.0f)
	{
		//������x���W��荷���傫��������(�E��)
		if (0 < diff_x)
		{
			move_x += 2.5f;

			return move_x;
		}
		//������x���W��荷��������������(����)
		else if (0 > diff_x)
		{
			move_x += -2.5f;

			return move_x;
		}
	}
	return move_x;
}


//��Ԑݒ菈��
void Enemy_Roomba::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Enemy_Roomba::DecreaseHp(float value)
{
	this->hp += value;
}

Vector2D Enemy_Roomba::GetLocation() const
{
	return this->location;
}

Vector2D Enemy_Roomba::GetBoxSize() const
{
	return this->box_size;
}

//�̗͎擾����
float Enemy_Roomba::GetHp() const
{
	return this->hp;
}
