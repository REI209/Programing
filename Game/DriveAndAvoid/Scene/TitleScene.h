#pragma once

#include"SceneBase.h"

class Titlescene :public SceneBase
{
private:

private:
	int background_image;  //�w�i�摜
	int menu_image;        //���j���[���
	int cursor_iamge;      //�J�[�\���摜
	int menu_cursor;       //���j���[�J�[�\���ԍ�

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};