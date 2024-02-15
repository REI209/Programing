#include "GameOverScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Object/common.h"

GameOverScene::GameOverScene() :background_image(NULL),gameoverbgm(0)
{
}

GameOverScene::~GameOverScene()
{
}

//����������
void GameOverScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph(GAMEOVER_BACK_IMAGE);
	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/Images/game_over.png������܂���\n");
	}

	//�����̓ǂݍ���
	gameoverbgm = LoadSoundMem(GAMEOVER_BGM);
}

eSceneType GameOverScene::Update()
{
	
	PlaySoundMem(gameoverbgm, DX_PLAYTYPE_BACK, FALSE);
	//B�{�^���������ꂽ��A���U���g��
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_RESULT;
	}
	return GetNowScene();

}

void GameOverScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, TRUE);
	DrawString(20, 120, "GameOver", 0xffffff, 0);

}

//�I���錾
void GameOverScene::Finalize()
{
	//�ǂݍ��񂾉����̍폜
	DeleteSoundMem(gameoverbgm);
}

//���݂̃V�[�������擾
eSceneType GameOverScene::GetNowScene() const
{
	return eSceneType::E_OVER;
}
