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
	float random_y = (float)(GetRand(3) * 144 + 85);
	//�����ʒu�̐ݒ�
	location = Vector2D( -50.0f, random_y);
	//�����蔻��̐ݒ�
	box_size = Vector2D(40.0f, 60.0f);//��Œ���
	//�����̐ݒ�
	speed =8.0f;
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/pet_robot_soujiki_cat.png");
}

void Obstacle_C::Update(float speed)
{

	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(this->speed, 0.0f);
}

void Obstacle_C::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.5, 0.0, image, TRUE);

#ifdef _DEBUG

	// �����蔻��m�F�p
	DrawBoxAA(location.x - box_size.x, location.y - box_size.y, location.x + box_size.x, location.y + box_size.y, 0xff0000, FALSE);

#endif // _DEBUG
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