#pragma once
#include "../Utility/Vector2D.h"

class Enemy_Roomba
{
private:
	bool is_stan;	//��~�����ǂ���
	int image;		//�摜�f�[�^
	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//�����蔻��̑傫��
	float speed;	//���x
	float hp;		//�̗�

public:
	Enemy_Roomba();
	~Enemy_Roomba();

	void Initialize();
	void Update(float time);
	void Draw() const;
	void Finalize();

	Vector2D GetLocation() const;
	Vector2D GetBoxSize() const;


};

