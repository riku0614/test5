//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjMain.h"
#include "ObjText.h"
#include "UtilityModule.h"



//使用するネームスペース
using namespace GameL;

CObjMain::CObjMain(int map[ROOM_X][ROOM_Y])
{
	memcpy(r_map, map, sizeof(int)*(ROOM_X * ROOM_Y));
}





//イニシャライズ
void CObjMain::Init()
{
	m_scroll_x = 64.0f;
	m_scroll_y = 64.0f;

	map_chg = 0;
	room_chg = 0;
	stop_flg =true;
	spawn_point[7] = NULL;
	room_in = true;
	delete_flg = false;
	first_stop = true;

	map_Item = false;
	map_Item_2 = false;
	pepepe = false;
	pepepe_2 = false;
	room_chg_stop = false;

	font_story_flg = false;

	
	//教室マップデータ
	r[1] = Save::ExternalDataOpen(L"教室１右サクラ.csv", &size);
	r[2] = Save::ExternalDataOpen(L"教室２右サクラ.csv", &size);
	r[3] = Save::ExternalDataOpen(L"教室３右サクラ.csv", &size);
	r[4] = Save::ExternalDataOpen(L"教室４右サクラ.csv", &size);
	r[5] = Save::ExternalDataOpen(L"教室５右サクラ.csv", &size);
	r[6] = Save::ExternalDataOpen(L"教室６右サクラ.csv", &size);

	//廊下マップデータ
	p[0] = Save::ExternalDataOpen(L"チーム開発マップ案1.csv", &size);
	p[1] = Save::ExternalDataOpen(L"マップ３.csv", &size);
	p[2] = Save::ExternalDataOpen(L"チーム開発マップ案2.csv", &size);
	p[3] = Save::ExternalDataOpen(L"チーム開発マップ案3.csv", &size);
    p[4] = Save::ExternalDataOpen(L"チーム開発マップ案４.csv", &size);
	p[5] = Save::ExternalDataOpen(L"チーム開発マップ案5.csv", &size);
    p[6] = Save::ExternalDataOpen(L"チーム開発マップ案6.csv", &size);
	p[7] = Save::ExternalDataOpen(L"チーム開発マップ案7.csv", &size);
	
	
}

