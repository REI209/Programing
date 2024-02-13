#pragma once

#include"../Utility/Vector2D.h"

class ObstacleA
{
private:
	int type;            //�^�C�v
	int image;           //�摜
	float speed;         //����
	Vector2D location;   //�ʒu���
	Vector2D box_size;   //�����蔻��̑傫��

public:
	ObstacleA(int type, int handle);
	~ObstacleA();

	void Initialize();         //����������
	void Update(float speed);  //�X�V����
	void Draw() const;         //�`�揈��
	void Finalize();           //�I��������

	Vector2D GetLocation() const;   //�ʒu���̎擾
	Vector2D GetBoxSize() const;    //�����蔻��̑傫�����擾
};