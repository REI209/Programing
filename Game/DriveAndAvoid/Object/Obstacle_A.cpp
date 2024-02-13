#include"Obstacle_A.h"//��Q���i��@�j
#include"DxLib.h"

ObstacleA::ObstacleA(int type, int handle) :type(type), image(handle), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

ObstacleA::~ObstacleA()
{

}

//����������
void ObstacleA::Initialize()
{
	//�o��������x���W�p�^�[�����擾
	//float random_x = (float)(GetRand(1)*);
	//�����ʒu�̐ݒ�
	//location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	//box_size = Vector2D(f, f);
	//�����̐ݒ�
	//speed=;
	//�摜�̓ǂݍ���
	//image = LoadGraph("Resource/images/.bmp");
	
}

void ObstacleA::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void ObstacleA::Draw() const
{
	//�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void ObstacleA::Finalize()
{

}

//�ʒu�����擾
Vector2D ObstacleA::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D ObstacleA::GetBoxSize() const
{
	return box_size;
}