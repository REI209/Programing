#pragma once
#include"DxLib.h"

#include"../Object/Player.h"
#include"SceneBase.h"
#include<math.h>


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

	int bonus_image;		//�{�[�i�X�摜
	float bonus_size;			//�T�C�Y�ύX


	int main_sound;       //�Q�[�����C���T�E���h
	int gameover_sound;   //�Q�[���I�[�o�[�T�E���h
	int enemy_count[3];   //�ʂ�߂����G�J�E���g
	int mainbgm;          //�Q�[�����C��BGM
	class Player* player;       //�v���C���[

	class Enemy_Roomba* enemy_roomba;	//�����o
	int roomba_image;	//�����o�̉摜
	float diff_x;		//�v���C���[�Ƃ̍�

	class Obstacle_A** obstacle_a;//��@
	int obstacle_a_image;//��@�摜


	class Obstacle_B** obstacle_b;//�ςݖ�
	int obstacle_b_image[3];//�ςݖ؉摜


	class Obstacle_C** obstacle_c;//�|���@
	int obstacle_c_image;//�|���@�摜

	class Family** family; //����
	int family_image[2]; //���ԉ摜
	int family_cnt[2]; //�W�߂����Ԃ̐�

	class Wind** wind;  //��
	int wind_image[2]; //���摜

public:
	bool bonus_flg;

public:
	GameMainScene* main;

	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	bool GetBonusFlg(bool flg) { return bonus_flg = flg; }


private:
	//�n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighScore();
	//�v���C���[�ƓG(�����o)�̓����蔻��
	bool IsHitCheck(Player* p, class Enemy_Roomba* e);
	
	//�����蔻��
	template <class T, class U>
	bool IsObjecHitCheck_O(T* object1, U* object2)
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


