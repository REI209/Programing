#pragma once
#include"DxLib.h"

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include "../Object/Enemy_Roomba.h"
//#include "../Object/Obstacle_A.h"
#include "../Object/Obstacle_B.h"
//#include "../Object/Obstacle_C.h"
class GameMainScene :public SceneBase
{
private:
	int time;	//�o�ߎ���
	int counter;		//���ݎ���

	int high_score;       //�n�C�X�R�A
	int back_ground;      //�w�i�摜
	int barrier_image;    //�o���A�摜
	int mileage;          //���s����
	int enemy_image[3];   //�G�摜
	int enemy_count[3];   //�ʂ�߂����G�J�E���g
	Player* player;       //�v���C���[
	//Enemy** enemy;        //�G

	Enemy_Roomba* enemy_roomba;	//�����o
	int roomba_image;	//�����o�̉摜

	Obstacle_B** obstacle_b;//�ςݖ�
	int obstacle_b_image;//�ςݖ؉摜

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
	//�����蔻��
	bool IsHitCheck(Player* p, Enemy* e);
};