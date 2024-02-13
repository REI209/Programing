#include"Obstacle_A.h"//��Q���i��@�j
#include"DxLib.h"

Obstacle_A::Obstacle_A(int image) :image(image), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

Obstacle_A::~Obstacle_A()
{

}

//����������
void Obstacle_A::Initialize()
{
	//�o��������x���W�p�^�[�����擾
	float random_x = (float)(GetRand(1) * 800 + 100);
	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(50.0f, 50.0f);
	//�����̐ݒ�
	speed=5.0f;
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/kaden_senpuki.png");
}

void Obstacle_A::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Obstacle_A::Draw() const
{
	//�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.3, 0.0, image, TRUE);
}

void Obstacle_A::Finalize()
{

}

//�ʒu�����擾
Vector2D Obstacle_A::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Obstacle_A::GetBoxSize() const
{
	return box_size;
}