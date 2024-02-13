#pragma once

#include"../Utility/Vector2D.h"

class Player
{
private:
	bool is_active;      //�L����Ԃ��H
	int image;           //�摜�f�[�^
	Vector2D location;   //�ʒu���W
	Vector2D box_size;   //�����蔻��̑傫��
	float angle;         //�p�x
	float speed;         //����
	float hp;            //�̗�
	float stamina;       //�X�^�~�i
	int damage;          //�_�ŗp�ϐ�
	float image_size;    //�\������摜�̑傫��
	float ly;            //�_���[�W���󂯂����̃v���C���[Y���W�̈ړ���

public:
	Player();
	~Player();

	void Initialize();   //����������
	void Update();       //�X�V����
	void Draw();         //�`�揈��
	void Finalize();     //�I��������

public:
	void SetActive(bool flg);       //�L���t���O�ݒ�
	void DecreaseHp(float value);   //�̗͌�������
	Vector2D GetLocation() const;   //�ʒu���W�擾
	Vector2D GetBoxSize() const;    //�����蔻��̑傫���擾
	float GetSpeed() const;         //�����擾����
	float GetStamina() const;          //�R���擾
	float GetHp() const;            //�̗͎擾
	bool GetActiveFlg() { return is_active; } //�L���t���O�擾
	int GetDamageTime() { return damage;  }   //�_���[�W���Ԏ擾 

private:
	void Movement();       //�ړ�����
	void Acceleration();   //����������
};