//アクション
void CObjMain::Action()
{

	//教室マップを６回回したらセーブしたマップへのロードに切り替える
	if (room_chg >= 7)
	{
		room_chg = 1;
		room_chg_stop = true;
	}
	//８階のマップの処理
	if (map_chg == 0)
	{
		//廊下マップから教室マップへの切り替え処理
		if (room_chg >= 1 && room_in == true && stop_flg == true)
		{
			//音楽情報の読み込み
			Audio::LoadAudio(4, L"4教室扉SE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(4);

			//主人公の初期位置を変更
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(20.0f*64.0f);
			hero->SetY(4.0f*64.0f);
			m_scroll_x = -15.0f*64.0f;
			m_scroll_y = -5.0f*64.0f;

			//新規にマップをロードするする処理とセーブしたマップをロードする処理の切り替え
			if (room_chg_stop == false)
			{
				RoomMapChanger(r_map, r, room_chg);
			}
			else
			{
				for (int i = 0; i < ROOM_X; i++)
				{
					for (int j = 0; j < ROOM_Y; j++)
					{
						r_map[i][j] = save_room_map[i][j][room_chg];

					}
				}

			}
		}
		//初期の教室から廊下へのマップ切り替え（１度しか回さない）
		if (room_in == false && stop_flg == true && first_stop == true)
		{
			//音楽情報の読み込み
			Audio::LoadAudio(5, L"5マップ切り替えSE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(5);


			//主人公の初期位置を変更
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(0.0f);
			hero->SetY(64.0f * 3);
			m_scroll_x = 0.0f;
			m_scroll_y = 0.0f;

			//マップ切り替え関数を呼び出す
			MapChanger(map_chg, m_map, p);


			first_stop = false;
		}


	}
	//７階以降のマップの処理
	if (map_chg >= 1)
	{
		if (map_chg > 0 && stop_flg == true)
		{
			//音楽情報の読み込み
			Audio::LoadAudio(5, L"5マップ切り替えSE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(5);

			//主人公の初期位置の値を関数で指定する
			spawn_point[map_chg] = SpawnChanger(map_chg);

			//主人公の初期位置を変更
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(spawn_point[map_chg]);
			hero->SetY(0.0f);
			m_scroll_x = spawn_point[map_chg] * 1.0f;
			m_scroll_y = 0.0f;
			//マップ切り替え関数を呼び出す
			MapChanger(map_chg, m_map, p);


			memcpy(m_map, save_map, sizeof(int)*(MAP_X * MAP_Y));

		}
		//教室マップから廊下マップへの切り替え処理
		else if (room_in == false && stop_flg == true)
		{
			//音楽情報の読み込み
			Audio::LoadAudio(5, L"5マップ切り替えSE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(5);

			//新規にマップをロードするする処理とセーブしたマップをロードする処理の切り替え
			if (room_chg_stop == false)
			{
				RoomMapChanger(r_map, r, room_chg);
			}
			else
			{
				for (int i = 0; i < ROOM_X; i++)
				{
					for (int j = 0; j < ROOM_Y; j++)
					{
						r_map[i][j] = save_room_map[i][j][room_chg];

				}
			}
		}

		//主人公の位置を取得
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float hx = hero->GetX();
		float hy = hero->GetY();//知らないです

	




		//後方スクロールライン
		if (hx < 75)
		{
			hero->SetX(75);
			m_scroll_x -= hero->GetVX();
		}

		//前方スクロールライン
		if (hx > 400)
		{
			hero->SetX(400);
			m_scroll_x -= hero->GetVX();
		}
		//上方スクロールライン
		if (hy < 75)
		{
			hero->SetY(75);
			m_scroll_y -= hero->GetVY();
		}

		//下方スクロールライン
		if (hy > 400)
		{
			hero->SetY(400);
			m_scroll_y -= hero->GetVY();


	}
	
	//ギミックのヒットボックスをマップごとに変更する処理
	if (stop_flg == true)
	{
		HitBoxChanger(map_chg, m_map,room_in,room_chg,r_map);
		stop_flg2 = false;
		
	}

		//敵キャラの生成（廊下用）
		if (stop_flg == true)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 5)
					{

						//敵オブジェクト作成
						CObjEnemy* obje = new CObjEnemy((j - 1)*64.0f + m_scroll_x, (i - 1)*64.0f + m_scroll_y);
						Objs::InsertObj(obje, OBJ_ENEMY, 11);




					}
				}

			}
		}

		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 34)
				{
					if ((j*64.0f) + 64.0f >= hero->GetX() && (j * 64.0f) - 64.0f <= hero->GetX())
					{

						//アイテムオブジェクト作成
						CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
						Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

						m_map[i][j] = 1;
					}
				}
			}
		}
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == 34)
				{
					if ((j*64.0f) + 64.0f >= hero->GetX() && (j * 64.0f) - 64.0f <= hero->GetX())
					{

						//アイテムオブジェクト作成
						CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
						Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

						r_map[i][j] = 1;
					}
				}
			}
		}
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 35)
				{
					if ((i*64.0f) + 64.0f >= hero->GetY() && (i * 64.0f) - 64.0f <= hero->GetY())
					{

						//敵作成
						CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
						Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

						m_map[i][j] = 1;
					}
				}
			}
		}
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == 35)
				{
					if ((i*64.0f) + 64.0f >= hero->GetY() && (i * 64.0f) - 64.0f <= hero->GetY())
					{

						//敵作成
						CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
						Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

						r_map[i][j] = 1;
					}
				}
			}
		}
		//アイテム「鍵」の表示処理：教室用
		if (stop_flg == true && room_in == false)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 4)
					{

						//アイテムオブジェクト作成
						CObjItem * obji = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
						Objs::InsertObj(obji, OBJ_ITEM, 16);

					}
				}
			}
		}

		if (hero->GetEnemyFlag() == true)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 25)
					{

						//アイテムオブジェクト作成
						CObjFastEnemy* objf = new CObjFastEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
						Objs::InsertObj(objf, OBJ_FASTENEMY, 13);

						m_map[i][j] = 1;

					}
				}
			}
		}

		//アイテム「鍵」の表示処理：教室用

		//アイテム「教室用」の表示処理：廊下用
		if (stop_flg == true && room_in == true)
		{
			for (int i = 0; i < ROOM_X; i++)
			{
				for (int j = 0; j < ROOM_Y; j++)
				{
					if (r_map[i][j] == 4)
					{

						//アイテムオブジェクト作成
						CObjItem * obji = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
						Objs::InsertObj(obji, OBJ_ITEM, 16);




					}
				}

			}

		}
		//アイテム「鍵」の表示処理：廊下用
		if (stop_flg == true && room_in == false)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 4)
					{

						//アイテムオブジェクト作成
						CObjItem * objir = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
						Objs::InsertObj(objir, OBJ_ITEM, 16);




					}
				}

			}
		}
		//アイテム「薬」の表示処理：廊下用
		if (room_in == false && stop_flg == true)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 21)
					{

						//アイテムオブジェクト作成
						CObjheal * objh = new CObjheal(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
						Objs::InsertObj(objh, OBJ_HEAL, 16);




					}
				}

			}

		}




		//アイテム「薬」の表示処理：教室用
		if (room_in == true && stop_flg == false)
		{

			for (int i = 0; i < ROOM_X; i++)
			{
				for (int j = 0; j < ROOM_Y; j++)
				{
					if (r_map[i][j] == 5)
					{

						//アイテムオブジェクト作成
						CObjheal * objh = new CObjheal(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
						Objs::InsertObj(objh, OBJ_HEAL, 16);




					}
				}

			}

		}
		//アイテム「バールのようなもの」の表示処理：廊下用
		if (stop_flg == true && room_in == false)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 26)
					{

						//アイテムオブジェクト作成
						CObjbar * objba = new CObjbar(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
						Objs::InsertObj(objba, OBJ_BAR, 16);




					}
				}

			}
		}
		//アイテム「バールのようなもの」の表示処理：教室用
		if (room_in == true && stop_flg == true)
		{
			for (int i = 0; i < ROOM_X; i++)
			{
				for (int j = 0; j < ROOM_Y; j++)
				{
					if (r_map[i][j] == 26)
					{

						//アイテムオブジェクト作成
						CObjbar * objba = new CObjbar(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
						Objs::InsertObj(objba, OBJ_BAR, 16);




					}
				}

			}

		}

		stop_flg = false;

	}
	
	



