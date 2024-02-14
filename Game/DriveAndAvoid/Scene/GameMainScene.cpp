#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL),mileage(0), player(nullptr), enemy_roomba(nullptr),diff_x(0.0),obstacle_a(nullptr), obstacle_b(nullptr), obstacle_c(nullptr), family(nullptr)//,enemy(nullptr)
{

	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}

	for (int i = 0; i < 2; i++)
	{
		family_image[i] = NULL;
	}

	roomba_image = NULL;


}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�����_�l��ǂݍ���
	ReadHighScore();

	//�������Ԃ̐ݒ�(�b) 
	counter = 60;


	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/Images/back_img.png");
	barrier_image = LoadGraph("Resource/Images/barrier.png");
	int result = LoadDivGraph("Resource/Images/car.bmp", 3, 3, 1, 63, 120,
		enemy_image);

	obstacle_a_image = LoadGraph("Resource/Images/kaden_senpuki.png");
	obstacle_b_image= LoadGraph("Resource/Images/omocha_tsumiki.png");
	obstacle_c_image = LoadGraph("Resource/Images/pet_robot_soujiki_cat.png");

	family_image[0] = LoadGraph("Resource/Images/IMG_0111.png");
	family_image[1] = LoadGraph("Resource/Images/IMG_0113.png");

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/Images/back_img.png������܂���\n");
	}
	if (result == -1)
	{
		throw("Resource/Images/car.bmp������܂���\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/Images/barrier.png������܂���\n");
	}
	if (obstacle_a)
	{
		throw("Resource/Images/kaden_senpuki.png������܂���\n");
	}
	if (obstacle_b)
	{
		throw("Resource/Images/omocha_tumiki.png������܂���\n");
	}
	if (obstacle_c)
	{
		throw("Resource/Images/pet_robot_soujiki_cat.png������܂���\n");
	}
	if (family_image[0] == -1)
	{
		throw("Resource/Images/IMG_0111.png������܂���\n");
	}
	if (family_image[1] == -1)
	{
		throw("Resource/Images/IMG_0113.png������܂���\n");
	}
	//�I�u�W�F�N�g�̐���
	player = new Player;
	//enemy = new Enemy * [10];

	enemy_roomba = new Enemy_Roomba;
	obstacle_a = new Obstacle_A * [10];
	obstacle_b = new Obstacle_B*[10];
	obstacle_c = new Obstacle_C * [10];

	family = new Family * [10];

	//�I�u�W�F�N�g�̏�����
	player->Initialize();
	enemy_roomba->Initialize();
	
	//obstacle_a->Initialize();
	//obstacle_b->Initialize();
	//obstacle_c->Initialize();

	for (int i = 0; i < 10; i++)
	{
		obstacle_a[i] = nullptr;
		obstacle_b[i] = nullptr;
		obstacle_c[i] = nullptr;
	}

	for (int i = 0; i < 5; i++)
	{
		family[i] = nullptr;
	}
}

