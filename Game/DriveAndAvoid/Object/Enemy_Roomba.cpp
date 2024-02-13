#include "Enemy_Roomba.h"
#include "DxLib.h"

Enemy_Roomba::Enemy_Roomba() :is_stan(false), image(NULL), location(0.0f), box_size(0.0f), speed(0.0f), hp(0.0f)
{
}

Enemy_Roomba::~Enemy_Roomba()
{
}

//����������
void Enemy_Roomba::Initialize()
{
	is_stan = false;
	location = Vector2D(250.0f, 440.0f);
	box_size = Vector2D(50.0f, 50.0f);
	speed = 2.0f;
	hp = 10000;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/roomba.bmp");
	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/image/roomba.bmp������܂���\n");
	}
}

void Enemy_Roomba::Update(float time)
{
	//��Q���ɂ��������瓮����2�b��~������
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

	//�v���C���[�̒��S���W��x���W���擾���A�����̂̒��S���W�Ƃ̍����o��
	//�������ȏ㍷���J������A�J�E���g�J�n
	//�J�E���g�J�n���莞�Ԃ����āA�v���C���[�̒��S���W��x���W�Ƃ̍��̕��A0�ɂȂ�܂ŉ��Z����

}

void Enemy_Roomba::Draw() const
{
	//�摜�̕`��
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