/*内積関数
　引数1,2 float   ax  ,  ay  :Aベクトル
  引数3,4 float   bx  ,  by  :Bベクトル
  戻り値　float   ：射影
  内容　AベクトルとBベクトルて内積を行い射影を求める*/
float CObjMain::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * by;

	return t;
}

/*外積関数
　引数1,2 float   ax  ,  ay  :Aベクトル
  引数3,4 float   bx  ,  by  :Bベクトル
  戻り値　float   ：射影
  内容　AベクトルとBベクトルて内積を行い射影を求める*/
float CObjMain::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//符号を求めるマクロ
#define SGN(x) 1-(x<=0)-(x<0)

/*線と線の交差判定関数
  引数　float 1, 2  a1_x,a1y            :軸ベクトルAの始点
  引数　float 3, 4  a2x,a2y             :軸ベクトルAの終点
  引数　float 5, 6  b1x,b1y             :軸ベクトルAの始点
  引数　float 7, 8  b2x,b2y             :軸ベクトルAの始点
  引数　float 9, 10  out_px,out_py      :軸ベクトルAの始点
  戻り値　bool  :true=交点有り　false=交点無し
  内容：引数のA・Bベクトルの交点を見つけ、out_pxとout_pyの返す*/
bool CObjMain::LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float* out_px, float* out_py
)
{
	//エラーコード
	*out_px = -99999.0f; *out_py = -99999.0f;

	//Aベクトル作成(a2←a1)
	float ax = a2x - a1x;  float ay = a2y - a1y;

	//Bベクトル作成(b2←b1)
	float bx = b2x - b1x;  float by = b2y - b1y;

	//Cベクトル作成(b1←a1)
	float cx = b1x - a1x;  float cy = b1y - a1y;

	//Dベクトル作成(b2←a1)
	float dx = b2x - a1x;  float dy = b2y - a1y;
	//A X Cの射影とA X Bの射影を求める
	float t1 = Cross(ax, ay, cx, cy);
	float t2 = Cross(ax, ay, dx, dy);
	//符号が同じ方向になっているかどうかチェック
	if (SGN(t1) == SGN(t2))
		return false;
	//射影の絶対値化
	t1 = abs(t1);  t2 = abs(t2);

	//交点を求める
	float px = bx * (t1 / (t1 + t2)) + b1x;
	float py = by * (t1 / (t1 + t2)) + b1y;

	//APベクトル（ｐ←a1）
	float apx = px - a1x;  float apy = py - a1y;

	//BPベクトル（p←a2)
	float bpx = px - a2x;  float bpy = py - a2y;

	//A・APの射影とA・BPの射影を求める
	float w1 = Dot(ax, ay, apx, apy);
	float w2 = Dot(ax, ay, bpx, bpy);

	//符号チェック
	if (SGN(w1) == SGN(w2))
		return false; //交点が外

	//交点を返す
	*out_px = px; *out_py = py;

	return true;

}

/*主人公と壁の交差判定関数
　引数1,2 float  x,y          :主人公の位置
  引数3,4 float  vx,vy        :主人公の移動ベクトル
  引数5,6 float* out_px,out_y :Blockとの交点
  引数7   float* out          :一から交点までの距離
  主人公の位置＋移動ベクトルと各ブロックの変で好転の判定を行い
  最も近い交点の位置と距離を返す*/
bool CObjMain::HeroBlockCrossPoint(
	float x, float y, float vx, float vy,
	float *out_px, float *out_py, float *out_len
)

