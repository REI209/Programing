#include"Obstacle_C.h"//��Q���i�|���@�j
#include"DxLib.h"

Obstacle_C::Obstacle_C(int image) :image(image), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

Obstacle_C::~Obstacle_C()
{

}

//����������
void Obstacle_C::Initialize()
{
	//�o��������x���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(50.0f, 50.0f);
	//�����̐ݒ�
	speed =10.0f;
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/pet_robot_soujiki_cat.png");
}

void Obstacle_C::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Obstacle_C::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.5, 0.0, image, TRUE);
}

void Obstacle_C::Finalize()
{

}

//�ʒu�����擾
Vector2D Obstacle_C::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Obstacle_C::GetBoxSize() const
{
	return box_size;
}