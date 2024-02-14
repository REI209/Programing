#include "GameOverScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Object/common.h"

GameOverScene::GameOverScene() :background_image(NULL)
{
}

GameOverScene::~GameOverScene()
{
}

//����������
void GameOverScene::Initialize()
{
	//�摜�̓ǂݍ���

	//�G���[�`�F�b�N

	//�����̓ǂݍ���
	gameoverbgm = LoadSoundMem(GAMEOVER_BGM);
}

eSceneType GameOverScene::Update()
{
	//BGM�𗬂�
	if (GetNowScene() == E_OVER)
	{
		PlaySoundMem(gameoverbgm, DX_PLAYTYPE_LOOP, FALSE);
	}
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
