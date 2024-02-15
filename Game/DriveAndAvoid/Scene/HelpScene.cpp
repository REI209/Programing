#include"HelpScene.h"
#include"../Utility/InputControl.h"
#include"../Object/common.h"
#include"DxLib.h"
#include "../Object/common.h"

HelpScene::HelpScene() :background_image(NULL),bgm(0),ok_se(0)
{

}

HelpScene::~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph(HELP_BACK_IMAGE);

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/game_help.png������܂���\n");
	}
}

//�X�V����
eSceneType HelpScene::Update()
{
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//�`�揈��
void HelpScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);
}

//�I���錾
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�폜
	//DeleteGraph(background_image);

	DeleteSoundMem(bgm);
	//DeleteSoundMem(ok_se);
}

//���݂̃V�[�������擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}