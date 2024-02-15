#include "GameOverScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Object/common.h"

GameOverScene::GameOverScene() :background_image(NULL),gameoverbgm{},ok_se(0)
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
	gameoverbgm[0] = LoadSoundMem(GAMEOVER_BGM);
	gameoverbgm[1] = LoadSoundMem(DEATH_SE);
	ok_se = LoadSoundMem(SELECT_SE);
}

eSceneType GameOverScene::Update()
{
	SetVolumeMusic(120);
	PlaySoundMem(gameoverbgm[0], DX_PLAYTYPE_BACK, FALSE);
	PlaySoundMem(gameoverbgm[1], DX_PLAYTYPE_BACK, FALSE);

	//B�{�^���������ꂽ��A���U���g��
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
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
	DeleteSoundMem(gameoverbgm[0]);
	DeleteSoundMem(gameoverbgm[1]);

}

//���݂̃V�[�������擾
eSceneType GameOverScene::GetNowScene() const
{
	return eSceneType::E_OVER;
}
