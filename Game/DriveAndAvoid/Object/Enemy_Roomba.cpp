#include "Enemy_Roomba.h"
#include "common.h"
#include "DxLib.h"

Enemy_Roomba::Enemy_Roomba() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
speed(0.0f), diff_x(0.0f), hp(0.0f)
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
	box_size = Vector2D(25.0f, 25.0f);
	speed = -0.08f;		//���x
	hp = 10000;			//�̗�


	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/Images/roomba.png");
	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/Images/roomba.png������܂���\n");
	}
}

void Enemy_Roomba::Update(float time,float _diff_x)
{
	//�v���C���[�̒��S���W��x���W���擾���A�����̂̒��S���W�Ƃ̍����o��
//�������ȏ㍷���J������A�J�E���g�J�n
//�J�E���g�J�n���莞�Ԃ����āA�v�����[�̒��S���W��x���W�Ƃ̍��̕��A0�ɂȂ�܂ŉ��Z����
	

	//�ʒu���Ɉړ��ʂ����Z����	//�v���C���[��x���W�Ƃ̍����擾
	location += Vector2D(TrackingPlayer(_diff_x), this->speed);
	


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
	}


	//��Q���ɂ��������瓮����2�b��~������
	if (!is_active)
	{
		int count_t = 0;
		count_t++;
		speed = 2.0f;

		if (count_t	> 120)
		{
			is_active = false;
		}
		return;
	}


}

void Enemy_Roomba::Draw() const
{
	//�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	DrawBoxAA(location.x - box_size.x, location.y - box_size.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, FALSE);
	DrawFormatString(510, 300, GetColor(255, 255, 255), "diff_x:%f", diff_x);
	DrawFormatString(510, 350, GetColor(255, 255, 255), "location.x:%f location.y:%f", location.x, location.y);


}

void Enemy_Roomba::Finalize()
{
}

//��Ԑݒ菈��
void Enemy_Roomba::SetActive(bool flg)
{
	this->is_active = flg;
}


Vector2D Enemy_Roomba::GetLocation() const
{
	return this->location;
}

Vector2D Enemy_Roomba::GetBoxSize() const
{
	return this->box_size;
}

float Enemy_Roomba::TrackingPlayer(float _diff_x)
{
	diff_x = _diff_x;
	float move_x = 0.0f;

	if (diff_x < -1.0f || diff_x>1.0f)
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

}