//�X�V����
eSceneType GameMainScene::Update()
{
	//�J�E���g
	time++;
	//1�b�𐔂��āA60�b�o�ߌナ�U���g��
	if (time % 60 == 0) {
		counter -= 1;
		if (counter < 0)
		{
			return eSceneType::E_RESULT;
		}
	}

	//�v���C���[�̍X�V
	player->Update();

	//�ړ������̍X�V
	if (player->GetActiveFlg() == true)
	{
		mileage += (int)player->GetSpeed();
	}
	else
	{
		mileage += 1;
	}

	//�G��������
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (obstacle_a[i] == nullptr)
			{
				obstacle_a[i] = new Obstacle_A(obstacle_a_image);
				obstacle_a[i]->Initialize();
				break;
			}
			if (obstacle_b[i] == nullptr)
			{
				//int type = GetRand(3) % 3;
				obstacle_b[i] = new Obstacle_B(obstacle_b_image);
				obstacle_b[i]->Initialize();
				break;
			}
			if (obstacle_c[i] == nullptr)
			{
				obstacle_c[i] = new Obstacle_C(obstacle_c_image);
				obstacle_c[i]->Initialize();
				break;
			}
		}
	}
	
	//���Ԑ�������
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (family[i] == nullptr)
			{
				int type = GetRand(1);
				family[i] = new Family(type,family_image[type]);
				family[i]->Initialize();
				break;
			}
		}
	}


	//�G�̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (obstacle_a[i] != nullptr)
		{
			obstacle_a[i]->Update(player->GetSpeed());

		//	////��ʊO�ɍs������A�G���폜���ăX�R�A���Z
		//	//if (enemy[i]->GetLocation().y >= 640.0f)
		//	//{
		//	//	enemy_count[enemy[i]->GetType()]++;
		//	//	enemy[i]->Finalize();
		//	//	delete enemy[i];
		//	//	enemy[i] = nullptr;
		//	//}

			////�����蔻��̊m�F
			//if (IsObjectHitCheck_P(player, obstacle_a[i]))
			//{
			//	player->SetActive(false);
			//	player->DecreaseHp(-50.0f;
			//	obstacle_a[i]->Finalize();
			//	delete obstacle_a[i];
			//	obstacle_a[i] = nullptr;
			//}
		}
		if (obstacle_b[i] != nullptr)
		{
			obstacle_b[i]->Update(player->GetSpeed());

			//��ʊO�ɍs������A�G���폜���ăX�R�A���Z
			/*if (obstacle_b[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[obstacle_b[i]->GetType()]++;
				obstacle_b[i]->Finalize();
				delete obstacle_b[i];
				obstacle_b[i] = nullptr;
			}*/

			//�����蔻��̊m�F
			if (IsObjectHitCheck_P(player, obstacle_b[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				obstacle_b[i]->Finalize();
				delete obstacle_b[i];
				obstacle_b[i] = nullptr;
			}

			//�G�Ə�Q���̓����蔻��
			if (IsObjecHitCheck_E(enemy_roomba, obstacle_b[i]))
			{
				enemy_roomba->SetActive(true);
				//enemy_roomba->DecreaseHp(-50.0f);
				obstacle_b[i]->Finalize();
				delete obstacle_b[i];
				obstacle_b[i] = nullptr;
			}
		}

		if (obstacle_c[i] != nullptr)
		{
			obstacle_c[i]->Update(player->GetSpeed());

		////	////��ʊO�ɍs������A�G���폜���ăX�R�A���Z
		////	//if (enemy[i]->GetLocation().y >= 640.0f)
		////	//{
		////	//	enemy_count[enemy[i]->GetType()]++;
		////	//	enemy[i]->Finalize();
		////	//	delete enemy[i];
		////	//	enemy[i] = nullptr;
		////	//}

			//�����蔻��̊m�F
			if (IsObjectHitCheck_P(player, obstacle_c[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-10000.0f);
				obstacle_c[i]->Finalize();
				delete obstacle_c[i];
				obstacle_c[i] = nullptr;
			}
		}
	}



	//�G(�����o)�̍X�V�Ɠ����蔻��`�F�b�N
	if (enemy_roomba != nullptr)
	{
		if (time % 60 == 0)
		{
			diff_x = player->GetLocation().x - enemy_roomba->GetLocation().x;
		}
		enemy_roomba->Update(counter,diff_x);

		//�����蔻��̊m�F
		if (IsHitCheck(player, enemy_roomba))
		{
			//�G(�����o)�ɓ�����ƃ_���[�W
			player->SetActive(false);
			player->DecreaseHp(-50.0f);
		}
	}
	
	//���Ԃ̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 5; i++)
	{
		if (family[i] != nullptr)
		{
			family[i]->Update(player->GetSpeed());

			//���Ԃ���ʊO�ɍs������폜
			if (family[i]->GetLocation().y >= 800.0f)
			{
				family[i]->Finalize();
				delete family[i];
				family[i] = nullptr;
			}

			//�����蔻��̊m�F
			if (IsObjectHitCheck_P(player, family[i]))
			{
				player->DecreaseHp(10.0f);
				player->SetSize(0.1f);
				player->SetBoxSize(0.1f);
				family[i]->Finalize();
				delete family[i];
				family[i] = nullptr;
			}

			//�G�Ə�Q���̓����蔻��
			if (IsObjecHitCheck_E(enemy_roomba, family[i]))
			{
				enemy_roomba->SetActive(true);
				//enemy_roomba->DecreaseHp(-50.0f);
				family[i]->Finalize();
				delete family[i];
				family[i] = nullptr;
			}

			for (int j = 0; j < 5; j++)
			{
				if (family[j] != nullptr && i != j)
				{
					//���ԓ��m�̓����蔻��
					if (IsObjecHitCheck_O(family[i], family[j]))
					{
						family[j]->Finalize();
						delete family[j];
						family[j] = nullptr;
					}
				}
			}
			
		}
	}

	//�v���C���[�̔R�����̗͂��O�����Ȃ�A���U���g�ɑJ�ڂ���
	if ( player->GetHp() < 0.0f)
	{
		return eSceneType::E_OVER;
	}

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 720 - 720, back_ground, TRUE);
	DrawGraph(0, mileage % 720, back_ground, TRUE);

	//�G�̕`��
	for (int i = 0; i < 10; i++)
	{
		if (obstacle_a[i] != nullptr)
		{
			obstacle_a[i]->Draw();
		}
		if (obstacle_b[i] != nullptr)
		{
			obstacle_b[i]->Draw();
		}
		if (obstacle_c[i] != nullptr)
		{
			obstacle_c[i]->Draw();
		}
	}

	//���Ԃ̕`��
	for (int i = 0; i < 5; i++)
	{
		if (family[i] != nullptr)
		{
			family[i]->Draw();
		}

		DrawFormatString(1000, 180+ i * 30, GetColor(255, 255, 255), "%d", family[i]);
	}

	//�����o�̕`��
	enemy_roomba->Draw();

	//�v���C���[�̕`��
	player->Draw();

	//UI�̕`��
	//DrawBox(980, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
	//SetFontSize(16);

	//�������Ԃ̕`��
	DrawFormatString(510, 180, GetColor(255, 255, 255), "time:%d", counter);

	/*DrawFormatString(510, 20, GetColor(0, 0, 0), "�n�C�X�R�A");
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d",high_score);
	DrawFormatString(510, 80, GetColor(0, 0, 0), "��������");
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE,FALSE);
		DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d",
			enemy_count[i]);
	}
	DrawFormatString(510, 200, GetColor(0, 0, 0), "���s����");
	DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d",mileage/10);
	DrawFormatString(555, 240, GetColor(0, 0, 0), "�X�s�[�h");
	DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f",
		player->GetSpeed());*/

	//�X�^�~�i�Q�[�W�̕`��
	float fx = player->GetLocation().x + 50.0f * player->GetPlayerSize();
	float fy = player->GetLocation().y - 40.0f * player->GetPlayerSize();
	DrawBoxAA(fx, fy, fx + 15.0f, fy + 50.0f, GetColor(0, 0, 0),FALSE);
	if (player->GetStamina() > 0.0f)
	{
		DrawBoxAA(fx, fy + 50.0f - player->GetStamina(), fx + 15.0f, fy + 50.0f, GetColor(0, 0, 255), TRUE);
	}
	

	//�̗̓Q�[�W�̕`��
	fx = 1000.0f;
	fy = 10.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 250 / 1000), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 250.0f, fy + 40.0f, GetColor(0, 0, 0),FALSE);
}

