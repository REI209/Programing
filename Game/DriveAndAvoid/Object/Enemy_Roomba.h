#pragma once
#include "../Utility/Vector2D.h"
#include "../Scene/GameMainScene.h"

class GameMainScene;

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
	int hit_count;		//�q�b�g�J�E���g

	int boom_image;
	bool draw_flg;

public:
	bool bonus_flg;

public:
	Enemy_Roomba();
	~Enemy_Roomba();

	void Initialize();
	void Update(GameMainScene* main,float time,float _diff_x);
	void Draw() const;
	void Finalize();

	void SetActive(bool flg);
	void DecreaseHp(float value);
	Vector2D GetLocation() const;
	Vector2D GetBoxSize() const;

	float TrackingPlayer(float _diff_x);

};