{
	
	bool pb = false;      //交点確認用
	float len = 99999.0f; //交点との距離
	//ブロックの辺ベクトル
	float edge[4][4] =
	{
		{ 0, 0,64, 0},
		{64, 0,64,64},
		{64,64, 0,64},
		{ 0,64, 0, 0},
	};

	//m_mapの全要素にアクセス
	//廊下用
	if (room_in == false)
	{


		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0 && m_map[i][j] != 5 && m_map[i][j] != 25)
				{
					//ブロックの４辺から交点を探す
					for (int k = 0; k < 4; k++)
					{
						//交点を探す
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,
							j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
							&px, &py);

						//交点チェック
						if (b == true)
						{
							//交点との距離を求める
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//見つけた交点の中で最も距離が短いものを探す
							if (len > l)
							{
								len = l;
								*out_px = px;
								*out_py = py;
								pb = true;
							}
						}

					}
				}
			}
		}
	}
	//教室用
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] > 0)
				{
					//ブロックの４辺から交点を探す
					for (int k = 0; k < 4; k++)
					{
						//交点を探す
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,
							j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
							&px, &py);

						//交点チェック
						if (b == true)
						{
							//交点との距離を求める
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//見つけた交点の中で最も距離が短いものを探す
							if (len > l)
							{
								len = l;
								*out_px = px;
								*out_py = py;
								pb = true;
							}
						}

					}
				}
			}
		}
	}
	*out_len = len;
	return pb;


}
/*BlockHit関数
  引数１　　float* x             :判定を行うobjectのX位置
  引数２　　float* y             :判定を行うobjectのY位置
  引数３　　bool  scroll_on_x    :判定を行うobjectはスクロールに影響を与えるかどうか（true=与える　false=与えない）
  引数５　　bool* up             :上下左右判定の上部分にあたっているかどうかを返す
  引数６　　bool* down           :上下左右判定の下部分にあたっているかどうかを返す
  引数７　　bool* left           :上下左右判定の左部分にあたっているかどうかを返す
  引数８　　bool* right          :上下左右判定の右部分にあたっているかどうかを返す
  引数９　　float* vx            :左右判定時の反発による移動方向・力の値を変えて返す
  引数１０　　float* vy            :上下判定時による自由落下運動の移動方向・力の値を変えて返す
  引数１１　int* bt            　:下部分判定時、特殊なブロックのタイプを返す
  判定を行うobjectとブロック64*64限定で、当たり判定と上下左右判定を行う
  その結果は引数４〜１０に返す*/

