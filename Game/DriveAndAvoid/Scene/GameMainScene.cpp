#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "../Object/common.h"



GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),mainbgm(NULL),
mileage(0), player(nullptr), enemy_roomba(nullptr),diff_x(0.0),/*obstacle_a(nullptr),*/ obstacle_b(nullptr), obstacle_c(nullptr), family(nullptr),
family_cnt{}, counter(0), count_down(0),/* obstacle_a_image(NULL),*/obstacle_c_image(NULL), time(0), se{}//,enemy(nullptr)
{

	for (int i = 0; i < 3; i++)
	{
		obstacle_b_image[i] = NULL;
	}

	for (int i = 0; i < 2; i++)
	{
		family_image[i] = NULL;
	}

	roomba_image = NULL;


}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	//高得点値を読み込む
	ReadHighScore();

	//制限時間の設定(秒) 
	counter = 60;
	count_down = 4;


	//画像の読み込み
	back_ground = LoadGraph(GAMEMAIN_BACK_IMAGE);

	//obstacle_a_image = LoadGraph("Resource/Images/kaden_senpuki1.png");
	int obs_b_image= LoadDivGraph(OBSTACLE_B_IMAGE,3,3,1,180,180,obstacle_b_image,TRUE);
	obstacle_c_image = LoadGraph(OBSTACLE_C_IMAGE);

	family_image[0] = LoadGraph(FAMILLY_IMAGE_01);
	family_image[1] = LoadGraph(FAMILLY_IMAGE_02);

	//音源の読み込み
	mainbgm = LoadSoundMem(GAMEMAIN_BGM);
	ChangeVolumeSoundMem(100, mainbgm);

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/Images/back_img.pngがありません\n");
	}
	if (obs_b_image == -1)
	{
		throw("Resource/Images/car.bmpがありません\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/Images/barrier.pngがありません\n");
	}
	/*if (obstacle_a)
	{
		throw("Resource/Images/kaden_senpuki.pngがありません\n");
	}*/
	if (obstacle_b)
	{
		throw("Resource/Images/omocha_tumiki.pngがありません\n");
	}
	if (obstacle_c)
	{
		throw("Resource/Images/pet_robot_soujiki_cat.pngがありません\n");
	}
	if (family_image[0] == -1)
	{
		throw("Resource/Images/family01.pngがありません\n");
	}
	if (family_image[1] == -1)
	{
		throw("Resource/Images/family02.pngがありません\n");
	}
	//オブジェクトの生成
	player = new Player;
	//enemy = new Enemy * [10];

	enemy_roomba = new Enemy_Roomba;
	//obstacle_a = new Obstacle_A * [10];
	obstacle_b = new Obstacle_B*[10];
	obstacle_c = new Obstacle_C * [10];

	family = new Family * [10];

	//オブジェクトの初期化
	player->Initialize();
	enemy_roomba->Initialize();
	
	//obstacle_a->Initialize();
	//obstacle_b->Initialize();
	//obstacle_c->Initialize();

	for (int i = 0; i < 10; i++)
	{
		//obstacle_a[i] = nullptr;
		obstacle_b[i] = nullptr;
		obstacle_c[i] = nullptr;
	}

	for (int i = 0; i < 5; i++)
	{
		family[i] = nullptr;
	}

	
	se[1] = LoadSoundMem(FAMILLY_GET_SE);
	se[2] = LoadSoundMem(DAMAGE_SE);
	se[3] = LoadSoundMem(DEATH_SE);
}

