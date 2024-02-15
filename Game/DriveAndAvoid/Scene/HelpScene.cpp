#include"HelpScene.h"
#include"../Utility/InputControl.h"
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
	////�摜�̓ǂݍ���
	//background_image = LoadGraph("Resource/images/Title.bpm");

	////�G���[�`�F�b�N
	//if (background_image == -1)
	//{
	//	throw("Resource/images/Title.bpm������܂���\n");
	//}

	bgm = LoadSoundMem(TITLE_BGM);
	ok_se = LoadSoundMem(SELECT_SE);
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
	//DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(16);
	DrawString(20, 120, "�w���v���", 0xffffff, 0);

	DrawString(20, 160, "����͏�Q��������Ȃ���", 0xffffff, 0);
	DrawString(20, 180, "���葱����Q�[���ł�", 0xffffff, 0);
	DrawString(20, 200, "�R�����s���邩��Q����", 0xffffff, 0);
	DrawString(20, 220, "���񓖂���ƃQ�[���I�[�o�[�ł�", 0xffffff, 0);

	DrawString(150, 450, "---- B�{�^���������ă^�C�g���֖߂� ----", 0xffffff, 0);
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