#pragma once
#include "../Utility/Vector2D.h"

class Enemy_Roomba
{
private:
	bool is_active;	//��~�����ǂ���
	int image;		//�摜�f�[�^
	int roombabgm;
	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//�����蔻��̑傫��

	float angle;

	float speed;		//���x
	float diff_x;	//�v���C���[�Ƃ�x���W�̍�
	float hp;		//�̗�

	int count_t = 0;	//�J�E���g�p�ϐ�

public:
	Enemy_Roomba();
	~Enemy_Roomba();

	void Initialize();
	void Update(float time,float _diff_x);
	void Draw() const;
	void Finalize();

	void SetActive(bool flg);
	void DecreaseHp(float value);
	Vector2D GetLocation() const;
	Vector2D GetBoxSize() const;

	float TrackingPlayer(float _diff_x);
};

