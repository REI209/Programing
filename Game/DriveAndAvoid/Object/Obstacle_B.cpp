#include"Obstacle_B.h"//��Q���i�ςݖ؁j
#include"DxLib.h"

ObstacleB::ObstacleB(int type, int handle) :type(type), image(handle), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

ObstacleB::~ObstacleB()
{

}

//����������
void ObstacleB::Initialize()
{
	//�摜����
	// int type=[3]
	// 
	//�o��������x���W�p�^�[�����擾
	//float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	//location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	//box_size = Vector2D(40f, 40f);
	//�����̐ݒ�
	//speed =;
}

void ObstacleB::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void ObstacleB::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void ObstacleB::Finalize()
{

}

//�G�̃^�C�v���擾
int ObstacleB::GetType() const
{
	return type;//3?
}

//�ʒu�����擾
Vector2D ObstacleB::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D ObstacleB::GetBoxSize() const
{
	return box_size;
}