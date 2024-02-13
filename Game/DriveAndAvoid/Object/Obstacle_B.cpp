#include"Obstacle_B.h"//��Q���i�ςݖ؁j
#include"DxLib.h"

Obstacle_B::Obstacle_B(int image) :image(image), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

Obstacle_B::~Obstacle_B()
{

}

//����������
void Obstacle_B::Initialize()
{
	//�o��������x���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(50.0f, 50.0f);
	//�����̐ݒ�
	speed =8.0f;
}

void Obstacle_B::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Obstacle_B::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.1, 0.0, image, TRUE);
}

void Obstacle_B::Finalize()
{

}

//�G�̃^�C�v���擾
//int Obstacle_B::GetType() const
//{
//	return type;//3?
//}

//�ʒu�����擾
Vector2D Obstacle_B::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Obstacle_B::GetBoxSize() const
{
	return box_size;
}