//�I�����錾
void GameMainScene::Finalize()
{
	//�X�R�A���v�Z����
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}
	//���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���J���܂���\n");
	}

	//�X�R�A��ۑ�
	fprintf(fp, "%d,\n", score);

	//���������Ɠ��_��ۑ�
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp,"%d,\n",enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;

	//for (int i = 0; i < 10; i++)
	//{
	//	if (enemy[i] != nullptr)
	//	{
	//		enemy[i]->Finalize();
	//		delete enemy[i];
	//		enemy[i] = nullptr;
	//	}
	//}

	//delete[] enemy;

	for (int i = 0; i < 10; i++)
	{
		if (obstacle_a[i] != nullptr)
		{
			obstacle_a[i]->Finalize();
			delete obstacle_a[i];
			obstacle_a[i] = nullptr;
		}
		if (obstacle_b[i] != nullptr)
		{
			obstacle_b[i]->Finalize();
			delete obstacle_b[i];
			obstacle_b[i] = nullptr;
		}
		if (obstacle_c[i] != nullptr)
		{
			obstacle_c[i]->Finalize();
			delete obstacle_c[i];
			obstacle_c[i] = nullptr;
		}
	}

	delete[] obstacle_a;
	delete[] obstacle_b;
	delete[] obstacle_c;

	for (int i = 0; i < 5; i++)
	{
		if (family[i] != nullptr)
		{
			family[i]->Finalize();
			delete family[i];
			family[i] = nullptr;
		}
	}

	delete[] family;
}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//�n�C�X�R�A�̓ǂݍ���
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}

//�����蔻��i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheck(Player* p, Enemy_Roomba* e)
{
	//�G��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (e == nullptr)
	{
		return false;
	}

	//�G���̍������擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//�����蔻��T�C�Y�̑傫���擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

//�����蔻��(�v���C���[�ƃI�u�W�F�N�g)
template<class T>
bool GameMainScene::IsObjectHitCheck_P(Player* p, T* object)
{
	//��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (object == nullptr)
	{
		return false;
	}

	//�G���̍������擾
	Vector2D diff_location = p->GetLocation() - object->GetLocation();

	//�����蔻��T�C�Y�̑傫���擾
	Vector2D box_ex = p->GetBoxSize() + object->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

//�����蔻��(�G(�����o)�ƃI�u�W�F�N�g)
template<class T>
bool GameMainScene::IsObjecHitCheck_E(Enemy_Roomba* e, T* object)
{
	//��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (object == nullptr)
	{
		return false;
	}

	//�G���̍������擾
	Vector2D diff_location = e->GetLocation() - object->GetLocation();

	//�����蔻��T�C�Y�̑傫���擾
	Vector2D box_ex = e->GetBoxSize() + object->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

//��Q�����m�̓����蔻��
template<class T>
bool GameMainScene::IsObjecHitCheck_O(T* object1, T* object2)
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