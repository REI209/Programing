#pragma once

#include"SceneBase.h"

class GameClear :public SceneBase
{
private:

private:
	int background_image;  //”wŒi‰æ‘œ
	int clearbgm;          //BGM
public:
	GameClear();
	virtual ~GameClear();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};