#pragma once
#include "../Utility/Vector2D.h"

class Enemy_Roomba
{
private:
	bool is_active;	//��~�����ǂ���
	int image;		//�摜�f�[�^
	
	int boom_image;
	bool draw_flg;

	int roombabgm;
	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//�����蔻��̑傫��

	float angle;

	float speed;		//���x
	float diff_x;	//�v���C���[�Ƃ�x���W�̍�
	float hp;		//�̗�

	int count_t = 0;	//�J�E���g�p�ϐ�
	int hit_count;

	bool is_boom; //�������Ă��邩�ǂ���


public:
	Enemy_Roomba();
	~Enemy_Roomba();

	void Initialize();
	void Update(float time, float _diff_x) ;
	void Draw() const;
	void Finalize();

	bool GetActiveFlg() { return is_active; } //�L���t���O�擾
	void SetActive(bool flg);
	void DecreaseHp(float value);
	float GetHp() const;            //�̗͎擾

	Vector2D GetLocation() const;
	Vector2D GetBoxSize() const;

	float TrackingPlayer(float _diff_x);

	bool GetBoomFlg() { return is_boom; }
};

