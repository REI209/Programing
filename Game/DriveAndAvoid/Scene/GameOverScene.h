#pragma once
#include "SceneBase.h"
class GameOverScene :public SceneBase
{
private:
	int background_image;	//�w�i
	int gameoverbgm[2];        //����
	int ok_se;
public:
	GameOverScene();
	~GameOverScene();

	virtual void Initialize();
	virtual eSceneType Update();
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

};

