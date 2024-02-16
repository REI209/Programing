#pragma once

#include"../Utility/Vector2D.h"

class Wind
{
private:
	int type;            //�E������
	int image;           //�摜
	float speed;         //����
	Vector2D location;   //�ʒu���
	Vector2D box_size;   //�����蔻��̑傫��

public:
	Wind(int type,int image);
	~Wind();

	void Initialize();         //����������
	void Update(float speed);  //�X�V����
	void Draw() const;         //�`�揈��
	void Finalize();           //�I��������

	Vector2D GetLocation() const;   //�ʒu���̎擾
	Vector2D GetBoxSize() const;    //�����蔻��̑傫�����擾
};