void CObjMain::BlockHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt, int *c_id, int *k_id
)
{
	
	//主人公の衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるブロックの種類の初期化
	*bt = 0;

	CObjItem* item = (CObjItem*)Objs::GetObj(OBJ_ITEM);
	CObjGimmick* gmk = (CObjGimmick*)Objs::GetObj(OBJ_GIMMICK);
	//m=mapの全要素にアクセス
	//廊下用
	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{


				if (m_map[i][j] != 21 && m_map[i][j] <= 99 && m_map[i][j] > 4 && m_map[i][j] != 7 && m_map[i][j] != 25 && m_map[i][j] != 26 && m_map[i][j] != 34 && m_map[i][j] != 35 || m_map[i][j] == 3)
				{
					//要素番号を座標に変更
					float bx = j * 64.0f;
					float by = i * 64.0f;



					//スクロールの影響
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//主人公とブロックの当たり判定
					if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + 64.0f) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + 64.0f))
					{
						//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy * rvy);


						//角度を求める
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if(r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さのより短い場合判定に入る
						if (len < 88.0f)
						{
							//角度で左右を判定
							if ((r < 45 && r >= 0) || r > 315)
							{
								//右
								*right = true;//主人公から見て、左の部分が衝突している
								*x = bx + 64.0f + (scroll_x);//ブロックの位置-主人公の幅]
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									stop_flg = true;
									map_chg++;
									stop_flg2 = true;
									
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = 99;

									hero->SetFlug(false);
									if (map_chg == 7)
									{
										Scene::SetScene(new CSceneGameClear);
									}


									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
								else if (m_map[i][j] == 17  && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										stop_flg = true;

										//item->SetFlag(true);
										
										room_chg++;
								
										//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);



										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								*vx = -(*vx)*0.1f;//-VX*反発係数
							}
							if (r > 45 && r < 135)
							{
								//上
								*down = true;//主人公から見て、下の部分が衝突している
								*y = by - 64.0f + (scroll_y);//ブロックの位置-主人公の幅
								if (m_map[i][j] == 2)
									*bt = m_map[i][j];
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									if (map_chg == 7)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = 99;

									hero->SetFlug(false);

									stop_flg = true;
									stop_flg2 = true;
						
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
								else if (m_map[i][j] == 16  && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										room_chg++;

										
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - 64.0f + (scroll_x);//ブロックの位置-主人公の幅
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY&&Input::GetVKey('E')==true)
								{
									stop_flg = true;
									stop_flg2 = true;
									
									first_stop = true;
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = 99;

									hero->SetFlug(false);

									if (map_chg == 7)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();

									map_chg++;
								}
								else if (m_map[i][j] == 18&& *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										stop_flg = true;

										//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								*vx = -(*vx)*0.1f;//-VX*反発係数
							}
							if (r > 225 && r < 315)
							{
								//下
								*up = true;//主人公から見て、上の部分が衝突している
								*y = by + 64.0f + (scroll_y);//ブロックの位置-主人公の
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									stop_flg = true;
									stop_flg2 = true;
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = 99;

									hero->SetFlug(false);
									if (map_chg == 7)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
							
								else if (m_map[i][j] == 15 && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{

										room_in = true;
										stop_flg = true;
										room_chg++;

										//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}

							}
						}
					}

				}
			}
		}
	}
	//教室用
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{


				if (r_map[i][j] <= 99 && r_map[i][j] > 4 && r_map[i][j] != 7 && r_map[i][j] != 26 && r_map[i][j] != 34 && r_map[i][j] != 35 || r_map[i][j] == 3)
				{
					//要素番号を座標に変更
					float bx = j * 64.0f;
					float by = i * 64.0f;

					//スクロールの影響
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//主人公とブロックの当たり判定
					if ((*x + (-scroll_x) + BLOCK_SIZE_X > bx) && (*x + (-scroll_x) < bx + BLOCK_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y > by) && (*y + (-scroll_y) < by + BLOCK_SIZE_Y))
					{
						//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy * rvy);


						//角度を求める
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さのより短い場合判定に入る
						if (len < 88.0f)
						{
							//角度で左右を判定
							if ((r < 45 && r >= 0) || r > 315)
							{
								//右
								*right = true;//主人公から見て、左の部分が衝突している
								*x = bx + 64.0f + (scroll_x);//ブロックの位置-主人公の幅
								//通常の時
								if (r_map[i][j] == 17 && *c_id == CHAR_HERO)
								{
									if (room_in == true && room_chg >= 1)
									{
										room_in = false;
										stop_flg = true;

										//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);

										memcpy(save_room_map[room_chg], r_map, sizeof(int)*(ROOM_X * ROOM_Y));
									}

								}

								//初期の部屋でバールを使わないと開かない処理
								else if (room_in == true && room_chg == 0)
								{
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									if (hero->Getflag_3() == true && Input::GetVKey('E'))
									{
										CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
										hero->SetFlug_3(false);
										gui->SetID(99);

										room_in = false;
										stop_flg = true;

										//主人公が階段に当たった瞬間に位置とスクロール情報を保存する
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);
										if (room_chg >= 1)
										{
											for (int i = 0; i < ROOM_X; i++)
											{
												for (int j = 0; j < ROOM_Y; j++)
												{
													save_room_map[i][j][room_chg] = r_map[i][j];
												}
											}
										}
									}
								}

								}
								if (r_map[i][j] == 31 && Input::GetVKey('E') == true)
								{
									font_story_flg = true;
								}
								*vx = -(*vx)*0.1f;//-VX*反発係数
							}
							if (r > 45 && r < 135)
							{
								//上
								*down = true;//主人公から見て、下の部分が衝突している
								*y = by - 64.0f + (scroll_y);//ブロックの位置-主人公の幅
								if (r_map[i][j] == 2)
									*bt = m_map[i][j];
								//通常の時
								if (r_map[i][j] == 16 && *c_id == CHAR_HERO)
								{
									if (room_in == true && room_chg >= 1)
									{
										room_in = false;
										stop_flg = true;

									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									hero->SetX(save_x[map_chg][0] + hero->GetVX());
									hero->SetY(save_y[map_chg][0] + hero->GetVY());
									main->SetScrollX(save_scroll_x[map_chg][0]);
									main->SetScrollY(save_scroll_y[map_chg][0]);

									memcpy(save_room_map[room_chg], r_map, sizeof(int)*(ROOM_X * ROOM_Y));
								}
								//初期の部屋でバールを使わないと開かない処理
								else if (room_in == true && room_chg == 0)
								{
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									if (hero->Getflag_3() == true && Input::GetVKey('E'))
									{
										CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
										hero->SetFlug_3(false);
										gui->SetID(99);

										room_in = false;
										stop_flg = true;

										//主人公が階段に当たった瞬間に位置とスクロール情報を保存する
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);

										if (room_chg >= 1)
										{
											for (int i = 0; i < ROOM_X; i++)
											{
												for (int j = 0; j < ROOM_Y; j++)
												{
													save_room_map[i][j][room_chg] = r_map[i][j];
												}
											}
										}
									}

								}
								if (r_map[i][j] == 31 && Input::GetVKey('E') == true)
								{
									font_story_flg = true;
								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - 64.0f + (scroll_x);//ブロックの位置-主人公の幅
								//通常の時
								if (r_map[i][j] == 18 && *c_id == CHAR_HERO)
								{
									if (room_in == true && room_chg >= 1)
									{
										room_in = false;
										stop_flg = true;

									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									hero->SetX(save_x[map_chg][0] + hero->GetVX());
									hero->SetY(save_y[map_chg][0] + hero->GetVY());
									main->SetScrollX(save_scroll_x[map_chg][0]);
									main->SetScrollY(save_scroll_y[map_chg][0]);

									memcpy(save_room_map[room_chg], r_map, sizeof(int)*(ROOM_X * ROOM_Y));
								}

							}
							else if (room_in == true && room_chg == 0)
							{
								CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
								if (hero->Getflag_3() == true && Input::GetVKey('E'))
								{
									CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
									hero->SetFlug_3(false);
									gui->SetID(99);

									room_in = false;
									stop_flg = true;

									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									hero->SetX(save_x[map_chg][0] + hero->GetVX());
									hero->SetY(save_y[map_chg][0] + hero->GetVY());
									main->SetScrollX(save_scroll_x[map_chg][0]);
									main->SetScrollY(save_scroll_y[map_chg][0]);

									if (room_chg >= 1)
									{
										for (int i = 0; i < ROOM_X; i++)
										{
											for (int j = 0; j < ROOM_Y; j++)
											{
												save_room_map[i][j][room_chg] = r_map[i][j];
											}
										}
									}
								}

								}
								if (r_map[i][j] == 31 && Input::GetVKey('E') == true)
								{
									font_story_flg = true;
								}
								*vx = -(*vx)*0.1f;//-VX*反発係数
							}
							if (r > 225 && r < 315)
							{
								//下
								*up = true;//主人公から見て、上の部分が衝突している
								*y = by + 64.0f + (scroll_y);//ブロックの位置-主人公の幅
								//通常の時
								if (r_map[i][j] == 15 && *c_id == CHAR_HERO)
								{
									if (room_in == true)
									{
										room_in = false;
										stop_flg = true;

									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する。
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									hero->SetX(save_x[map_chg][0] + hero->GetVX());
									hero->SetY(save_y[map_chg][0] + hero->GetVY());
									main->SetScrollX(save_scroll_x[map_chg][0]);
									main->SetScrollY(save_scroll_y[map_chg][0]);

									if (room_chg >= 1)
									{
										for (int i = 0; i < ROOM_X; i++)
										{
											for (int j = 0; j < ROOM_Y; j++)
											{
												save_room_map[i][j][room_chg] = r_map[i][j];
											}
										}
									}
								}
								memcpy(save_room_map[room_chg], r_map, sizeof(int)*(ROOM_X * ROOM_Y));
							}
							//初期の部屋でバールを使わないと開かない処理
							else if (room_in == true && room_chg == 0)
							{
								CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
								if (hero->Getflag_3() == true && Input::GetVKey('E'))
								{
									CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
									hero->SetFlug_3(false);
									gui->SetID(99);

								}
								if (r_map[i][j] == 31&&Input::GetVKey('E')==true)
								{
									font_story_flg = true;
								}
										room_in = false;
										stop_flg = true;

									//主人公が階段に当たった瞬間に位置とスクロール情報を保存する
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									hero->SetX(save_x[map_chg][0] + hero->GetVX());
									hero->SetY(save_y[map_chg][0] + hero->GetVY());
									main->SetScrollX(save_scroll_x[map_chg][0]);
									main->SetScrollY(save_scroll_y[map_chg][0]);

									memcpy(save_room_map[room_chg], r_map, sizeof(int)*(ROOM_X * ROOM_Y));

								}
							}
						}
						if (r_map[i][j] == 19 && Input::GetVKey(VK_RETURN) == true)
						{
						}
						//本棚から鍵を取る処理
						if (r_map[i][j] == 19 && Input::GetVKey(VK_RETURN) == true)
						{

							CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
							*k_id = ITEM_KEY;

							hero->SetFlug(true);

							font_flg = true;
						}
						if (r_map[i][j] == 30 && Input::GetVKey(VK_RETURN) == true)
						{
							//UIオブジェクト作成
							CObjText* objtx = new CObjText();
							Objs::InsertObj(objtx, OBJ_TEXT, 12);
						}
						if (*vy < 0)
						{
							*vy = 0.0f;
						}

					}

						
					


					

				}
			}
		}
	}
}

