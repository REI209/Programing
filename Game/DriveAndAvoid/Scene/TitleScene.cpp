#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include "../Object/common.h"
TitleScene::TitleScene() :background_image(NULL),cursor_image(NULL), menu_cursor(0),titlebgm(0)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Title.png");
	cursor_image = LoadGraph("Resource/images/cursor.png");
	//�����̓ǂݍ���
	titlebgm = LoadSoundMem(TITLE_BGM);

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}
}

//�X�V����
eSceneType TitleScene::Update()
{
	//BGM�𗬂�
	if (GetNowScene() == E_TITLE)
	{
		PlaySoundMem(titlebgm, DX_PLAYTYPE_LOOP, FALSE);
	}
	
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//��ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
	}

	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//��ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
	}

	//�J�[�\������(���肵����ʂɑJ�ڂ���)
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_HELP;
		case 2:
			return eSceneType::E_END;
		default:
			break;	
		}
	}
	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{
	//�^�C�g����ʂ̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�J�[�\����ʂ̕`��
	DrawGraph(320, 305 + menu_cursor * 100, cursor_image,TRUE);
}

//�I�����錾
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(cursor_image);
	DeleteSoundMem(titlebgm);
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}