#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL),mileage(0), player(nullptr), enemy_roomba(nullptr), obstacle_a(nullptr),obstacle_b(nullptr),obstacle_c(nullptr)//,enemy(nullptr)
{

	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
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


	//画像の読み込み
	back_ground = LoadGraph("Resource/Images/back_img.png");
	barrier_image = LoadGraph("Resource/Images/barrier.png");
	int result = LoadDivGraph("Resource/Images/car.bmp", 3, 3, 1, 63, 120,
		enemy_image);

	obstacle_a_image = LoadGraph("Resource/Images/kaden_senpuki.png");
	obstacle_b_image= LoadGraph("Resource/Images/omocha_tsumiki.png");
	obstacle_c_image = LoadGraph("Resource/Images/pet_robot_soujiki_cat.png");

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/Images/back_img.pngがありません\n");
	}
	if (result == -1)
	{
		throw("Resource/Images/car.bmpがありません\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/Images/barrier.pngがありません\n");
	}
	if (obstacle_a)
	{
		throw("Resource/Images/kaden_senpuki.pngがありません\n");
	}
	if (obstacle_b)
	{
		throw("Resource/Images/omocha_tumiki.pngがありません\n");
	}
	if (obstacle_c)
	{
		throw("Resource/Images/pet_robot_soujiki_cat.pngがありません\n");
	}
	//オブジェクトの生成
	player = new Player;
	//enemy = new Enemy * [10];

	enemy_roomba = new Enemy_Roomba;
	obstacle_a = new Obstacle_A * [10];
	obstacle_b = new Obstacle_B*[10];
	obstacle_c = new Obstacle_C * [10];

	//オブジェクトの初期化
	player->Initialize();
	enemy_roomba->Initialize();
	
	//obstacle_a->Initialize();
	//obstacle_b->Initialize();
	//obstacle_c->Initialize();

	for (int i = 0; i < 10; i++)
	{
		obstacle_a[i] = nullptr;
		obstacle_b[i] = nullptr;
		obstacle_c[i] = nullptr;
	}
}

