#include "GameOverScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

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
}

eSceneType GameOverScene::Update()
{

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
	//�ǂݍ��񂾉摜�̍폜
}

//���݂̃V�[�������擾
eSceneType GameOverScene::GetNowScene() const
{
	return eSceneType::E_OVER;
}
