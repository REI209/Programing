#pragma once
#include"DxLib.h"
#include<math.h>
#include"SceneBase.h"

#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include "../Object/Enemy_Roomba.h"
#include "../Object/Obstacle_A.h"
#include "../Object/Obstacle_B.h"
#include "../Object/Obstacle_C.h"
#include "../Object/Family.h"

class GameMainScene :public SceneBase
{
private:
	int time;	//�o�ߎ���
	int counter;		//���ݎ���
	int count_down;

	int high_score;       //�n�C�X�R�A
	int back_ground;      //�w�i�摜
	int barrier_image;    //�o���A�摜
	int mileage;          //���s����
	int mainbgm;          //�Q�[�����C��BGM
	class Player* player;       //�v���C���[
	//Enemy** enemy;        //�G

	class Enemy_Roomba* enemy_roomba;	//�����o
	int roomba_image;	//�����o�̉摜
	float diff_x;		//�v���C���[�Ƃ̍�

	//Obstacle_A** obstacle_a;//��@
	//int obstacle_a_image;//��@�摜


	class Obstacle_B** obstacle_b;//�ςݖ�
	int obstacle_b_image[3];//�ςݖ؉摜


	class Obstacle_C** obstacle_c;//�|���@
	int obstacle_c_image;//�|���@�摜

	class Family** family; //����
	int family_image[2]; //���ԉ摜
	int family_cnt[2]; //�W�߂����Ԃ̐�

	int se[4];

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;


private:
	//�n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighScore();

public:
	//��Q�����m�̓����蔻��
	template <class T, class U>
	inline bool IsObjecHitCheck(T* object1, U* object2)
	{
		//��񂪂Ȃ���΁A�����蔻��𖳎�����
		if (object1 == nullptr)
		{
			return false;
		}

		//�G���̍������擾
		Vector2D diff_location = object1->GetLocation() - object2->GetLocation();

		//�����蔻��T�C�Y�̑傫���擾
		Vector2D box_ex = object1->GetBoxSize() + object2->GetBoxSize();

		//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
		return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
	}
};