//更新処理
eSceneType GameMainScene::Update()
{
	//カウント
	time++;
	//1秒を数えて、60秒経過後リザルトへ
	if (time % 60 == 0) {
		counter -= 1;
		if (counter < 0)
		{
			return eSceneType::E_RESULT;
		}
	}


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

	//敵生成処理
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (obstacle_a[i] == nullptr)
			{
				obstacle_a[i] = new Obstacle_A(obstacle_a_image);
				obstacle_a[i]->Initialize();
				break;
			}
			if (obstacle_b[i] == nullptr)
			{
				//int type = GetRand(3) % 3;
				obstacle_b[i] = new Obstacle_B(obstacle_b_image);
				obstacle_b[i]->Initialize();
				break;
			}
			if (obstacle_c[i] == nullptr)
			{
				obstacle_c[i] = new Obstacle_C(obstacle_c_image);
				obstacle_c[i]->Initialize();
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

		//	////画面外に行ったら、敵を削除してスコア加算
		//	//if (enemy[i]->GetLocation().y >= 640.0f)
		//	//{
		//	//	enemy_count[enemy[i]->GetType()]++;
		//	//	enemy[i]->Finalize();
		//	//	delete enemy[i];
		//	//	enemy[i] = nullptr;
		//	//}

		//	////当たり判定の確認
		//	//if (IsHitCheck(player, enemy[i]))
		//	//{
		//	//	player->SetActive(false);
		//	//	player->DecreaseHp(-50.0f);
		//	//	enemy[i]->Finalize();
		//	//	delete enemy[i];
		//	//	enemy[i] = nullptr;
		//	//}
		//}
		if (obstacle_b[i] != nullptr)
		{
			obstacle_b[i]->Update(player->GetSpeed());

			//画面外に行ったら、敵を削除してスコア加算
			/*if (obstacle_b[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[obstacle_b[i]->GetType()]++;
				obstacle_b[i]->Finalize();
				delete obstacle_b[i];
				obstacle_b[i] = nullptr;
			}*/

			//当たり判定の確認
			if (IsObjectHitCheck_P(player, obstacle_b[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				obstacle_b[i]->Finalize();
				delete obstacle_b[i];
				obstacle_b[i] = nullptr;
			}

			//敵と障害物の当たり判定
			if (IsObjecHitCheck_E(enemy_roomba, obstacle_b[i]))
			{
				enemy_roomba->SetActive(true);
				//enemy_roomba->DecreaseHp(-50.0f);
				obstacle_b[i]->Finalize();
				delete obstacle_b[i];
				obstacle_b[i] = nullptr;
			}
		}

		//if (obstacle_c[i] != nullptr)
		//{
		//	obstacle_c[i]->Update(player->GetSpeed());

		////	////画面外に行ったら、敵を削除してスコア加算
		////	//if (enemy[i]->GetLocation().y >= 640.0f)
		////	//{
		////	//	enemy_count[enemy[i]->GetType()]++;
		////	//	enemy[i]->Finalize();
		////	//	delete enemy[i];
		////	//	enemy[i] = nullptr;
		////	//}

		//	//当たり判定の確認
		//	if (IsHitCheck(player, [i]))
		//	{
		//		player->SetActive(false);
		//		player->DecreaseHp(-50.0f);
		//		enemy[i]->Finalize();
		//		delete enemy[i];
		//		enemy[i] = nullptr;
		//	}
		//}
	}



	//敵(ルンバ)の更新と当たり判定チェック
	if (enemy_roomba != nullptr)
	{
		
		float diff_x = player->GetLocation().x - enemy_roomba->GetLocation().x;
		enemy_roomba->Update(counter,diff_x);

		//当たり判定の確認
		if (IsHitCheck(player, enemy_roomba))
		{
			//敵(ルンバ)に当たるとダメージ
			player->SetActive(false);
			player->DecreaseHp(-50.0f);
		}
	}

	////プレイヤーと障害物の当たり判定
	//if (IsObjectHitCheck_P(player, object_kari[i]))
	//{

	//}
	



	//プレイヤーの燃料化体力が０未満なら、リザルトに遷移する
	if ( player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, mileage % 720 - 720, back_ground, TRUE);
	DrawGraph(0, mileage % 720, back_ground, TRUE);

	//敵の描画
	for (int i = 0; i < 10; i++)
	{
		if (obstacle_a[i] != nullptr)
		{
			obstacle_a[i]->Draw();
		}
		if (obstacle_b[i] != nullptr)
		{
			obstacle_b[i]->Draw();
		}
		if (obstacle_c[i] != nullptr)
		{
			obstacle_c[i]->Draw();
		}
	}

	//ルンバの描画
	enemy_roomba->Draw();

	//プレイヤーの描画
	player->Draw();

	//UIの描画
	DrawBox(980, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
	SetFontSize(16);

	//制限時間の描画
	DrawFormatString(510, 180, GetColor(255, 255, 255), "time:%d", counter);


	DrawFormatString(510, 20, GetColor(0, 0, 0), "ハイスコア");
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d",high_score);
	DrawFormatString(510, 80, GetColor(0, 0, 0), "避けた数");
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE,
			FALSE);
		DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d",
			enemy_count[i]);
	}
	DrawFormatString(510, 200, GetColor(0, 0, 0), "走行距離");
	DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d",mileage/10);
	DrawFormatString(555, 240, GetColor(0, 0, 0), "スピード");
	DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f",
		player->GetSpeed());

	//スタミナゲージの描画
	float fx = 1005.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "STAMINA METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetStamina() * 250 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 250.0f, fy + 40.0f, GetColor(0, 0, 0),FALSE);

	//体力ゲージの描画
	fx = 1005.0f;
	fy = 450.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 250 / 1000), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 250.0f, fy + 40.0f, GetColor(0, 0, 0),FALSE);
}

//終了時宣言
void GameMainScene::Finalize()
{
	//スコアを計算する
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}
	//リザルトデータの書き込み
	FILE* fp = nullptr;
	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが開けません\n");
	}

	//スコアを保存
	fprintf(fp, "%d,\n", score);

	//避けた数と得点を保存
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp,"%d,\n",enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);

	//動的確保したオブジェクトを削除する
	player->Finalize();
	delete player;

	//for (int i = 0; i < 10; i++)
	//{
	//	if (enemy[i] != nullptr)
	//	{
	//		enemy[i]->Finalize();
	//		delete enemy[i];
	//		enemy[i] = nullptr;
	//	}
	//}

	//delete[] enemy;
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

//当たり判定（プレイヤーと敵）
bool GameMainScene::IsHitCheck(Player* p, Enemy_Roomba* e)
{
	//敵情報がなければ、当たり判定を無視する
	if (e == nullptr)
	{
		return false;
	}

	//敵情報の差分を取得
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//当たり判定サイズの大きさ取得
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

template<class T>
bool GameMainScene::IsObjectHitCheck_P(Player* p, T* object)
{
	//情報がなければ、当たり判定を無視する
	if (object == nullptr)
	{
		return false;
	}

	//敵情報の差分を取得
	Vector2D diff_location = p->GetLocation() - object->GetLocation();

	//当たり判定サイズの大きさ取得
	Vector2D box_ex = p->GetBoxSize() + object->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

template<class T>
bool GameMainScene::IsObjecHitCheck_E(Enemy_Roomba* e, T* object)
{
	//情報がなければ、当たり判定を無視する
	if (object == nullptr)
	{
		return false;
	}

	//敵情報の差分を取得
	Vector2D diff_location = e->GetLocation() - object->GetLocation();

	//当たり判定サイズの大きさ取得
	Vector2D box_ex = e->GetBoxSize() + object->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}