/*ItemHit関数
  引数１　　float* x             :判定を行うobjectのX位置
  引数２　　float* y             :判定を行うobjectのY位置
  引数３　　bool  scroll_on_x    :判定を行うobjectはスクロールに影響を与えるかどうか（true=与える　false=与えない）
  引数５　　bool* up             :上下左右判定の上部分にあたっているかどうかを返す
  引数６　　bool* down           :上下左右判定の下部分にあたっているかどうかを返す
  引数７　　bool* left           :上下左右判定の左部分にあたっているかどうかを返す
  引数８　　bool* right          :上下左右判定の右部分にあたっているかどうかを返す
  引数９　　float* vx            :左右判定時の反発による移動方向・力の値を変えて返す
  引数１０　　float* vy            :上下判定時による自由落下運動の移動方向・力の値を変えて返す
  引数１１　int* bt            　:下部分判定時、特殊なブロックのタイプを返す
  判定を行うobjectとブロック64*64限定で、当たり判定と上下左右判定を行う
  その結果は引数４〜１０に返す*/

void CObjMain::ItemHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt
)
{
	//主人公の衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	

	//踏んでいるブロックの種類の初期化
	*bt = 0;
	
	if (room_in == false)
	{
		//m=mapの全要素にアクセス
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 4 || m_map[i][j] == 21 || m_map[i][j] == 26)
				{



					//要素番号を座標に変更
					float bx = j * 64.0f;
					float by = i * 64.0f;

					//スクロールの影響
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//主人公とブロックの当たり判定
					if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + ITEM_SIZE_X) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + ITEM_SIZE_Y))
					{
						//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy * rvy);


						//角度を求める
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さのより短い場合判定に入る
						if (len < 88.0f)
						{
							//角度で左右を判定
							if ((r < 45 && r>0) || r > 315)
							{
								//右
								*right = true;//主人公から見て、左の部分が衝突している
								*x = bx + ITEM_SIZE_X + (scroll_x);//ブロックの位置-主人公の幅
								ix = bx / 64;
								iy = by / 64;

								//アイテムを取得した際にアイテムを消す処理
								if (delete_flg == true)
								{
									m_map[iy][ix] = 1;

									delete_flg = false;
								}

								*vx = -(*vx)*0.1f;//-VX*反発係数
							}
							if (r > 45 && r < 135)
							{
								//上
								*down = true;//主人公から見て、下の部分が衝突している
								*y = by - 64.0f + (scroll_y);//ブロックの位置-主人公の幅
								ix = bx / 64;
								iy = by / 64;

								//アイテムを取得した際にアイテムを消す処理
								if (delete_flg == true)
								{
									m_map[iy][ix] = 1;

									delete_flg = false;
								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - 64.0f + (scroll_x);//ブロックの位置-主人公の幅
								ix = bx / 64;
								iy = by / 64;

								//アイテムを取得した際にアイテムを消す処理
								if (delete_flg == true)
								{
									m_map[iy][ix] = 1;

									delete_flg = false;
								}
								*vx = -(*vx)*0.1f;//-VX*反発係数
							}
							if (r > 225 && r < 315)
							{
								//下
								*up = true;//主人公から見て、上の部分が衝突している
								*y = by + ITEM_SIZE_Y + (scroll_y);//ブロックの位置-主人公の幅
								ix = bx / 64;
								iy = by / 64;
								//アイテムを取得した際にアイテムを消す処理
								if (delete_flg == true)
								{
									m_map[iy][ix] = 1;

									delete_flg = false;
								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}


							}
							//鍵
							if (m_map[i][j] == 4)
							{
								map_Item = true;
							}
							//薬
							if (m_map[i][j] == 21)
							{
								map_Item_2 = true;
							}
							//バール
							if (m_map[i][j] == 26)
							{
								map_Item_3 = true;
							}


						}


					}


				}

			}

		}
	}
	//教室用
	if(room_in==true)
	{
		//m=mapの全要素にアクセス
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == 4 || r_map[i][j] == 21 || r_map[i][j] == 26)
				{



					//要素番号を座標に変更
					float bx = j * 64.0f;
					float by = i * 64.0f;

				//スクロールの影響
				float scroll_x = scroll_on_x ? m_scroll_x : 0;
				float scroll_y = scroll_on_y ? m_scroll_y : 0;
				//主人公とブロックの当たり判定
				if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + ITEM_SIZE_X) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + ITEM_SIZE_Y))
				{
					//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy * rvy);


						//角度を求める
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);


					//lenがある一定の長さのより短い場合判定に入る
					if (len < 88.0f)
					{
						//角度で左右を判定
						if ((r < 45 && r>0) || r > 315)
						{
							//右
							*right = true;//主人公から見て、左の部分が衝突している
							*x = bx + ITEM_SIZE_X + (scroll_x);//ブロックの位置-主人公の
							ix = bx / 64;
							iy = by / 64;

								if (delete_flg == true)
								{
									r_map[iy][ix] = 1;

									delete_flg = false;
								}
								*vx = -(*vx)*0.1f;//-VX*反発係数

							}
							if (r > 45 && r < 135)
							{
								//上
								*down = true;//主人公から見て、下の部分が衝突している
								*y = by - 64.0f + (scroll_y);//ブロックの位置-主人公の幅
								ix = bx / 64;
								iy = by / 64;

								if (delete_flg == true)
								{
									r_map[iy][ix] = 1;

									delete_flg = false;
								}

								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - 64.0f + (scroll_x);//ブロックの位置-主人公の幅
								ix = bx / 64.0f;
								iy = by / 64.0f;

								if (delete_flg == true)
								{
									r_map[iy][ix] = 1;

								delete_flg = false;
							}
							*vx = -(*vx)*0.1f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公から見て、上の部分が衝突している
							*y = by + ITEM_SIZE_Y + (scroll_y);//ブロックの位置-主人公の幅
							ix = bx / 64;
							iy = by / 64;

								if (delete_flg == true)
								{
									r_map[iy][ix] = 1;

									delete_flg = false;
								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}


						}
						//鍵
						if (r_map[i][j] == 4)
						{
							map_Item = true;
						}
						//薬
						if (r_map[i][j] == 21)
						{
							map_Item_2 = true;
						}
						//バールのようなもの
						if (r_map[i][j] == 26)
						{
							map_Item_3 = true;
						}


						}


					}


				}

			}

		}
	}
	
}


	


