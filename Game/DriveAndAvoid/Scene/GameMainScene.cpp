#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL),
mileage(0), player(nullptr),
enemy(nullptr)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�����_�l��ǂݍ���
	ReadHighScore();

	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resouce/images/back.bpm");
	barrier_image = LoadGraph("Resouce/images/barrier.png");
	int result = LoadDivGraph("Resouce/images/car.bpm", 3, 3, 1, 63, 120,
		enemy_image);

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resouce/images/back.bpm������܂���\n");
	}
	if (result == -1)
	{
		throw("Resouce/images/car.bpm������܂���\n");
	}
	if (barrier_image == -1)
	{
		throw("Resouce/images/barrier.png������܂���\n");
	}

	//�I�u�W�F�N�g�̐���
	player = new Player;
	enenmy = new Enemy * [10];

	//�I�u�W�F�N�g�̏�����
	Player->Initialize();

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
}

//�X�V����
eSceneType GameMainScene::Update()
{

}