//更新処理
eSceneType GameMainScene::Update()
{
	//カウント
	time++;

	//BGMを流す
	if (GetNowScene() == E_MAIN)
	{
		PlaySoundMem(mainbgm, DX_PLAYTYPE_LOOP, FALSE);
	}

	//1秒を数えて、60秒経過後リザルトへ
	if (time % 60 == 0) 
	{
		count_down -= 1;

		if (count_down < 0)
		{
			counter -= 1;

			if (counter < 0)
			{
				counter = 0;
				return eSceneType::E_CLEAR;
			}
		}
	}

	if (count_down < 1)
	{
		//プレイヤーの更新
		player->Update();

		//移動距離の更新
		if (player->GetActiveFlg() == true)
		{
			mileage += (int)player->GetSpeed();
		}
		else
		{
			mileage += 1;
		}

		////敵生成処理
		//if (mileage / 20 % 100 == 0)
		//{
		//	for (int i = 0; i < 10; i++)
		//	{
		//		if (obstacle_a[i] == nullptr)
		//		{
		//			int type = GetRand(1);
		//			obstacle_a[i] = new Obstacle_A(type,obstacle_a_image);
		//			obstacle_a[i]->Initialize();
		//			break;
		//		}
		//	}
		//}

		//つみきの生成
		if (mileage / 10 % 50 == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				if (obstacle_b[i] == nullptr)
				{
					int type = GetRand(3) % 3;
					obstacle_b[i] = new Obstacle_B(type,obstacle_b_image[type]);
					obstacle_b[i]->Initialize();
					break;
				}
			}
		}

		//掃除機の生成
		if (counter < 55)
		{
			if (mileage / 20 % 300 == 0)
			{
				se[0] = LoadSoundMem(CLEANER_SE);
				ChangeVolumeSoundMem(255, se[0]);
				for (int i = 0; i < 2; i++)
				{
					if (obstacle_c[i] == nullptr)
					{
						obstacle_c[i] = new Obstacle_C(obstacle_c_image);
						obstacle_c[i]->Initialize();
						break;
					}
				}
			}
		}
		

		//仲間生成処理
		if (mileage / 20 % 100 == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				if (family[i] == nullptr)
				{
					int type = GetRand(1);
					family[i] = new Family(type, family_image[type]);
					family[i]->Initialize();
					break;
				}
			}
		}


		//敵の更新と当たり判定チェック
		for (int i = 0; i < 10; i++)
		{
			//if (obstacle_a[i] != nullptr)
			//{
			//	obstacle_a[i]->Update(player->GetSpeed());

			//	//画面外に行ったら削除
			//	if (obstacle_a[i]->GetLocation().y >= 800.0f)
			//	{
			//		obstacle_a[i]->Finalize();
			//		delete obstacle_a[i];
			//		obstacle_a[i] = nullptr;
			//	}

			//	if (player->GetActiveFlg() == true)
			//	{
			//		//当たり判定の確認
			//		if (IsObjectHitCheck_P(player, obstacle_a[i]))
			//		{
			//			player->SetActive(false);
			//			player->DecreaseHp(-20.0f);
			//			if (player->GetPlayerSize() > 0.3f)
			//			{
			//				player->SetSize(-0.1f);
			//				player->SetBoxSize(-0.1f);
			//			}
			//			obstacle_a[i]->Finalize();
			//			delete obstacle_a[i];
			//			obstacle_a[i] = nullptr;
			//		}
			//	}

			////敵と障害物の当たり判定
			//if (IsObjecHitCheck_E(enemy_roomba, obstacle_a[i]))
			//{
			//	enemy_roomba->SetActive(false);
			//	enemy_roomba->DecreaseHp(-10.0f);
			//	obstacle_a[i]->Finalize();
			//	delete obstacle_a[i];
			//	obstacle_a[i] = nullptr;
			//}

			//	for (int j = 0; j < 10; j++)
			//	{
			//		if (obstacle_a[j] != nullptr && i != j)
			//		{
			//			//仲間同士の当たり判定
			//			if (IsObjecHitCheck_O(obstacle_a[i], obstacle_a[j]))
			//			{
			//				obstacle_a[j]->Finalize();
			//				delete obstacle_a[j];
			//				obstacle_a[j] = nullptr;
			//			}
			//		}
			//	}

			//}
			if (obstacle_b[i] != nullptr)
			{
				obstacle_b[i]->Update(player->GetSpeed());

				//画面外に行ったら削除
				if (obstacle_b[i]->GetLocation().y >= 800.0f)
				{
					obstacle_b[i]->Finalize();
					delete obstacle_b[i];
					obstacle_b[i] = nullptr;
				}

				if (player->GetActiveFlg() == true)
				{
					//当たり判定の確認
					if (IsObjecHitCheck<class Player, class Obstacle_B>(player, obstacle_b[i]))
					{
						PlaySoundMem(se[2], DX_PLAYTYPE_BACK, TRUE);
						player->SetActive(false);
						player->DecreaseHp(-50.0f);
						if (player->GetPlayerSize() > 0.3f)
						{
							player->SetSize(-0.1f);
							player->SetBoxSize(-0.1f);
						}
						obstacle_b[i]->Finalize();
						delete obstacle_b[i];
						obstacle_b[i] = nullptr;
					}
				}

			//敵と障害物の当たり判定
			if (IsObjecHitCheck<class Enemy_Roomba, class Obstacle_B>(enemy_roomba, obstacle_b[i]))
			{
				PlaySoundMem(se[2], DX_PLAYTYPE_BACK, TRUE);
				enemy_roomba->SetActive(false);
				enemy_roomba->DecreaseHp(-50.0f);
				obstacle_b[i]->Finalize();
				delete obstacle_b[i];
				obstacle_b[i] = nullptr;
			}

				for (int j = 0; j < 10; j++)
				{
					if (obstacle_b[j] != nullptr && i != j)
					{
						//敵同士の当たり判定
						if (IsObjecHitCheck<class Obstacle_B,class Obstacle_B>(obstacle_b[i], obstacle_b[j]))
						{
							obstacle_b[j]->Finalize();
							delete obstacle_b[j];
							obstacle_b[j] = nullptr;
						}
					}
				}
			}

			if (obstacle_c[i] != nullptr)
			{
				obstacle_c[i]->Update(player->GetSpeed());
				PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

				//画面外に行ったら削除
				if (obstacle_c[i]->GetLocation().x >= 1290.0f)
				{
					obstacle_c[i]->Finalize();
					delete obstacle_c[i];
					obstacle_c[i] = nullptr;
				}

				if (player->GetActiveFlg() == true)
				{
					//プレイヤーと障害物の当たり判定の確認
					if (IsObjecHitCheck<class Player, class Obstacle_C>(player, obstacle_c[i]))
					{
						PlaySoundMem(se[3], DX_PLAYTYPE_BACK, TRUE);
						player->SetRoomAnim(1);
						//敵(ルンバ)に当たるとダメージ
						player->SetActive(false);
						if (player->GetPlayerSize() <= 0.5f)
						{
							
							player->SetHp();
						}
						else
						{
							player->SetSizeDef();
						}

						if (player->GetPlayerSize() > 0.3f)
						{
							player->SetSize(-0.1f);
							player->SetBoxSize(-0.1f);
						}
						//player->SetY(100.0f);
						obstacle_c[i]->Finalize();
						delete obstacle_c[i];
						obstacle_c[i] = nullptr;
						DeleteSoundMem(se[0]);
					}
				}

				//敵と障害物の当たり判定
				if (IsObjecHitCheck<class Enemy_Roomba,class Obstacle_C>(enemy_roomba, obstacle_c[i]))
				{
					PlaySoundMem(se[2], DX_PLAYTYPE_BACK, TRUE);
					enemy_roomba->SetActive(false);
					enemy_roomba->DecreaseHp(-50.0f);
					obstacle_c[i]->Finalize();
					delete obstacle_c[i];
					obstacle_c[i] = nullptr;
				}

				for (int j = 0; j < 10; j++)
				{
					if (obstacle_c[j] != nullptr && i != j)
					{
						//仲間同士の当たり判定
						if (IsObjecHitCheck<class Obstacle_C,class Obstacle_C>(obstacle_c[i], obstacle_c[j]))
						{
							obstacle_c[j]->Finalize();
							delete obstacle_c[j];
							obstacle_c[j] = nullptr;
						}
					}
				}
			}
		}

		//敵(ルンバ)の更新と当たり判定チェック
		if (enemy_roomba != nullptr)
		{
			if (time % 60 == 0)
			{
				diff_x = player->GetLocation().x - enemy_roomba->GetLocation().x;
			}
			enemy_roomba->Update((float)counter, diff_x);

			if (player->GetActiveFlg() == true)
			{
				//プレイヤーと敵の当たり判定の確認
				if (IsObjecHitCheck<class Player, class Enemy_Roomba>(player, enemy_roomba))
				{
					PlaySoundMem(se[3], DX_PLAYTYPE_BACK, TRUE);
					player->SetRoomAnim(1);
					//敵(ルンバ)に当たるとダメージ
					player->SetActive(false);
					if (player->GetPlayerSize() <= 0.5f)
					{
						player->SetHp();
					}
					else
					{
						player->SetSizeDef();
					}

					if (player->GetPlayerSize() > 0.3f)
					{
						player->SetSize(-0.1f);
						player->SetBoxSize(-0.1f);
					}
					player->SetY(100.0f);

				}
			}
		}

		//仲間の更新と当たり判定チェック
		for (int i = 0; i < 5; i++)
		{
			if (family[i] != nullptr)
			{
				family[i]->Update(player->GetSpeed());

				//仲間が画面外に行ったら削除
				if (family[i]->GetLocation().y >= 800.0f)
				{
					family[i]->Finalize();
					delete family[i];
					family[i] = nullptr;
				}

			//当たり判定の確認
				if (player->GetActiveFlg() == true)
				{
					if (IsObjecHitCheck<class Player, class Family>(player, family[i]))
					{
						PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);
						if (player->GetHp() < 230)
						{
							player->DecreaseHp(10.0f);
						}
						if (player->GetPlayerSize() < 2.0f)
						{
							player->SetSize(0.1f);
							player->SetBoxSize(0.1f);
						}
						family_cnt[family[i]->GetType()]++;
						family[i]->Finalize();
						delete family[i];
						family[i] = nullptr;
					}
				}
			

				//敵と障害物の当たり判定
				if (IsObjecHitCheck<class Enemy_Roomba, class Family>(enemy_roomba, family[i]))
				{
					PlaySoundMem(se[3], DX_PLAYTYPE_BACK, TRUE);
					family[i]->Finalize();
					delete family[i];
					family[i] = nullptr;
				}

				for (int j = 0; j < 5; j++)
				{
					if (family[j] != nullptr && i != j)
					{
						//仲間同士の当たり判定
						if (IsObjecHitCheck<class Family, class Family>(family[i], family[j]))
						{
							family[j]->Finalize();
							delete family[j];
							family[j] = nullptr;
						}
					}
				}

			}
		}

	}

	//プレイヤーの燃料化体力が０未満なら、リザルトに遷移する
	if (player->GetHp() < 0.1f)
	{
		return eSceneType::E_OVER;
	}

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, mileage % 720 - 720, back_ground, TRUE);
	DrawGraph(0, mileage % 720, back_ground, TRUE);

	//プレイヤーの描画
	player->Draw();

	//ルンバの描画
	enemy_roomba->Draw();

	//スタミナゲージの描画
	float fx = player->GetLocation().x + player->GetBoxSize().x + 13.0f;
	float fy = player->GetLocation().y - player->GetBoxSize().y;
	DrawBoxAA(fx, fy, fx + 15.0f, fy + 50.0f, GetColor(0, 0, 0), FALSE);
	if (player->GetStamina() > 0.0f)
	{
		DrawBoxAA(fx, fy + 50.0f - player->GetStamina(), fx + 15.0f, fy + 50.0f, GetColor(0, 0, 255), TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(995, 5, 1265, 115, GetColor(255, 255, 255), TRUE);

	SetFontSize(16);
	//DrawFormatStringF(1000.0f, 60.0f, GetColor(0, 0, 0), "集めた仲間の数");

	//集めた仲間の数
	fx = 1010.0f;
	fy = 60.0f;
	SetFontSize(20);
	DrawExtendGraphF(fx, fy, fx + 50, fy + 50, family_image[0], TRUE);
	DrawFormatStringF(fx + 60, fy + 20, GetColor(0, 0, 0), "× %d", family_cnt[0]);

	fx = 1145.0f;
	fy = 60.0f;
	DrawExtendGraphF(fx, fy, fx + 50, fy + 50, family_image[1], TRUE);
	DrawFormatStringF(fx + 60, fy + 20, GetColor(0, 0, 0), "× %d", family_cnt[1]);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//体力ゲージの描画
	fx = 1015.0f;
	fy = 10.0f;
	SetFontSize(16);
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "HP");
	DrawBoxAA(fx, fy + 20.0f, fx + player->GetHp(), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 230.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	//制限時間の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(20, 30, 100, 110, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetFontSize(20);
	DrawFormatString(40, 10, GetColor(0, 0, 0), "TIME");

	SetFontSize(60);
	if (counter > 10)
	{
		DrawFormatString(30, 40, GetColor(0, 0, 0), "%02d", counter);
	}
	else
	{
		DrawFormatString(30, 40, GetColor(255, 0, 0), "%02d", counter);
	}

	//一時停止中なら画面を薄暗くする

	SetFontSize(120);

	if (count_down > 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawFormatString(600, 315, GetColor(255, 255, 255), "%d", count_down - 1);
	}
	else if (count_down == 1)
	{
		DrawFormatString(570, 315, GetColor(0, 0, 0), "GO!");
	}

	SetFontSize(16);

	//敵の描画
	for (int i = 0; i < 10; i++)
	{
		/*if (obstacle_a[i] != nullptr)
		{
			obstacle_a[i]->Draw();
		}*/
		if (obstacle_b[i] != nullptr)
		{
			obstacle_b[i]->Draw();
		}
		if (obstacle_c[i] != nullptr)
		{
			obstacle_c[i]->Draw();
		}
	}

	//仲間の描画
	for (int i = 0; i < 5; i++)
	{
		if (family[i] != nullptr)
		{
			family[i]->Draw();
		}

		//DrawFormatString(1000, 180+ i * 30, GetColor(255, 255, 255), "%d", family[i]);
	}
	//UIの描画

} 

//終了時宣言
void GameMainScene::Finalize()
{
	////スコアを計算する
	//int score = (mileage / 10 * 10);
	//for (int i = 0; i < 3; i++)
	//{
	//	score += (i + 1) * 50 * enemy_count[i];
	//}
	////リザルトデータの書き込み
	//FILE* fp = nullptr;
	////ファイルオープン
	//errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	////エラーチェック
	//if (result != 0)
	//{
	//	throw("Resource/dat/result_data.csvが開けません\n");
	//}

	////スコアを保存
	//fprintf(fp, "%d,\n", score);

	////避けた数と得点を保存
	//for (int i = 0; i < 3; i++)
	//{
	//	fprintf(fp,"%d,\n",enemy_count[i]);
	//}

	////ファイルクローズ
	//fclose(fp);

	//動的確保したオブジェクトを削除する
	player->Finalize();
	delete player;
	delete enemy_roomba;

	for (int i = 0; i < 10; i++)
	{
		/*if (obstacle_a[i] != nullptr)
		{
			obstacle_a[i]->Finalize();
			delete obstacle_a[i];
			obstacle_a[i] = nullptr;
		}*/
		if (obstacle_b[i] != nullptr)
		{
			obstacle_b[i]->Finalize();
			delete obstacle_b[i];
			obstacle_b[i] = nullptr;
		}
		if (obstacle_c[i] != nullptr)
		{
			obstacle_c[i]->Finalize();
			delete obstacle_c[i];
			obstacle_c[i] = nullptr;
		}
	}

	//delete[] obstacle_a;
	delete[] obstacle_b;
	delete[] obstacle_c;

	for (int i = 0; i < 5; i++)
	{
		if (family[i] != nullptr)
		{
			family[i]->Finalize();
			delete family[i];
			family[i] = nullptr;
		}
	}

	delete[] family;
	DeleteSoundMem(mainbgm);
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//ハイスコアの読み込み
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}