//ドロー
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置


	if(room_in==false)
	{ 
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0)
				{


					//表示位置の設定
					dst.m_top = i * 64.0f + m_scroll_y;
					dst.m_left = j * 64.0f + m_scroll_x;
					dst.m_right = dst.m_left + 64.0;
					dst.m_bottom = dst.m_top + 64.0;


					//床テクスチャ
					if (m_map[i][j] == 1 || m_map[i][j] == 4 || m_map[i][j] == 7 || m_map[i][j] == 13 || m_map[i][j] == 21||m_map[i][j]==25 || m_map[i][j] == 26)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					//13がなければ　床
					if (m_map[i][j] == 13 && plane_chg_hole == false)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 34||m_map[i][j]==35)				
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(39, &src, &dst, c, 0.0f);
					}
					else if (m_map[i][j] == 13 && plane_chg_hole == true)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(21, &src, &dst, c, 0.0f);
					}
					//階段テクスチャ
					if (m_map[i][j] == 3)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(7, &src, &dst, c, 0.0f);
					}
					//壁テクスチャ４つ
					if (m_map[i][j] == 9)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(3, &src, &dst, c, 0.0f);
					}
					if(m_map[i][j]==10)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(18, &src, &dst, c, 0.0f);
					}	
					if (m_map[i][j] == 11)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(19, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 12)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(20, &src, &dst, c, 0.0f);
					}//壁テクスチャ４つ↑

					//扉テクスチャ４つ
					if (m_map[i][j] == 15)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(25, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 16)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(26, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 17)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(28, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 18)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(27, &src, &dst, c, 0.0f);
					}//扉テクスチャ４つ↑
					 //壁角4つ
					if (m_map[i][j] == 27)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(34, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 28)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(35, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 29)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(36, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 30)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(37, &src, &dst, c, 0.0f);
					}//角壁4つ↑

					 //壁角２・4つ
					if (m_map[i][j] == 31)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(38, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 32)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(39, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 33)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(40, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 34)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(41, &src, &dst, c, 0.0f);
					}//角壁２・4つ↑
				}
			}

		}
	}
	else 
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] > 0)
				{


					//表示位置の設定
					dst.m_top = i * 64.0f + m_scroll_y;
					dst.m_left = j * 64.0f + m_scroll_x;
					dst.m_right = dst.m_left + 64.0;
					dst.m_bottom = dst.m_top + 64.0;


					//床テクスチャ
					if (r_map[i][j] >= 1&&r_map[i][j]<= 8|| r_map[i][j] == 5||r_map[i][j]==7|| r_map[i][j] == 8|| r_map[i][j] == 13||r_map[i][j]==31)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					//机まとめ
					if(r_map[i][j]==2)
					{
						src.m_top = 100.0f;
						src.m_left = 350.0f;
						src.m_right = src.m_left + 200.0f;
						src.m_bottom = src.m_top + 200.0f;

						Draw::Draw(30, &src, &dst, c, 0.0f);
					}
					//椅子まとめ
					if(r_map[i][j]==3)
					{
						src.m_top = 50.0f;
						src.m_left = 320.0f;
						src.m_right = src.m_left + 180.0f;
						src.m_bottom = src.m_top + 180.0f;

						Draw::Draw(31, &src, &dst, c, 0.0f);
					}
					//敵の出現床
					if (r_map[i][j] == 34 || r_map[i][j] == 35)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(43, &src, &dst, c, 0.0f);
					}
					//壁テクスチャ
					if (r_map[i][j] == 9)
					//壁テクスチャ4つ
					if (r_map[i][j] == 9||r_map[i][j]==19)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(3, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 10)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(19, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 11)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(18, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 12)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(20, &src, &dst, c, 0.0f);
					}//壁テクスチャ４つ↑

					//扉テクスチャ4つ
					if (r_map[i][j] == 15)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(26, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 16)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(25, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 17)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(28, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 18)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(27, &src, &dst, c, 0.0f);
					}//扉４つ↑
					
					 //壁角4つ
					if (r_map[i][j] == 27)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(34, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 28)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(35, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 29)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(36, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 30)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(37, &src, &dst, c, 0.0f);
					}//角壁4つ↑
						
					//アイテム（仮）
					if (r_map[i][j] == 4)
					{

							//描画切り取り位置
							src.m_top = 17.0f;
							src.m_left = 20.0f;
							src.m_right = src.m_left + 25.0f;
							src.m_bottom = src.m_top + 30.0f;
							
							//表示位置の設定
							dst.m_top = i * 64.0f + m_scroll_y;
							dst.m_left = j * 64.0f + m_scroll_x;
							dst.m_right = dst.m_left + ITEM_SIZE_X;
							dst.m_bottom = dst.m_top + ITEM_SIZE_Y;

							Draw::Draw(8, &src, &dst, c, 0.0f);
					}
					//本棚
					if (r_map[i][j] == 19)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;
						
						Draw::Draw(29, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 31)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(33, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 30)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(33, &src, &dst, c, 0.0f);
					}
					//教卓
					if (r_map[i][j] == 13)
					{

						//描画切り取り位置
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						
						Draw::Draw(40, &src, &dst, c, 0.0f);
					}
				}
			}
		}

	}
	//本棚から鍵を入手した際のテキストの表示と一定時間たったらテキストを消す処理
	if (font_key_flg == true && m_time <= 300)
	{
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

		Font::StrDraw(L"鍵を入手した...", 350.0f,530.0f, 25, c);

		m_time++;
	}
	else
	{
		font_key_flg = false;

		m_time = 0;
	}
}
	


