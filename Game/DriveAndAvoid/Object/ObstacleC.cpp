#include"ObstacleC.h"//��Q���i�|���@�j
#include"DxLib.h"

ObstacleC::ObstacleC(int type, int handle) :type(type), image(handle), speed(0.0f),
location(0.0f), box_size(0.0f)
{

}

ObstacleC::~ObstacleC()
{

}

//����������
void ObstacleC::Initialize()
{
	//�o��������x���W�p�^�[�����擾
	//float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	//location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	//box_size = Vector2D(f, f);
	//�����̐ݒ�
	//speed =;
	//�摜�̓ǂݍ���
	//image = LoadGraph("Resource/images/.bmp");
}

void ObstacleC::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void ObstacleC::Draw() const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void ObstacleC::Finalize()
{

}

//�ʒu�����擾
Vector2D ObstacleC::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D ObstacleC::GetBoxSize() const
{
	return box_size;
}