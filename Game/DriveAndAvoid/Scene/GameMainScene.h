#pragma once
#include"DxLib.h"

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
	int enemy_image[3];   //�G�摜
	int enemy_count[3];   //�ʂ�߂����G�J�E���g
	int mainbgm;          //�Q�[�����C��BGM
	int roombabgm;        //�����o����BGM
	Player* player;       //�v���C���[
	//Enemy** enemy;        //�G

	Enemy_Roomba* enemy_roomba;	//�����o
	int roomba_image;	//�����o�̉摜
	float diff_x;		//�v���C���[�Ƃ̍�

	Obstacle_A** obstacle_a;//��@
	int obstacle_a_image;//��@�摜


	Obstacle_B** obstacle_b;//�ςݖ�
	int obstacle_b_image;//�ςݖ؉摜


	Obstacle_C** obstacle_c;//�|���@
	int obstacle_c_image;//�|���@�摜

	Family** family; //����
	int family_image[2]; //���ԉ摜
	int family_cnt[2]; //�W�߂����Ԃ̐�

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
	//�v���C���[�ƓG(�����o)�̓����蔻��
	bool IsHitCheck(Player* p, Enemy_Roomba* e);
	//�v���C���[�Ə�Q���̓����蔻��
	template <class T>
	bool IsObjectHitCheck_P(Player* p, T* object);
	//�G(�����o)��Q���̓����蔻��
	template <class T>
	bool IsObjecHitCheck_E(Enemy_Roomba* e, T* object);
	//��Q�����m�̓����蔻��
	template <class T>
	bool IsObjecHitCheck_O(T* object1, T* object2);
};


